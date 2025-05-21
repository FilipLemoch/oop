#include <cstdlib> // rand
#include <ctime>   // time

void Map::revealSurroundings() {
    srand(static_cast<unsigned>(time(nullptr)));

    for (int dy = -1; dy <= 1; ++dy) {
        for (int dx = -1; dx <= 1; ++dx) {
            int x = playerX + dx;
            int y = playerY + dy;
            if (x >= 0 && y >= 0 && x < MAP_SIZE && y < MAP_SIZE) {
                if (!revealed[y][x]) {
                    revealed[y][x] = true;

                    // jen prázdná místa mùžou mít nìco
                    if (grid[y][x] == ' ') {
                        int roll = rand() % 100;

                        if (!shopPlaced && roll < 1) {        // 1% šance na shop
                            grid[y][x] = 'S';
                            shopPlaced = true;
                        }
                        else if (roll < 6) {                  // 5% dungeon
                            grid[y][x] = 'D';
                        }
                        else if (roll < 8) {                  // 2% encounter
                            grid[y][x] = 'C';
                        }
                    }
                }
            }
        }
    }
}
