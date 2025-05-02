#include "MinesweeperApp.h"


// Constructor to initialize the Minesweeper application with a preset board
MinesweeperApp::MinesweeperApp(int row, int col, const sf::Texture& sharedTexture, const std::vector<std::vector<int>>& preset)
    : ml::Application(row * 100, col * 100, 32, "Minesweeper App"),
    board(row, col, sharedTexture, preset),
    backtracking(board),
    highlighter(board) {}


// Constructor to initialize the Minesweeper application with a random board
MinesweeperApp::MinesweeperApp(int row, int col, int numMines, const sf::Texture& sharedTexture)
    : ml::Application(row * 100, col * 100, 32, "Minesweeper App"),
    board(row, col, numMines, sharedTexture),
    backtracking(board),
    highlighter(board) {}



// Initialization function to set up the application
// This function is called after the application window is created
// and is used to set up the initial state of the application.
void MinesweeperApp::initialization() {
    // Set the board size for the nodes
    for (int row = 0; row < board.getMaxRow(); ++row) {                                     // Loop through all the rows
        for (int col = 0; col < board.getMaxCol(); ++col) {                                 // Loop through all the columns
            auto& drawable = board.getNode(row, col).getDrawable();                         // Get the drawable object of the node
            drawable.setPosition(sf::Vector2<float>(col * cellWidth, row * cellHeight));    // Set the position of the drawable object
            addComponent(static_cast<ml::UIComponent&>(drawable));                          // Add the drawable to the application


        }
    }

    // Register the events for the nodes
    backtracking.initialization();
    highlighter.loadScript(
        backtracking.getSteps(),
        backtracking.getFlags()
    );

    // This line registers an update function that will be called every frame
    this->onUpdate([this]() { this->update(); });
}


// Function to register events for the nodes
// This function is called after the initialization function
void MinesweeperApp::registerEvents() {
    // An click event test
    // Go through all the nodes and register the click event
    for (int r = 0; r < board.getMaxRow(); ++r) {
        for (int c = 0; c < board.getMaxCol(); ++c) {
            auto& node = board.getNode(r, c);
            node.getDrawable().onClick([this, r = r, c = c]() {
                if (board.isMine(r, c)) {
                    board.getNode(r, c).setNumber(-6);  // Mine tile
                } else {
                    board.getNode(r, c).setNumber(-2);  // Blank tile
                }
            });
        }
    }
}


// Function to update the application state
void MinesweeperApp::update() {
    highlighter.update();
}
