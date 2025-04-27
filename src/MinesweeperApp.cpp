#include "MinesweeperApp.h"

MinesweeperApp::MinesweeperApp(const sf::Texture& sharedTexture)
    : ml::Application(720, 420, 32, "Minesweeper App"), board(3, 3, sharedTexture), backtracking(board)
{}

void MinesweeperApp::initialization() {
    float cellWidth = 100.f;
    float cellHeight = 100.f;

    // Draw the board
    for (int row = 0; row < board.getRowCount(); ++row) {
        for (int col = 0; col < board.getColCount(); ++col) {
            auto& drawable = board.getNode(row, col).getDrawable();
            drawable.setPosition(sf::Vector2<float>(col * cellWidth, row * cellHeight));
            addComponent(drawable); // Add the drawable to the application
        }
    }

    backtracking.initialization();
    this->onUpdate([this]() { this->update(); });
}

void MinesweeperApp::registerEvents() {
    // An click event test
    // Go through all the nodes and register the click event
        for (int r = 0; r < board.getRowCount(); ++r) {
            for (int c = 0; c < board.getColCount(); ++c) {
                // Get the node and register the click event
                auto& node = board.getNode(r, c);
                // Lambda function to handle the click event
                node.getDrawable().onClick([&node]() {
                    if (node.getNumber() <= 0)
                        node.setNumber(-6); 
                });
            }
        }
}

void MinesweeperApp::update() {
    backtracking.update();
}
