#include "Map.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <thread>
#include <chrono>
#include "Enemy.h"
#include "WeaponSystem.h"
#include "PlayerStats.h"
#include <limits>
#include "LevelSystem.h"
#include "Shop.h"




bool Map::startCombat(PlayerInventory& inventory, PlayerStats& stats, EnemyType forcedType) {
    Enemy enemy(forcedType);
    int playerHP = stats.currentHP;

    int playerBaseDMG = inventory.equippedWeapon ? inventory.equippedWeapon->getDamage() : 5;
    playerBaseDMG = static_cast<int>(playerBaseDMG * stats.bonusDMG);

    const int barLength = 10;
    const int delayPerCharMs = 150;

    while (true) {
        for (int i = 0; i <= barLength; ++i) {
            std::cout << "\r[";
            for (int j = 0; j < barLength; ++j) {
                std::cout << (j < i ? "-" : " ");
            }
            std::cout << "]  HP: " << playerHP << "   ";
            std::cout.flush();
            std::this_thread::sleep_for(std::chrono::milliseconds(delayPerCharMs));
        }

        int enemyArmor = enemy.getArmor();
        int enemyDamage = enemy.getDamage();

        bool isCrit = ((rand() % 100) < (stats.bonusCritChance * 100));
        int damageToEnemy = playerBaseDMG - enemyArmor;
        if (damageToEnemy < 0) damageToEnemy = 0;
        if (isCrit) damageToEnemy *= 2;

        enemy.takeDamage(damageToEnemy);
        std::cout << "Nepøítel má nyní " << enemy.getHP() << " HP\n";

        playerHP -= enemyDamage;

        std::cout << "\nDal jsi nepøíteli " << damageToEnemy << " DMG" << (isCrit ? " (kritický zásah!)" : "") << ".\n";
        std::cout << "Nepøítel ti dal " << enemyDamage << " DMG.\n";

        if (playerHP <= 0) {
            std::cout << "Byl jsi poražen. Konec hry.\n";
            exit(0);
        }

        if (!enemy.isAlive()) {
            std::cout << "Zvítìzil jsi!\n";
            stats.currentHP = playerHP;

            int xpReward = enemy.getXPReward();
            int goldReward = enemy.getGoldReward();
            stats.xp += xpReward;
            stats.gold += goldReward;

            std::cout << "Získal jsi " << xpReward << " XP a " << goldReward << " zlaákù!\n";

            if (stats.xp >= stats.xpToNext) {
                std::cout << "*** LEVEL UP! Jsi nyní level " << (stats.level + 1) << " ***\n";
                levelUp(stats);
            }

            std::cout << "\n[1] Pokraèovat\n";
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cin.get();
            system("cls");
            return true;
        }
    }
}

Map::Map() {
    grid = std::vector<std::vector<char>>(MAP_SIZE, std::vector<char>(MAP_SIZE, ' '));
    revealed = std::vector<std::vector<bool>>(MAP_SIZE, std::vector<bool>(MAP_SIZE, false));
    playerX = MAP_SIZE / 2;
    playerY = MAP_SIZE / 2;
    shopPlaced = false;
    revealSurroundings();
}

void Map::drawMap() const {
    system("cls");

    for (int y = 0; y < MAP_SIZE; y++) {
        for (int x = 0; x < MAP_SIZE; x++) {
            if (x == playerX && y == playerY) {
                std::cout << "P ";
            }
            else if (revealed[y][x]) {
                std::cout << grid[y][x] << " ";
            }
            else {
                std::cout << "? ";
            }
        }
        std::cout << "\n";
    }
}

bool Map::movePlayer(char direction, PlayerInventory& inventory, PlayerStats& stats) {
    grid[playerY][playerX] = '.';

    switch (direction) {
    case 'w': if (playerY > 0) playerY--; break;
    case 's': if (playerY < MAP_SIZE - 1) playerY++; break;
    case 'a': if (playerX > 0) playerX--; break;
    case 'd': if (playerX < MAP_SIZE - 1) playerX++; break;
    }

    revealSurroundings();

    if (grid[playerY][playerX] == 'C') {
        grid[playerY][playerX] = '.';
        return startCombat(inventory, stats, EnemyType::Normal);
    }
    else if (grid[playerY][playerX] == 'D') {
        grid[playerY][playerX] = '.';
        std::cout << "Narazil jsi na dungeon!\n";
        std::cout << "Vyber úroveò nepøítele:\n";
        std::cout << "1. Slabý\n2. Støední\n3. Silný\nTvoje volba: ";
        int volba;
        std::cin >> volba;
        EnemyType type = EnemyType::Normal;
        if (volba == 2) type = EnemyType::Elite;
        else if (volba == 3) type = EnemyType::Boss;
        return startCombat(inventory, stats, type);
    }
    else if (grid[playerY][playerX] == 'S') {
        grid[playerY][playerX] = '.';
        extern Shop globalShop;
        globalShop.showShop();
        globalShop.handlePurchase(inventory, stats);
    }

    return false;
}

void Map::revealSurroundings() {
    srand(static_cast<unsigned>(time(nullptr)));

    for (int dy = -1; dy <= 1; ++dy) {
        for (int dx = -1; dx <= 1; ++dx) {
            int x = playerX + dx;
            int y = playerY + dy;
            if (x >= 0 && y >= 0 && x < MAP_SIZE && y < MAP_SIZE) {
                if (!revealed[y][x]) {
                    revealed[y][x] = true;

                    if (grid[y][x] == ' ') {
                        int roll = rand() % 100;

                        if (!shopPlaced && roll < 1) {
                            grid[y][x] = 'S';
                            shopPlaced = true;
                        }
                        else if (roll < 6) {
                            grid[y][x] = 'D';
                        }
                        else if (roll < 8) {
                            grid[y][x] = 'C';
                        }
                    }
                }
            }
        }
    }
}
