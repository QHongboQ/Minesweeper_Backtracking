#ifndef BOARD_H
#define BOARD_H

#include "Node.h"
#include <vector>

class Board{
public:
    Board(int rows, int cols, const sf::Texture& sharedTexture);


    Node& getNode(int row, int col);
    void setNodeNumber(int row, int col, int number);

    int getRowCount() const;
    int getColCount() const;

    void setBombState(const std::vector<std::pair<int, int>>& newState);
    const std::vector<std::pair<int, int>>& getBombState() const;

private:
    int rows, cols;
    std::vector<std::vector<Node>> grid;

    std::vector<std::pair<int, int>> currentBombState;
};


#endif // BOARD_H