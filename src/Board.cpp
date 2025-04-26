#include "Board.h"

Board::Board(int rows, int cols, const sf::Texture& sharedTexture)
    : rows(rows), cols(cols)
{
    grid.resize(rows);
    for (int row = 0; row < rows; ++row) {
        grid[row].reserve(cols);
        for (int column = 0; column < cols; ++column) {
            // 默认每个格子 number = 0（可以后面手动 set）
            grid[row].emplace_back(row, column, 0, sharedTexture);
        }
    }

    if (rows > 0 && cols > 0)
        grid[rows / 2][cols / 2].setNumber(5);
}

Node& Board::getNode(int row, int col) {
    return grid[row][col];
}

void Board::setNodeNumber(int row, int col, int number) {
    grid[row][col].setNumber(number);
    grid[row][col].updateView();
}


int Board::getRowCount() const { return rows; }
int Board::getColCount() const { return cols; }


void Board::setBombState(const std::vector<std::pair<int, int>>& newState) {
    currentBombState = newState;
}

const std::vector<std::pair<int, int>>& Board::getBombState() const {
    return currentBombState;
}

const Node& Board::getNode(int row, int col) const {
    return grid[row][col]; // 或者其他数据结构
}