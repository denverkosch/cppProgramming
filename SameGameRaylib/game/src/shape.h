#ifndef SHAPE_H
#define SHAPE_H

#include "raylib.h"

enum ShapeColor {
    S_RED,
    S_GREEN,
    S_BLUE,
    S_EMPTY
};

class Shape {
    private:
        int x;
        int y;
        int width;
        int height;
        ShapeColor color;
    public:
        Shape(ShapeColor color, int x, int y, int width, int height);
        int getX();
        int getY();
        int getWidth();
        int getHeight();
        ShapeColor getColor();
        void setColor(ShapeColor color);
        void setX(int x);
        void setY(int y);
        void setWidth(int width);
        void setHeight(int height);
        virtual void draw() = 0;
};

#endif