#include "Board.h"

Board::Board(int rows, int cols, const sf::Texture& sharedTexture)
    : rows(rows), cols(cols)
{
    // Initialize the grid with the given number of rows and columns
    grid.resize(rows);
    for (int row = 0; row < rows; ++row) {
        grid[row].reserve(cols);
        for (int column = 0; column < cols; ++column) {
            // Set every node to 0
            grid[row].emplace_back(row, column, 0, sharedTexture);
        }
    }

    // Set the center node to 5
    if (rows > 0 && cols > 0)
        grid[rows / 2][cols / 2].setNumber(5);
}

Node& Board::getNode(int row, int col) {
    return grid[row][col];
}

int Board::getRowCount() const { return rows; }
int Board::getColCount() const { return cols; }


const Node& Board::getNode(int row, int col) const {
    return grid[row][col];
}