// BackTracking.h
#ifndef BACKTRACKING_H
#define BACKTRACKING_H

#include "Board.h"
#include <utility> // for std::pair
#include "Highlighter.h"

class BackTracking {
public:
    BackTracking(Board& board);
    void initialization();
    void update();

private:
    Board& board;
    int comboIndex;
    bool finished = false;

    std::vector<std::vector<std::pair<int, int>>> combinations;

    void compareCombinations();
    std::vector<std::pair<int, int>> toRemove;
    std::vector<std::pair<int, int>> toAdd;
    void advance();
    void move();
    void movePrev();

    Highlighter highlighter;
    sf::Clock clock;
};

#endif // BACKTRACKING_H