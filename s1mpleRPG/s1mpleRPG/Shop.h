#pragma once

#include <vector>
#include <variant>
#include <string>
#include "WeaponSystem.h"
#include "PlayerStats.h"

class Shop {
public:
    struct ShopItem {
        std::variant<Weapon, Armor> item;
    };

    Shop();

    void generateShopItems();
    void showShop() const;
    void handlePurchase(PlayerInventory& inventory, PlayerStats& stats);
    void upgradeItem(PlayerInventory& inventory, PlayerStats& stats);

private:
    std::vector<ShopItem> items;
};

