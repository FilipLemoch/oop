#include <iostream>
#include "Map.h"
#include "WeaponSystem.h"
#include "PlayerStats.h"
#include <cmath>
#include <limits>
#include <cctype>
#include "LevelSystem.h"
#include "Shop.h"

Shop globalShop;


void showMenu() {
    std::cout << "==== MENU ====\n";
    std::cout << "1. Hrát hru\n";
    std::cout << "2. Zobrazit mapu\n";
    std::cout << "3. Inventář\n";
    std::cout << "4. Konec\n";
    std::cout << "Vyber: ";
}

void zobrazInventar(const PlayerInventory& inv) {
    std::cout << "=== INVENTÁŘ ===\n";
    if (inv.weapons.empty()) {
        std::cout << "Žádné zbraně v inventáři.\n";
    }
    else {
        std::cout << "Zbraně:\n";
        for (size_t i = 0; i < inv.weapons.size(); ++i) {
            std::cout << i + 1 << ". " << inv.weapons[i].getName() << "\n";
        }
    }
    std::cout << "Nasazená zbraň: "
        << (inv.equippedWeapon ? inv.equippedWeapon->getName() : "Žádná") << "\n";
    std::cout << "Brnění: " << inv.equippedArmor.getName() << "\n";
    std::cout << "Štít: " << (inv.hasShield ? "Ano" : "Ne") << "\n\n";
}

int main() {
    Map gameMap;
    PlayerInventory inventory;
    PlayerStats stats;

    Weapon starter("Dagger", 10, 2);
    inventory.weapons.push_back(starter);
    inventory.equippedWeapon = starter;

    char input;

    while (true) {
        showMenu();
        std::cin >> input;

        if (input == '1') {
            while (true) {
                gameMap.drawMap();
                std::cout << "Pohyb: [W] Nahoru, [S] Dolu, [A] Vlevo, [D] Vpravo, [R] Odpočinek, [X] Nová mapa, [Q] Zpět do menu\n";
                std::cin >> input;
                input = std::tolower(input);
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                if (input == 'q') break;

                else if (input == 'r') {
                    int healed = std::min(20, stats.baseHP - stats.currentHP);
                    stats.currentHP += healed;
                    std::cout << "Odpočíváš... Doplněno " << healed << " HP. Aktuální HP: " << stats.currentHP << "/" << stats.baseHP << "\n";
                }

                else if (input == 'x') {
                    gameMap = Map();
                    std::cout << "Generuji novou mapu...\n";
                }

                bool victory = gameMap.movePlayer(input, inventory, stats);
                }
            }
        
        else if (input == '2') {
            gameMap.drawMap();
        }
        else if (input == '3') {
            zobrazInventar(inventory);
            std::cout << "Zadej příkaz (např. eq2 pro nasazení zbraně 2, nebo 0 pro návrat): ";

            std::string prikaz;
            std::cin >> prikaz;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            if (prikaz.substr(0, 2) == "eq") {
                try {
                    int index = std::stoi(prikaz.substr(2)) - 1;
                    if (index >= 0 && index < static_cast<int>(inventory.weapons.size())) {
                        Weapon nova = inventory.weapons[index];

                        
                        if (inventory.equippedWeapon) {
                            inventory.weapons.push_back(*inventory.equippedWeapon);
                        }

                        
                        inventory.weapons.erase(inventory.weapons.begin() + index);
                        inventory.equippedWeapon = nova;

                        std::cout << "Nasadil jsi: " << inventory.equippedWeapon->getName() << "\n";
                    }
                    else {
                        std::cout << "Neplatné číslo zbraně.\n";
                    }
                }
                catch (...) {
                    std::cout << "Neplatný vstup. Použij např. eq1.\n";
                }
            }
        }


        else if (input == '4') {
            std::cout << "Ukončuji hru...\n";
            break;
        }
    }

    return 0;
}
