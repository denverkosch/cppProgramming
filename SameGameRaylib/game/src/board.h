#ifndef BOARD_H
#define BOARD_H

#include "shape.h"

class Board {
    private:
        ShapeColor board[5][5];
        int numMoves;
    public:
        Board();
        ShapeColor getTile(int row, int col);
        void shiftTiles();
        bool checkStatus();
        bool removeChunk(int row, int col);
        int getNumMoves();
};

#endif
