#include "Map.h"
#include <iostream>
#include <cstdlib> // rand
#include <ctime>   // time


Map::Map() {
    grid = std::vector<std::vector<char>>(MAP_SIZE, std::vector<char>(MAP_SIZE, ' '));
    revealed = std::vector<std::vector<bool>>(MAP_SIZE, std::vector<bool>(MAP_SIZE, false));
    playerX = MAP_SIZE / 2;
    playerY = MAP_SIZE / 2;
    shopPlaced = false;

    revealSurroundings();
}


void Map::drawMap() const {
    system("cls");  // Pro Windows – smaže obrazovku

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


void Map::movePlayer(char direction) {
    grid[playerY][playerX] = '.';  // oznaèí odkud se hráè pohnul

    switch (direction) {
    case 'w': if (playerY > 0) playerY--; break;
    case 's': if (playerY < MAP_SIZE - 1) playerY++; break;
    case 'a': if (playerX > 0) playerX--; break;
    case 'd': if (playerX < MAP_SIZE - 1) playerX++; break;
    }

    revealSurroundings();
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

                    // jen prázdná místa mùžou mít nìco
                    if (grid[y][x] == ' ') {
                        int roll = rand() % 100;

                        if (!shopPlaced && roll < 1) {        // 1% šance na shop
                            grid[y][x] = 'S';
                            shopPlaced = true;
                        }
                        else if (roll < 6) {                  // 5% dungeon
                            grid[y][x] = 'D';
                        }
                        else if (roll < 8) {                  // 2% encounter
                            grid[y][x] = 'C';
                        }
                    }
                }
            }
        }
    }
}