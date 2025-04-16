#ifndef MAP_H
#define MAP_H

#include <vector>

class Map {
private:
    static const int MAP_SIZE = 10;
    std::vector<std::vector<char>> grid;
    std::vector<std::vector<bool>> revealed;
    int playerX, playerY;
    bool shopPlaced;

    void revealSurroundings(); // nový helper

public:
    Map();
    void drawMap() const;
    void movePlayer(char direction);
    int getPlayerX() const { return playerX; }
    int getPlayerY() const { return playerY; }
};


#endif
