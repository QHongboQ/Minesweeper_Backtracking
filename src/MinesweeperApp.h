#ifndef MINESWEEPERAPP_H
#define MINESWEEPERAPP_H

#include <Malena/common.hpp>
#include "Board.h"
#include "BackTracking.h"
#include "Highlighter.h"

class MinesweeperApp : public ml::Application {
public:
    // Constructor to initialize the Minesweeper application with a preset board
    MinesweeperApp(int row, int col, const sf::Texture& sharedTexture, const std::vector<std::vector<int>>& preset);
    // Constructor to initialize the Minesweeper application with a random board
    MinesweeperApp(int rows, int cols, int numMines, const sf::Texture& texture);

    void initialization() override;
    void registerEvents() override;
    void update();

    
private:
    sf::Texture sharedTexture;
    Board board;
    BackTracking backtracking;
    Highlighter highlighter;
    float cellWidth = 100.f;
    float cellHeight = 100.f;
};
    

#endif // MINESWEEPERAPP_H