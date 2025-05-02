#ifndef NODE_H
#define NODE_H

#include <vector>
#include "TileSprite.h" 

class Node {
public:
    // Constructor to initialize the node with its position and number
    Node(int row, int col, int number, const sf::Texture& sharedTexture);

    // Getters and setters for the node's properties
    int getRow() const;
    int getCol() const;
    int getNumber() const;
    void setNumber(int num);

    // Function to get the combinations of neighbors
    std::vector<std::vector<std::pair<int, int>>> getCombinations() const;

    // Function to get the neighbors of the node
    const std::vector<std::pair<int, int>>& getNeighbors() const;

    // Function to get the neighbors of the node
    void updateView();              // Update the view of the node based on its number        
    ml::Rectangle& getDrawable();   // Get the drawable object of the node
    void setHighlighted(bool on);   // Set the highlighted state of the node

    // Static function to set the board size
    static void setBoardSize(int maxRow, int maxCol);


private:
    int row, col, number;
    std::vector<std::pair<int, int>> neighbors;
    TileSprite tileSprite;
    static int maxRow, maxCol;
};

#endif // NODE_H

