#include "Node.h"

Node::Node(int row, int col, int number, const sf::Texture& sharedTexture)
    : row(row), col(col), number(number),tileSprite(sharedTexture)
{
    /*
    Initialize the nighbors of the node.
    The neighbors should be
    (-1, -1),   (-1, 0),  (-1, 1),
    (0, -1),          ,   (0, 1),
    (1, -1),    (1, 0),   (1, 1)
    */

    // Store the coordinates of the neighbors in a 2D grid
    for (int index_row = -1; index_row <= 1; ++index_row) {

        // Skip the center node (0, 0) which is the current node
        for (int index_column = -1; index_column <= 1; ++index_column) {

            // Skip the center node (0, 0) which is the current node
            if (index_row == 0 && index_column == 0) continue;

            // Calculate the row and column of the neighbor
            int final_row = row + index_row;

            // Calculate the column of the neighbor
            int final_column = col + index_column;

            // Check if the neighbor is within bounds
            // When the node is in a boundary
            // Then the neighbor is not out of bounds
            if (final_row >= 0 && final_row < 3 && final_column >= 0 && final_column < 3) {
                // If everything is ok, push the neighbor into the vector
                neighbors.push_back({final_row, final_column});
            }
        }
    }
}


int Node::getRow() const {return row;}

int Node::getCol() const {return col;}

int Node::getNumber() const {return number;}

void Node::setNumber(int num) 
{
    number = num;
    updateView();
}


std::vector<std::vector<std::pair<int, int>>> Node::getCombinations() const{
    // 3D vector,
    // 1D: Index of the neighbors
    // 2D: One combo of posible bombs
    // 3D: All the combos of bombs

    std::vector<std::vector<std::pair<int, int>>> allCombos;
    std::vector<std::pair<int, int>> currentCombo;

    // Recursive backtracking function to generate combinations
    // Lambda function to generate combinations
    // Input: index of the current neighbor, number of bombs left
    std::function<void(int, int)> backtrack = [&](int index, int bombsLeft) {
        // When all bombs set, we can push the current combo into the allCombos vector
        if (bombsLeft == 0) {
            allCombos.push_back(currentCombo);
            return;
        }
        // When all neighbors are checked, we can return
        if (index >= neighbors.size()) return;

        // Select the current neighbor
        // Check if the current neighbor is already selected
        // If the current neighbor is already selected, we can skip it
        // If the current neighbor is not selected, we can select it
        currentCombo.push_back(neighbors[index]);   // Try to put a bomb in the current neighbor
        backtrack(index + 1, bombsLeft - 1);    // When we put a bomb in the current neighbor, we can go to the next neighbor
        currentCombo.pop_back();    // Backtrack to the previous state

        // skip the current neighbor
        backtrack(index + 1, bombsLeft);
    };

    // Check if the number of bombs is valid
    if (number >= 0 && number <= neighbors.size()) {
        backtrack(0, number);
    }

    return allCombos;
   
}


void Node::updateView() {
    if (number == 0)
        tileSprite.setByGrid(0, 0);
    else if (number == -1)
        tileSprite.setByGrid(0, 2);
    else if(number == 5)
        tileSprite.setByGrid(1, 4);
    else if (number == -6)
        tileSprite.setByGrid(0, 6);
}

ml::Rectangle& Node::getDrawable() {
    return tileSprite;
}

void Node::setHighlighted(bool on) {
    if (on) {
        tileSprite.setFillColor(sf::Color::Yellow);

    } else {
        tileSprite.setFillColor(sf::Color::White);
    }
}