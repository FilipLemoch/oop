#ifndef ENEMY_H
#define ENEMY_H
#include <cstdlib>

enum class EnemyType { Normal, Elite, Boss };

class Enemy {

private:
    int armor;
    int damage;
    int hp;
    int xpReward;
    int goldMin;
    int goldMax;
    EnemyType type;

public:
    Enemy(EnemyType type = EnemyType::Normal);
    int getArmor() const { return armor; }
    int getDamage() const { return damage; }
    int getHP() const { return hp; }
    void takeDamage(int dmg);
    bool isAlive() const { return hp > 0; }
    int getXPReward() const { return xpReward; }
    int getGoldReward() const { return rand() % (goldMax - goldMin + 1) + goldMin; }
};

#endif
