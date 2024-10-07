#include <cstdlib>
#include "shape.h"
#include "board.h"
#include <time.h>


Board::Board() {
    srand(time(NULL));
    for (int i = 0; i < 5; i++) 
        for (int j = 0; j < 5; j++) board[i][j] = ShapeColor(rand() % 3);

    numMoves = 0;
}

bool Board::removeChunk(int row, int col) {
    ShapeColor spotToRemove = board[row][col];
    // If spot is already EMPTY, invalid move
    if (spotToRemove == S_EMPTY) return false;
    board[row][col] = S_EMPTY;

    // Check if adjacent spots are the same color, then recursively delete
    if (row > 0 && board[row - 1][col] == spotToRemove) removeChunk(row - 1, col);
    if (row < 4 && board[row + 1][col] == spotToRemove) removeChunk(row + 1, col);
    if (col > 0 && board[row][col - 1] == spotToRemove) removeChunk(row, col - 1);
    if (col < 4 && board[row][col + 1] == spotToRemove) removeChunk(row, col + 1);

    return true;
}

void Board::shiftTiles() {
    //If empty tile has RGB tiles above it in any of the other rows before, shift empty tile(s) to the top
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (board[i][j] == S_EMPTY) {
                for (int k = i; k > 0; k--) board[k][j] = board[k - 1][j];
                board[0][j] = S_EMPTY;
            }
        }
    }
}

bool Board::checkStatus() {
    numMoves++;
    //true if no more colors, false if colors still on board
    for (int i = 0; i < 5; i++) 
        for (int j = 0; j < 5; j++) if (board[i][j] != S_EMPTY) return false;
    return true;
}

ShapeColor Board::getTile(int row, int col) {
    return board[row][col];
}

int Board::getNumMoves() {
    return numMoves;
}
