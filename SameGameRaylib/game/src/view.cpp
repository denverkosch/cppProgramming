#include "shape.h"
#include <iostream>
#include "view.h"
#include "board.h"
#include "square.h"

using namespace std;

View::View (Board& b) {
    board = &b;
}

void View::draw() {
    vector<Shape*> squares;

    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            ShapeColor color = board->getTile(i, j);

            if (color == S_EMPTY) continue;
            
            Shape* s = new Square(color, (j * 100) + 50, (i * 100) + 50, 100, 100);
            squares.push_back(s);
        }
    }
    
    for (Shape* s : squares) s->draw(); 
}
