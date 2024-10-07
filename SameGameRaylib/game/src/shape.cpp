#include "shape.h"

Shape::Shape(ShapeColor color, int x, int y, int width, int height) {
    this->color = color;
    this->width = width;
    this->height = height;
    this->x = x;
    this->y = y;
}

ShapeColor Shape::getColor() {
    return color;
}
int Shape::getWidth() {
    return width;
}
int Shape::getHeight() {
    return height;
}
int Shape::getX() {
    return x;
}
int Shape::getY() {
    return y;
}
void Shape::setX(int x) {
    this->x = x;
}
void Shape::setY(int y) {
    this->y = y;
}
void Shape::setColor(ShapeColor color) {
    this->color = color;
}

