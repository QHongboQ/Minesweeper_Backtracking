#include "BackTracking.h"

BackTracking::BackTracking(Board& board) : board(board), highlighter(board.getRowCount(), board.getColCount()) {}

void BackTracking::initialization() {
    currentRow = currentCol = comboIndex = currentBombIndex = 0;
    clock.restart();
    highlighter = Highlighter(board.getRowCount(), board.getColCount());
    highlighter.highlight(board); // Highlight the first node
    /*
    Get the information of the board
    Go through all the nodes in the board
    If the node is a number node, get the combinations of the node
    If the node is not a number node, go to the next node
    */
    for (int row = 0; row < board.getRowCount(); ++row) {
        for (int col = 0; col < board.getColCount(); ++col) {
            // Get the node
            Node& node = board.getNode(row, col);
            // Check if the node is a number node
            if (node.getNumber() > 0) {
                // If the node is a number node, get the combinations of the node
                combinations = node.getCombinations();
                break;
            }
        }
    }
    if (!combinations.empty()) {
        toAdd = combinations[0];
    }
}

void BackTracking::update() {
    // Sleep 0.5 seconds between each step
    if (clock.getElapsedTime().asSeconds() < 0.5f) return;
    clock.restart();

    int row = highlighter.getRow();
    int col = highlighter.getCol();
    int maxRow = board.getRowCount();
    int maxCol = board.getColCount();

    if (row == maxRow - 1 && col == maxCol - 1) return; // If we are at the last node, do nothing

    advance(); // Move to the next node
  
}

void BackTracking::compareCombinations() {
    toRemove.clear();
    toAdd.clear();

    // If is the first combo, no need to compare or If is the last combo, no need to compare
    if (comboIndex == 0 || comboIndex >= combinations.size()) return;

    // Get the previous and current combinations
    const auto& prevCombo = combinations[comboIndex - 1];
    const auto& currentCombo = combinations[comboIndex];

    // Compare the two combinations
    for (int i = 0; i < currentCombo.size(); ++i) {
        if (prevCombo[i] != currentCombo[i]) {
            toRemove.push_back(prevCombo[i]); // Need to remove the previous one
            toAdd.push_back(currentCombo[i]); // Need to add the current one
        }
    }
}

void BackTracking::advance() {
    int row = highlighter.getRow();
    int col = highlighter.getCol();

    if (board.getNode(row, col).getNumber() > 0) {
        move(); // 跳过数字格子
        return;
    }
    
    // If we have to remove a node, go into the function
    if (!toRemove.empty()) {
        auto [removeRowIndex, removeColIndex] = toRemove.back();

        if (row == removeRowIndex && col == removeColIndex) {
            board.getNode(row, col).setNumber(0);
            toRemove.pop_back();
        } else {
            move();
        }
    }
    // If we have to add a node, go into the function
    else if (!toAdd.empty()) {
        auto [removeRowIndex, removeColIndex] = toAdd.back();

        if (row == removeRowIndex && col == removeColIndex) {
            board.getNode(row, col).setNumber(-1);
            toAdd.pop_back();
        } else {
            move();
        }
    }
    else {
        ++comboIndex;
        if (comboIndex < combinations.size()) {
            compareCombinations();
        }
        move();
    }
}


void BackTracking::move() {
    highlighter.removeHighlight(board);
    highlighter.moveNextSkippingNumber(board);
    highlighter.highlight(board);
}