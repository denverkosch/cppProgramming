#ifndef VIEW_H
#define VIEW_H

#include "shape.h"
#include "board.h"

class View {
    public:
        View(Board& b);
        void draw();
    private:
        View() = delete;
        Board* board;
};

#endif
