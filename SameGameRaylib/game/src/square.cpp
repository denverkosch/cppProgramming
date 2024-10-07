#include <cstdlib>
#include "square.h"
#include "raylib.h"

using namespace std;


void Square::draw() {
    Color c;
    ShapeColor color = this->getColor();
    switch (color) {
        case S_RED:
            c = RED;
            break;
        case S_GREEN:
            c = GREEN;
            break;
        case S_BLUE:
            c = BLUE;
            break;
        case S_EMPTY:
            c = WHITE;
            break;
    }

    int x = this->getX();
    int y = this->getY();
    int width = this->getWidth();
    int height = this->getHeight();
    DrawRectangle(x, y, width, height, c);
}

Square::Square(ShapeColor color, int x, int y, int width, int height) : Shape(color, x, y, width, height) {
}