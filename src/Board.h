#ifndef BOARD_H
#define BOARD_H

#include "Node.h"
#include <vector>
#include <set>


class Board{
public:
    // Constructor to initialize the board with a preset grid
    Board(int maxRow, int maxCol, const sf::Texture& sharedTexture,const std::vector<std::vector<int>>& preset);

    // Constructor to initialize the board with a random grid
    Board(int maxRow, int maxCol, int numMines, const sf::Texture& sharedTexture);

    // Getter for nod
    Node& getNode(int row, int col);
    
    // Getters for the maximum row and column size
    int getMaxRow() const;
    int getMaxCol() const;

    bool isMine(int row, int col) const;


private:
    int maxRow, maxCol;
    std::vector<std::vector<Node>> grid;

    // Function to place mines randomly on the board
    // This function takes the number of mines as an argument
    // and places them randomly on the board.
    // It also updates the minePositions set with the positions of the mines.
    void placeMinesRandomly(int numMines);
    void calculateNumbers();
    std::set<std::pair<int, int>> minePositions;    // Store mine positions for later use

};


#endif // BOARD_H