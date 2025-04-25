// BackTracking.h
#ifndef BACKTRACKING_H
#define BACKTRACKING_H

#include "Board.h"
#include <vector>
#include <SFML/System.hpp>
#include <algorithm>

class BackTracking {
public:
    BackTracking(Board& board);
    void start();
    void update();  // 每帧调用，推动一步逻辑

private:
    Board& board;
    int currentRow;
    int currentCol;
    int comboIndex;
    int currentNeighborIndex;

    std::vector<std::vector<std::pair<int, int>>> combinations;
    std::vector<std::pair<int, int>> currentCombo;
    std::vector<std::pair<int, int>> toRemove;
    int removeIndex;

    sf::Clock clock;
    bool removing = false;

    void advanceToNextNumberTile();

};

#endif // BACKTRACKING_H