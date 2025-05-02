#ifndef HIGHLIGHTER_H
#define HIGHLIGHTER_H

#include <SFML/System.hpp>
#include <vector>
#include "Board.h"

class Highlighter {
public:
    explicit Highlighter(Board& board);

    // movement functions
    void moveNext();
    void movePrev();
    void update();

    // highlight functions
    void highlight() const;
    void removeHighlight() const;

    // Current state functions
    int getRow() const;
    int getCol() const;
    bool stepToTarget(std::pair<int, int> target, float delay);
    bool waitSeconds(float seconds);

    // Loading script functions
    void loadScript(
        const std::vector<std::pair<int, int>>& steps,
        const std::vector<std::vector<std::pair<int, int>>>& flags
    );

    // Control functions
    void inverseFlag(int r, int c);


private:
    int index; // Index of the current number node
    sf::Clock timer;

    Board& board;
    std::vector<std::pair<int, int>> numberCoords;

    // Animated script
    std::vector<std::pair<int, int>> stepScript;
    std::vector<std::vector<std::pair<int, int>>> flagScript;
    int currentStepIndex = 0;
    int currentFlagIndex = 0;
    bool inFlagPhase = false;
};

#endif // HIGHLIGHTER_H