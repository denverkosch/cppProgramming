#include "squareColors.h"
#include <iostream>
#include "view.h"
#include "board.h"

View::View (Board& b) {
    board = &b;
}

void View::printBoard() {
    cout << "  ";
    for (int i = 1; i < 6; i++) cout << i << " ";
    cout << endl;

    for (int i = 0; i < 5; i++) {
        cout << i+1 << " ";
        for (int j = 0; j < 5; j++) {
            switch (this->board->getTile(i, j)) {
                case RED:
                    cout << "R ";
                    break;
                case GREEN:
                    cout << "G ";
                    break;
                case BLUE:
                    cout << "B ";
                    break;
                case EMPTY:
                    cout << "  ";
                    break;
            }
        }
        cout << endl;
    }
}
