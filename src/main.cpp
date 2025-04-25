#include <SFML/Graphics.hpp>
#include "MinesweeperApp.h"

int main() {
    sf::Texture sharedTexture;
    if (!sharedTexture.loadFromFile("C:/NoSystemFile/Hongbo/VSProject/Minesweeper_Backtracking/Image/minesweep_cut.png")) {
        std::cerr << "Failed to load texture!" << std::endl;
        return 1;
    }
    MinesweeperApp app(sharedTexture);
    app.run();
    
    return 0;
}
