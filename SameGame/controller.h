#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "board.h"
#include "view.h"
#include <iostream>
#include <string>

class Controller {
    public:
        Controller(Board& b, View& v);
        void run();
    private:
        Controller() = delete;
        Board* board;
        View* view;
};

int validateInput(string in);
int main();

#endif
