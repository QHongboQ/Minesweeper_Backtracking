#include "Highlighter.h"

Highlighter::Highlighter(int maxRow, int maxCol)
    : row(0), col(0), maxRow(maxRow), maxCol(maxCol) {}

void Highlighter::moveNext() {
    ++col;
    if (col >= maxCol) {
        col = 0;
        ++row;
    }
}

void Highlighter::movePrev() {
    --col;
    if (col < 0) {
        col = maxCol - 1;
        --row;
    }
}

void Highlighter::highlight(Board& board) const {
    board.getNode(row, col).setHighlighted(true);
}

void Highlighter::removeHighlight(Board& board) const {
    board.getNode(row, col).setHighlighted(false);
}

int Highlighter::getRow() const {return row;}

int Highlighter::getCol() const {return col;}

void Highlighter::moveNextSkippingNumber(const Board& board) {
    do {
        moveNext();
        if (row >= maxRow) {
            row = maxRow - 1;
            col = maxCol - 1;
            break;
        }

    } while (board.getNode(row, col).getNumber() > 0); // skip numbers
}

void Highlighter::movePrevSkippingNumber(const Board& board) {
    do {
        movePrev();
        if (row < 0) {
            row = 0;
            col = 0;
            break;
        }

    } while (board.getNode(row, col).getNumber() > 0); // skip numbers
}