#include "LevelSystem.h"
#include <iostream>

void levelUp(PlayerStats& stats) {
    stats.level++;
    stats.xp = 0;
    stats.xpToNext = static_cast<int>(stats.xpToNext * 1.05);
    std::cout << "\n*** LEVEL UP! Jsi nyní level " << stats.level << " ***\n";
    std::cout << "[1] +5% DMG\n[2] +5% HP\n[3] +5% Crit šance\nVyber bonus: ";
    int volba;
    std::cin >> volba;

    switch (volba) {
    case 1: stats.bonusDMG *= 1.05; break;
    case 2: stats.baseHP = static_cast<int>(stats.baseHP * 1.05); stats.currentHP = stats.baseHP; break;
    case 3: stats.bonusCritChance += 0.05; break;
    default: std::cout << "Neplatná volba.\n"; break;
    }
}
