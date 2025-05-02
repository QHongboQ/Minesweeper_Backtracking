#include <SFML/Graphics.hpp>
#include "MinesweeperApp.h"

int main() {
    std::srand(static_cast<unsigned int>(std::time(nullptr)));  // Seed the random number generator

    sf::Texture sharedTexture;  // Create a texture to be shared among all nodes
    if (!sharedTexture.loadFromFile("Image/minesweep_cut.png")) {
        std::cerr << "Failed to load texture!" << std::endl;
        return 1;
    }
    
    // MinesweeperApp app(row, col, sharedTexture, presetVector);
    MinesweeperApp app(5, 5, 5, sharedTexture);    // Create a Minesweeper application with a random board
    
    app.run();
    
    return 0;
}
