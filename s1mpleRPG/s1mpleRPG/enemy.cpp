#include "Enemy.h"
#include <cstdlib>

void Enemy::takeDamage(int dmg) {
    hp -= dmg;
    if (hp < 0) hp = 0;
}


Enemy::Enemy(EnemyType type) : type(type) {
    int baseArmor = rand() % 10 + 1;
    int baseDamage = rand() % 21 + 10;
    int baseHP = 10;

    int multiplier = 1;

    switch (type) {
    case EnemyType::Normal: multiplier = 1; break;
    case EnemyType::Elite: multiplier = 3; break;
    case EnemyType::Boss: multiplier = 10; break;
    }

    armor = baseArmor * multiplier;
    damage = baseDamage * multiplier;
    hp = baseHP * multiplier;

    xpReward = 25 * multiplier;
    goldMin = 10 * multiplier;
    goldMax = 80 * multiplier;
}