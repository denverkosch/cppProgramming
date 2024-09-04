#ifndef VIEW_H
#define VIEW_H

#include "squareColors.h"
#include "board.h"

using namespace std;

class View {
    public:
        View(Board& b);
        void printBoard();
    private:
        View() = delete;
        Board* board;
};

#endif
