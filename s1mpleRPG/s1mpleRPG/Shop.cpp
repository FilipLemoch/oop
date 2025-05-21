#include "Shop.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <limits>

Shop::Shop() {
    generateShopItems();
}

void Shop::generateShopItems() {
    items.clear();
    for (int i = 0; i < 4; ++i) {
        bool isWeapon = rand() % 2;
        if (isWeapon) {
            std::vector<std::string> names = { "Dagger", "Iron Sword", "Crossbow", "Mace", "Axe" };
            std::string name = names[rand() % names.size()];
            int baseDMG = 10 + rand() % 11;
            int level = 1 + rand() % 5;
            items.push_back({ Weapon(name, baseDMG, level) });
        }
        else {
            std::vector<std::string> names = { "Cloth Armor", "Leather Armor", "Chainmail", "Plate Armor" };
            std::string name = names[rand() % names.size()];
            ArmorType type = static_cast<ArmorType>(rand() % 3);
            int armorValue = 5 + rand() % 11;
            items.push_back({ Armor(name, armorValue, type) });
        }
    }
}

void Shop::showShop() const {
    std::cout << "\n=== OBCHOD ===\n";
    for (size_t i = 0; i < items.size(); ++i) {
        std::cout << i + 1 << ". ";
        if (std::holds_alternative<Weapon>(items[i].item)) {
            std::cout << std::get<Weapon>(items[i].item).getName();
        }
        else {
            std::cout << std::get<Armor>(items[i].item).getName();
        }
        std::cout << "\n";
    }
    std::cout << "5. Kovadlina (vylepšit vybavení)\n";
    std::cout << "Zadej èíslo položky nebo 0 pro návrat: ";
}

void Shop::handlePurchase(PlayerInventory& inventory, PlayerStats& stats) {
    int volba;
    std::cin >> volba;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    if (volba >= 1 && volba <= 4) {
        const auto& selected = items[volba - 1];
        if (std::holds_alternative<Weapon>(selected.item)) {
            Weapon w = std::get<Weapon>(selected.item);
            int cost = w.getLevel() * 15;

            std::cout << "Opravdu chceš koupit " << w.getName() << " za " << cost << " zlaákù? [Y/N]: ";
            char confirm;
            std::cin >> confirm;
            confirm = std::tolower(confirm);
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            if (confirm == 'y') {
                if (stats.gold >= cost) {
                    stats.gold -= cost;
                    inventory.weapons.push_back(w);
                    std::cout << "Zakoupil jsi: " << w.getName() << " za " << cost << " zlaákù.\n";
                }
                else {
                    std::cout << "Nemáš dost zlata (" << stats.gold << "/" << cost << ").\n";
                }
            }
            else {
                std::cout << "Nákup zrušen.\n";
            }
        }
        else {
            Armor a = std::get<Armor>(selected.item);
            std::cout << "Opravdu chceš koupit " << a.getName() << " za 50 zlaákù? [Y/N]: ";
            char confirm;
            std::cin >> confirm;
            confirm = std::tolower(confirm);
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            if (confirm == 'y') {
                if (stats.gold >= 50) {
                    stats.gold -= 50;
                    inventory.equippedArmor = a;
                    std::cout << "Zakoupil jsi: " << a.getName() << " za 50 zlaákù.\n";
                }
                else {
                    std::cout << "Nemáš dost zlata (" << stats.gold << "/50).\n";
                }
            }
            else {
                std::cout << "Nákup zrušen.\n";
            }
        }


        showShop();
        handlePurchase(inventory, stats);
    }
    else if (volba == 5) {
        upgradeItem(inventory, stats);
        showShop();
        handlePurchase(inventory, stats);
    }
    else if (volba == 0) {
        std::cout << "Odcházíš z obchodu.\n";
        return;
    }
    else {
        std::cout << "Neplatná volba. Zkus to znovu.\n";
        showShop();
        handlePurchase(inventory, stats);
    }
}



void Shop::upgradeItem(PlayerInventory& inventory, PlayerStats& stats) {
    if (!inventory.equippedWeapon) {
        std::cout << "Nemáš žádnou nasazenou zbraò!\n";
        return;
    }

    Weapon current = *inventory.equippedWeapon;
    int currentLevel = current.getLevel();
    if (currentLevel >= 9) {
        std::cout << "Zbraò je již na maximální úrovni!\n";
        return;
    }

    int cost = (currentLevel + 1) * 10;
    if (stats.gold < cost) {
        std::cout << "Nemáš dostatek zlata (" << cost << ")\n";
        return;
    }

    std::cout << "Chceš zlepšit " << current.getName() << " na +" << (currentLevel + 1) << " za " << cost << "g? [y/n]\n";
    char ch;
    std::cin >> ch;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    if (ch == 'y' || ch == 'Y') {
        stats.gold -= cost;
        bool success = rand() % 2 == 0;
        if (success) {
            Weapon upgraded(current.getName().substr(0, current.getName().find(" +")), current.getDamage() / (1 + 0.1 * currentLevel), currentLevel + 1);
            inventory.equippedWeapon = upgraded;
            std::cout << "Vylepšení úspìšné! Nyní máš " << upgraded.getName() << "\n";
        }
        else {
            std::cout << "Vylepšení se nezdaøilo.\n";
        }
    }
}


