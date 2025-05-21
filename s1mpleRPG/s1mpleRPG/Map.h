#ifndef MAP_H
#define MAP_H

#include <vector>
#include "WeaponSystem.h"
#include "PlayerStats.h"
#include "Enemy.h"

class Map {
private:
    static const int MAP_SIZE = 10;
    std::vector<std::vector<char>> grid;
    std::vector<std::vector<bool>> revealed;
    int playerX, playerY;
    bool shopPlaced;

    void revealSurroundings();

public:
    Map();
    void drawMap() const;

    bool movePlayer(char direction, PlayerInventory& inventory, PlayerStats& stats);

    bool startCombat(PlayerInventory& inventory, PlayerStats& stats);
    bool startCombat(PlayerInventory& inventory, PlayerStats& stats, EnemyType forcedType);

    int getPlayerX() const { return playerX; }
    int getPlayerY() const { return playerY; }
};

#endif
