#ifndef NODE_H
#define NODE_H

#include <vector>
#include "TileSprite.h" 

class Node {
public:
    Node(int row, int col, int number, const sf::Texture& sharedTexture);

    void setNumber(int num);

    int getRow() const;
    int getCol() const;
    int getNumber() const;

    // Function to generate all combinations of neighbors
    std::vector<std::vector<std::pair<int, int>>> getCombinations() const;

    void updateView();
    ml::Rectangle& getDrawable();
    void setHighlighted(bool on);


private:
    int row, col, number;
    std::vector<std::pair<int, int>> neighbors;
    
    TileSprite tileSprite;

};

#endif // NODE_H

