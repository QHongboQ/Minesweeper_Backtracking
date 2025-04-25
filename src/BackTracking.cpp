#include "BackTracking.h"

BackTracking::BackTracking(Board& board) : board(board) {}

void BackTracking::start() {
    currentRow = currentCol = comboIndex = currentNeighborIndex = 0;
    removing = false;
    clock.restart();
}

void BackTracking::advanceToNextNumberTile() {
    // Get the boundary of the board
    int rowCount = board.getRowCount();
    int colCount = board.getColCount();

    // When we are in the boundary
    while (currentRow < rowCount) {
        while (currentCol < colCount) {
            // Get the current node
            Node& node = board.getNode(currentRow, currentCol);

            if (node.getNumber() > 0) {
                combinations = node.getCombinations();
                comboIndex = 0;
                currentNeighborIndex = 0;
                return;
            }
            ++currentCol;
        }
        currentCol = 0;
        ++currentRow;
    }
    combinations.clear();
}

void BackTracking::update() {
    // Sleep for 1 second to simulate the delay
    if (clock.getElapsedTime().asSeconds() < 0.5f) return;
    clock.restart();

    if (comboIndex >= combinations.size()) {
        advanceToNextNumberTile();
        return;
    }


    Node& numberNode = board.getNode(currentRow, currentCol);
    // numberNode.setHighlighted(false);
    const auto& currentCombo = combinations[comboIndex];

    if (removing) {
        for (const auto& [r, c] : currentCombo) {
            board.getNode(r, c).setNumber(0);
        }
    
        removing = false;
        ++comboIndex;
        currentNeighborIndex = 0;
        return;
    }

    if (currentNeighborIndex < currentCombo.size()) {
        const auto& [r, c] = currentCombo[currentNeighborIndex];
    
        // 取消上一个高亮（如果不是第一次）
        if (currentNeighborIndex > 0) {
            const auto& [prevR, prevC] = currentCombo[currentNeighborIndex - 1];
            board.getNode(prevR, prevC).setHighlighted(false);
        }
    
        board.getNode(r, c).setHighlighted(true);
        board.getNode(r, c).setNumber(-1);
        ++currentNeighborIndex;
    } else {
        // 清除最后一个高亮（最后一次设置完）
        if (!currentCombo.empty()) {
            const auto& [lastR, lastC] = currentCombo.back();
            board.getNode(lastR, lastC).setHighlighted(false);
        }
    
        currentNeighborIndex = 0;
        removing = true;
    }
    
}