// BackTracking.cpp
#include "BackTracking.h"


// Constructor to initialize the BackTracking object with a reference to the board
BackTracking::BackTracking(Board& board)
    : board(board), foundSolution(false) {}


// Function to initialize the backtracking process
// This function clears the previous steps and flags, updates the board state, and starts the backtracking process
void BackTracking::initialization() {
    step.clear();
    flagStep.clear();
    currentlyFlagged.clear();
    foundSolution = false;

    updateBoardState(); // Update the board state to get all number nodes
    backtrack(0);       // Start the backtracking process
}


// Function to get the steps taken during backtracking
const std::vector<std::pair<int, int>>& BackTracking::getSteps() const {
    return step;
}


// Function to get the flags set during backtracking
const std::vector<std::vector<std::pair<int, int>>>& BackTracking::getFlags() const {
    return flagStep;
}


// Function to update the board state based on the current step
void BackTracking::updateBoardState() {
    allNumberNodes.clear();                                 // Clear the previous number nodes
    for (int row = 0; row < board.getMaxRow(); ++row) {     // Iterate through all rows
        for (int col = 0; col < board.getMaxCol(); ++col) { // Iterate through all columns
            if (board.getNode(row, col).getNumber() > 0) {  // If the node is a number node
                allNumberNodes.emplace_back(row, col);      // Add it to the list of number nodes
            }
        }
    }
}


/*
    * This function performs backtracking to find a solution for the Minesweeper board.
    * It recursively explores all possible combinations of flagged neighbors for each number node.
    * If a valid combination is found, it updates the board state and continues to the next number node.
    * If a solution is found, it sets the foundSolution flag to true and returns.
*/
void BackTracking::backtrack(int index) {
    // Base case: if all number nodes have been processed, check if the board is valid
    // If the board is valid, set the foundSolution flag to true
    if (index >= allNumberNodes.size()) {
        if (validateBoard()) {
            foundSolution = true;
        }
        return;
    }

    // Other stop condition: if a solution has already been found, return
    if (foundSolution) return;

    // Get the current number node and its properties
    auto [row, col] = allNumberNodes[index];
    auto& node = board.getNode(row, col);
    int number = node.getNumber();
    auto combinations = node.getCombinations();

    // Count the number of already flagged neighbors for the first combination
    int existingFlags = 0;
    for (const auto& coord : combinations[0]) {             // Check the first combination of neighbors
        if (currentlyFlagged.count(coord)) ++existingFlags; // If the neighbor is flagged, increment the count
    }

    // If the number of already flagged neighbors is greater than the number on the node, return
    if (existingFlags > number) return;

    // If the number of already flagged neighbors is equal to the number on the node, continue to the next number node
    if (existingFlags == number) {
        step.push_back({row, col}); // Add the current number node to the step vector
        flagStep.push_back({});     // Add an empty vector to the flagStep vector
        backtrack(index + 1);       // Continue to the next number node(Recursive call)
        return;                     // Return to the previous state
    }

    int flagsNeeded = number - existingFlags;           // Calculate the number of flags needed for the current number node

    for (const auto& combo : combinations) {        // Check if the current combination of neighbors is valid
        std::vector<std::pair<int, int>> toAdd;     // Vector to store the coordinates of the neighbors to be flagged
        bool valid = true;                          // Flag to indicate if the combination is valid
        int countAlreadyFlagged = 0;                // Count the number of already flagged neighbors in the current combination

        for (const auto& coord : combo) {           // Iterate through the coordinates of the neighbors in the current combination
            // If it is already flagged, increment the countAlreadyFlagged and continue to the next coordinate
            if (currentlyFlagged.count(coord)) {  
                ++countAlreadyFlagged;
                continue;
            }

            // If the neighbor is already a number or not safe to flag, set valid to false and break the loop
            auto& neighbor = board.getNode(coord.first, coord.second);
            if (neighbor.getNumber() != 0 || !isSafeToFlag(coord.first, coord.second)) {
                valid = false;
                break;
            }

            toAdd.push_back(coord); // Add the coordinate to the toAdd vector
        }

        // If the combination is not valid or the number of flags does not match, continue to the next combination
        if (!valid || countAlreadyFlagged + toAdd.size() != number) continue;   

        step.push_back({row, col}); // Add the current number node to the step vector
        flagStep.push_back(toAdd);  // Add the coordinates to be flagged to the flagStep vector

        for (const auto& coord : toAdd) {    // Iterate through the coordinates to be flagged
            currentlyFlagged.insert(coord);  // Flag the coordinate
        }

        backtrack(index + 1);                // Continue to the next number node(Recursive call)
        if (foundSolution) return;           // If a solution is found, return

        step.push_back({row, col});          // Add the current number node to the step vector again
        flagStep.push_back(toAdd);           // Add the coordinates to be flagged to the flagStep vector again

        for (const auto& coord : toAdd) {     // Iterate through the coordinates to be unflagged
            currentlyFlagged.erase(coord);    // Unflag the coordinate
        }
    }

    // If no valid combination is found, continue to the next number node
    step.push_back({row, col});
    flagStep.push_back({});
}


