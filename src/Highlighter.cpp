#include "Highlighter.h"


// Constructor to initialize the Highlighter with a reference to the board
Highlighter::Highlighter(Board& board)
    : board(board), index(0)
{
    /*
    Initialize the highlighter with the board and find all number nodes.
    The number nodes are stored in the numberCoords vector.
    */
    for (int r = 0; r < board.getMaxRow(); ++r) {
        for (int c = 0; c < board.getMaxCol(); ++c) {
            if (board.getNode(r, c).getNumber() > 0) {
                numberCoords.emplace_back(r, c);
            }
        }
    }

    // If there are number nodes, highlight the first one
    if (!numberCoords.empty()) {
        highlight();
    }
}


// test version
void Highlighter::update() {
    // If the current step index is out of bounds, return
    if (currentStepIndex >= stepScript.size()) return;

    /*
    If not in flag phase, check if the current number node has arrived at the target position.
    If it has, print debug information and set the flag phase to true.
    If in flag phase, check if the current flag index is within bounds.
    If it is, wait for a short duration and then inverse the flag at the current position.
    If all flags have been processed, move to the next step and set the flag phase to false.
    */
    if (!inFlagPhase) { // check if in flag phase
        // check if the current number node has arrived at the target position
        if (stepToTarget(stepScript[currentStepIndex], 0.5f)) {
            // print debug information
            std::cout << "Step[" << currentStepIndex << "] at ("
                      << stepScript[currentStepIndex].first << ","
                      << stepScript[currentStepIndex].second << ")";
            if (!flagScript[currentStepIndex].empty()) {
                std::cout << " | Flags:";
                for (const auto& [fr, fc] : flagScript[currentStepIndex]) {
                    std::cout << " (" << fr << "," << fc << ")";
                }
            } else {
                std::cout << " | Flags: (none)";
            }
            std::cout << "\n";

            // After arriving at the target, set the flag phase to true
            // So we can go to the flag phase
            // Reset the current flag index to 0
            inFlagPhase = true;
            currentFlagIndex = 0;
        }
    } else {    // in flag phase
        // check if the current flag index is within bounds
        if (currentFlagIndex < flagScript[currentStepIndex].size()) {
            if (waitSeconds(0.5f)) {
                // wait for a short duration before inverting the flag
                // Inverse the flag at the current position
                auto [r, c] = flagScript[currentStepIndex][currentFlagIndex];
                inverseFlag(r, c);
                ++currentFlagIndex;
            }
        } else {    // all flags have been processed
            // Move to the next step and set the flag phase to false
            // So we can go to the next step
            ++currentStepIndex;
            inFlagPhase = false;
        }
    }
}


// Load the script for the highlighter
// The script consists of a series of steps and flags to be processed in order
void Highlighter::loadScript(
    const std::vector<std::pair<int, int>>& stepPath,
    const std::vector<std::vector<std::pair<int, int>>>& flagPath
) {
    stepScript = stepPath;
    flagScript = flagPath;
    currentStepIndex = 0;
    currentFlagIndex = 0;
    inFlagPhase = false;
    timer.restart();
}


/*
 * Check if the current number node has arrived at the target position.
 * If it has, return true.
 * If not, move to the next number node in the direction of the target.
 * The delay parameter specifies the time interval between moves.
 * The function returns true if the target is reached, false otherwise.
 * */
bool Highlighter::stepToTarget(std::pair<int, int> target, float delay) {
    if (numberCoords.empty()) return false;         // if no number nodes, return false
    if (numberCoords[index] == target) return true; // if already at target, return true

    // find the index of the target in numberCoords
    int targetIndex = -1;
    for (int i = 0; i < numberCoords.size(); ++i) {
        // If the target is found, set the targetIndex and break the loop
        // If the target is not found, set the targetIndex to -1
        if (numberCoords[i] == target) {
            targetIndex = i;
            break;
        }
    }
    if (targetIndex == -1) return false;

    // every 0.5s move to the next node
    if (timer.getElapsedTime().asSeconds() >= delay) {
        timer.restart();
        removeHighlight();
        if (index < targetIndex) {
            ++index;
        } else if (index > targetIndex) {
            --index;
        }
        highlight();
    }
    // check if the current number node has arrived at the target position
    // If it has, return true
    return index == targetIndex;
}


// Wait for a specified number of seconds
bool Highlighter::waitSeconds(float seconds) {
    if (timer.getElapsedTime().asSeconds() >= seconds) {
        timer.restart();
        return true;
    }
    return false;
}


// Highlight the current number node
// This function sets the highlighted state of the current number node to true
void Highlighter::highlight() const {
    auto [r, c] = numberCoords[index];
    board.getNode(r, c).setHighlighted(true);
}


// Remove the highlight from the current number node
// This function sets the highlighted state of the current number node to false
void Highlighter::removeHighlight() const {
    auto [r, c] = numberCoords[index];
    board.getNode(r, c).setHighlighted(false);
}


// Inverse the flag at the specified position
// If the current number is 0, set it to -1 (flagged)
// If the current number is -1, set it to 0 (unflagged)
void Highlighter::inverseFlag(int r, int c) {
    int current = board.getNode(r, c).getNumber();
    if (current == 0) {
        board.getNode(r, c).setNumber(-1);  // Set the number to -1 (flagged)
    } else if (current == -1) {
        board.getNode(r, c).setNumber(0);   // Set the number to 0 (unflagged)
    }
}


// Move to the next number node and highlight it
void Highlighter::moveNext() {
    if (index + 1 < numberCoords.size()) {
        removeHighlight();
        ++index;
        highlight();
    }
}


// Move to the previous number node and highlight it
void Highlighter::movePrev() {
    if (index > 0) {
        removeHighlight();
        --index;
        highlight();
    }
}


// Get the row and column of the current number node
int Highlighter::getRow() const {
    return numberCoords[index].first;
}


// Get the column of the current number node
int Highlighter::getCol() const {
    return numberCoords[index].second;
}