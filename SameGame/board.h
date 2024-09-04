#ifndef BOARD_H
#define BOARD_H

#include "squareColors.h"

class Board {
    private:
        SquareColor board[5][5];
    public:
        Board();
        SquareColor getTile(int row, int col);
        void shiftTiles();
        bool checkStatus();
        bool removeChunk(int row, int col);
};

#endif
