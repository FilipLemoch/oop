#pragma once
#include <string>
#include <vector>
#include <optional>
#include <memory>

enum class ArmorType { Light, Medium, Heavy };

class Weapon {
    std::string name;
    int baseDamage;
    int level;

public:
    Weapon(std::string name, int baseDamage, int level)
        : name(name), baseDamage(baseDamage), level(level) {}

    std::string getName() const {
        return name + " +" + std::to_string(level);
    }

    int getDamage() const {
        return static_cast<int>(baseDamage * (1 + 0.1 * level));
    }

    int getLevel() const { return level; }

};

class Armor {
    std::string name;
    int armorValue;
    ArmorType type;

public:
    Armor(std::string name, int armorValue, ArmorType type)
        : name(name), armorValue(armorValue), type(type) {}

    std::string getName() const { return name; }
    int getArmor() const { return armorValue; }
    ArmorType getType() const { return type; }
};

struct PlayerInventory {
    std::vector<Weapon> weapons;
    std::optional<Weapon> equippedWeapon;
    Armor equippedArmor = Armor("Cloth Armor", 0, ArmorType::Light);
    bool hasShield = false;
};