/*
    * This function checks if the number of flagged neighbors for each number node matches the number on the node.
    * If any number node has an incorrect number of flagged neighbors, the function returns false.
    * If all number nodes are valid, the function returns true.
*/
bool BackTracking::validateBoard() const {
    for (const auto& [row, col] : allNumberNodes) {         // Iterate through all number nodes
        int number = board.getNode(row, col).getNumber();   // Get the number of the node
        int count = 0;                                      // Initialize the count of flagged neighbors
        for (int dr = -1; dr <= 1; ++dr) {                  // Iterate through the neighbors
            for (int dc = -1; dc <= 1; ++dc) {              // Check all 8 directions
                int nr = row + dr, nc = col + dc;           // Calculate the neighbor's position
                if (nr < 0 || nr >= board.getMaxRow() || nc < 0 || nc >= board.getMaxCol()) continue;   // Skip out-of-bounds neighbors
                if (currentlyFlagged.count({nr, nc})) ++count;  // If the neighbor is flagged, increment the count
            }
        }
        if (count != number) return false;                      // If the count does not match the number, return false
    }
    return true;                                                // If all number nodes are valid, return true
}


/*
    * This function checks if it is safe to flag a node at the specified position.
    * It iterates through all neighbors of the node and checks if the number of flagged neighbors exceeds the number on the neighbor
*/
bool BackTracking::isSafeToFlag(int r, int c) {
    for (int dr = -1; dr <= 1; ++dr) {           // Iterate through the neighbors
        for (int dc = -1; dc <= 1; ++dc) {       // Check all 8 directions
            int nr = r + dr, nc = c + dc;        // Calculate the neighbor's position

            // Skip out-of-bounds neighbors
            if (nr < 0 || nr >= board.getMaxRow() || nc < 0 || nc >= board.getMaxCol()) continue;  

            // Skip the center node (0, 0) which is the current node
            if (nr == r && nc == c) continue;

            const auto& neighbor = board.getNode(nr, nc);   // Get the neighbor node
            int number = neighbor.getNumber();  // Get the number of the neighbor node
            // If the neighbor is not a number, continue to the next neighbor
            if (number <= 0) continue;

            int flagCount = 0;                          // Initialize the count of flagged neighbors
            for (int rr = -1; rr <= 1; ++rr) {          // Iterate through the neighbors of the neighbor node
                for (int cc = -1; cc <= 1; ++cc) {      // Check all 8 directions
                    int rrn = nr + rr, ccn = nc + cc;   // Calculate the neighbor's position

                    // Skip out-of-bounds neighbors
                    if (rrn < 0 || rrn >= board.getMaxRow() || ccn < 0 || ccn >= board.getMaxCol()) continue;   

                    // If the neighbor is flagged, increment the count
                    if (currentlyFlagged.count({rrn, ccn}) || (rrn == r && ccn == c)) ++flagCount;  
                }
            }
            // If the count exceeds the number, return false
            if (flagCount > number) return false;   
        }
    }
    // If all neighbors are valid, return true
    return true;
}