#include "MinesweeperApp.h"

MinesweeperApp::MinesweeperApp(const sf::Texture& sharedTexture)
    : ml::Application(720, 420, 32, "Minesweeper App"), board(3, 3, sharedTexture), backtracking(board)
{}

void MinesweeperApp::initialization() {
    float cellWidth = 100.f;
    float cellHeight = 100.f;

    for (int r = 0; r < board.getRowCount(); ++r) {
        for (int c = 0; c < board.getColCount(); ++c) {
            auto& drawable = board.getNode(r, c).getDrawable();
            drawable.setPosition(sf::Vector2<float>(c * cellWidth, r * cellHeight));
            addComponent(drawable); // ✨关键：将图块添加到应用中
        }
    }

    backtracking.initialization();
    this->onUpdate([this]() { this->update(); });
}

void MinesweeperApp::registerEvents() {
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
