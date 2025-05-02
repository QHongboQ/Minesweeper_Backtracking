#include "Board.h"

// Constructor to initialize the board with a preset grid
Board::Board(int rows, int cols, const sf::Texture& sharedTexture, const std::vector<std::vector<int>>& preset)
    : maxRow(rows), maxCol(cols)
{
    // Set the board size for the nodes
    Node::setBoardSize(rows, cols);

    // Initialize the grid with the given number of rows and columns
    grid.resize(rows);
    for (int row = 0; row < rows; ++row) {
        grid[row].reserve(cols);
        for (int column = 0; column < cols; ++column) {
            // Set every node to 0
            grid[row].emplace_back(row, column, 0, sharedTexture);
        }
    }

    // Set the preset values in the grid
    for (int row = 0; row < rows; ++row) {
        for (int col = 0; col < cols; ++col) {
            grid[row][col].setNumber(preset[row][col]);
        }
    }
}

// Constructor to initialize the board with a random grid
Board::Board(int rows, int cols, int numMines, const sf::Texture& sharedTexture)
    : maxRow(rows), maxCol(cols)
{
    // Set the board size for the nodes
    Node::setBoardSize(rows, cols);

    // initialize the grid with the given number of rows and columns
    grid.resize(rows);
    for (int row = 0; row < rows; ++row) {
        grid[row].reserve(cols);
        for (int col = 0; col < cols; ++col) {
            grid[row].emplace_back(row, col, 0, sharedTexture);
        }
    }

    // place mines randomly
    placeMinesRandomly(numMines);

    // calculate numbers around mines
    calculateNumbers();
}

// Get the node at the specified row and column
Node& Board::getNode(int row, int col) {
    return grid[row][col];
}

// Get the maximum row and column size
int Board::getMaxRow() const { return maxRow; }
int Board::getMaxCol() const { return maxCol; }


// Randomly place mines on the board
// This function takes the number of mines as an argument and places them randomly on the board.
// It also updates the minePositions set with the positions of the mines.
// The function uses a set to ensure that no two mines are placed in the same position.
void Board::placeMinesRandomly(int numMines) {
    // Initialize a set to store mine positions
    // The set will automatically handle duplicates
    std::set<std::pair<int, int>> placed;

    // Randomly place mines until the desired number is reached
    // The while loop continues until the size of the set is equal to the number of mines
    while (placed.size() < numMines) {
        int r = std::rand() % maxRow;   // Generate random row index
        int c = std::rand() % maxCol;   // Generate random row and column indices
        placed.insert({r, c});          // Insert the position into the set
    }

    minePositions = placed; // Store mine positions for later use
}


// Calculate the number of mines around each node
// This function iterates through each node in the grid and counts the number of mines in its neighbors.
// It updates the number of mines for each node accordingly.
// The function uses a nested loop to check the neighbors of each node and increments the count if a mine is found.
// The neighbors are determined by checking the positions in a 3x3 grid around the current node.
// The function skips nodes that are mines themselves by checking the minePositions set.
void Board::calculateNumbers() {
    for (int row = 0; row < maxRow; ++row) {                // Iterate through each row
        for (int col = 0; col < maxCol; ++col) {            // Iterate through each column
            if (minePositions.count({row, col})) continue;  // Skip if the node is a mine

            int count = 0;                                                  // Count the number of mines around this node
            for (int dr = -1; dr <= 1; ++dr) {                              // Iterate through the rows of the neighbors
                for (int dc = -1; dc <= 1; ++dc) {                          // Iterate through the columns of the neighbors
                    if (dr == 0 && dc == 0) continue;                       // Skip the center node (0, 0) which is the current node
                    int nr = row + dr;                                      // Calculate the row of the neighbor
                    int nc = col + dc;                                      // Calculate the column of the neighbor
                    if (nr >= 0 && nr < maxRow && nc >= 0 && nc < maxCol) { // Check if the neighbor is within bounds
                        if (minePositions.count({nr, nc})) ++count;         // If the neighbor is a mine, increment the count
                    }
                }
            }

            grid[row][col].setNumber(count); // Set the number of mines around this node
        }
    }
}


// Check if the specified position is a mine
bool Board::isMine(int row, int col) const {
    return minePositions.count({row, col}) > 0;
}
