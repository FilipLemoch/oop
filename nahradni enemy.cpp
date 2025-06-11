#include "Enemy.h"


class EnemyImpl {
protected:
    int armor;
    int damage;
    int hp;
    int xpReward;
    int goldMin;
    int goldMax;

public:
    virtual ~EnemyImpl() = default;

    virtual void generateStats() = 0;

    int getArmor() const { return armor; }
    int getDamage() const { return damage; }
    int getHP() const { return hp; }
    int getXPReward() const { return xpReward; }
    int getGoldMin() const { return goldMin; }
    int getGoldMax() const { return goldMax; }
};

class NormalEnemyImpl : public EnemyImpl {
public:
    void generateStats() override {
        armor = rand() % 10 + 1;
        damage = rand() % 21 + 10;
        hp = 10;
        xpReward = 25;
        goldMin = 10;
        goldMax = 80;
    }
};

class EliteEnemyImpl : public EnemyImpl {
public:
    void generateStats() override {
        armor = (rand() % 10 + 1) * 3;
        damage = (rand() % 21 + 10) * 3;
        hp = 10 * 3;
        xpReward = 25 * 3;
        goldMin = 10 * 3;
        goldMax = 80 * 3;
    }
};

class BossEnemyImpl : public EnemyImpl {
public:
    void generateStats() override {
        armor = (rand() % 10 + 1) * 10;
        damage = (rand() % 21 + 10) * 10;
        hp = 10 * 10;
        xpReward = 25 * 10;
        goldMin = 10 * 10;
        goldMax = 80 * 10;
    }
};

Enemy::Enemy(EnemyType type) : type(type) {
    EnemyImpl* impl = nullptr;

    switch (type) {
    case EnemyType::Normal: impl = new NormalEnemyImpl(); break;
    case EnemyType::Elite:  impl = new EliteEnemyImpl(); break;
    case EnemyType::Boss:   impl = new BossEnemyImpl(); break;
    }

    if (impl) {
        impl->generateStats();
        armor = impl->getArmor();
        damage = impl->getDamage();
        hp = impl->getHP();
        xpReward = impl->getXPReward();
        goldMin = impl->getGoldMin();
        goldMax = impl->getGoldMax();
        delete impl;
    }
}

void Enemy::takeDamage(int dmg) {
    hp -= dmg;
    if (hp < 0) hp = 0;
}
