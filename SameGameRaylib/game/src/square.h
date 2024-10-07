#ifndef SQUARE_H
#define SQUARE_H

#include "shape.h"

class Square : public Shape {
    public:
        void draw();
        Square(ShapeColor color, int x, int y, int width, int height);
};


#endif
