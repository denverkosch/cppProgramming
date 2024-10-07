#include <iostream>
#include <string>
#include "controller.h"
#include "board.h"
#include "view.h"

using namespace std;


Controller::Controller(Board& b, View& v) {
    board = &b;
    view = &v;
}

void Controller::run() {
    string input;
    int row;
    int col;
    int moves = 0;
    while (true) {
        view->printBoard();
        //get row or q to quit
        do {
            cout << "Enter a row, or press q to quit game: ";
            cin >> input;
            if (input == "q") return;
            row = validateInput(input);
            if (row == -1) cout << "Invalid input. Try again." << endl;
        } while (row == -1);

        //get column
        do {
            cout << "Enter a column: ";
            cin >> input;
            col = validateInput(input);
            if (col == -1) cout << "Invalid input. Try again." << endl;
        } while (col == -1);

        //make move
        bool removalSuccessful = board->removeChunk(row, col);

        
        if (!removalSuccessful) cout << "Invalid move. Try again." << endl;
        else moves++;

        board->shiftTiles();

        // CheckStatus returns true if empty, false if not empty yet
        if (board->checkStatus()) {
            cout << "Congratulations! You won in " << moves << " moves." << endl;
            return;
        }
    }
}

int validateInput(string in) {
    try {
        int num = stoi(in)-1;
        if (num < 0 || num > 4) return -1;
        return num;
    } catch (exception e) {
        return -1;
    }
}

int main() {
    Board board;
    View view(board);
    Controller controller(board, view);
    controller.run();
}
