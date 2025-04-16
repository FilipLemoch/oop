#include <iostream>
#include "Map.h"

void showMenu() {
    std::cout << "==== MENU ====\n";
    std::cout << "1. Hrat hru\n";
    std::cout << "2. Zobrazit mapu\n";
    std::cout << "3. Inventar (zatím neimplementovano)\n";
    std::cout << "4. Konec\n";
    std::cout << "Vyber: ";
}

int main() {
    Map gameMap;
    char input;

    while (true) {
        showMenu();
        std::cin >> input;

        if (input == '1') {
            while (true) {
                gameMap.drawMap();
                std::cout << "Pohyb: [W] Nahoru, [S] Dolu, [A] Vlevo, [D] Vpravo, [Q] Zpet do menu\n";
                std::cin >> input;

                if (input == 'q') break;
                gameMap.movePlayer(input);
            }
        }
        else if (input == '4') {
            std::cout << "Ukoncuji hru...\n";
            break;
        }
    }

    return 0;
}
