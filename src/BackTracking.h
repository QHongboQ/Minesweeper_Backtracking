#ifndef BACKTRACKING_H
#define BACKTRACKING_H

#include "Board.h"
#include <vector>
#include <set>

class BackTracking {
public:
    BackTracking(Board& board); // Constructor to initialize the BackTracking object with a reference to the board

    void initialization();                                                   // Function to initialize the backtracking process
    const std::vector<std::pair<int, int>>& getSteps() const;                // Function to get the steps taken during backtracking
    const std::vector<std::vector<std::pair<int, int>>>& getFlags() const;  // Function to get the flags set during backtracking


private:
    Board& board;

    std::vector<std::pair<int, int>> allNumberNodes;  // Vector to store all number nodes
    std::set<std::pair<int, int>> currentlyFlagged;   // Set to store currently flagged nodes

    std::vector<std::pair<int, int>> step;                  // Vector to store the steps taken during backtracking
    std::vector<std::vector<std::pair<int, int>>> flagStep; // Vector to store the flags set during backtracking

    bool foundSolution;                                     // Flag to indicate if a solution was found

    void updateBoardState();              // Function to update the board state based on the current step
    void backtrack(int index);            // Recursive function to perform backtracking
    bool validateBoard() const;           // Function to validate the current board state
    bool isSafeToFlag(int r, int c);      // Function to check if it is safe to flag a node
};

#endif // BACKTRACKING_H