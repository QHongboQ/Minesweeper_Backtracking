#ifndef HIGHLIGHTER_H
#define HIGHLIGHTER_H

#include "Board.h"

class Highlighter {
private:
    int row;
    int col;
    int maxRow;
    int maxCol;

public:
    Highlighter(int maxRow, int maxCol);
    void moveNext();
    void movePrev();
    void highlight(Board& board) const;
    void removeHighlight(Board& board) const;
    void moveNextSkippingNumber(const Board& board);
    void movePrevSkippingNumber(const Board& board);

    int getRow() const;
    int getCol() const;
    
};

#endif // HIGHLIGHTER_H