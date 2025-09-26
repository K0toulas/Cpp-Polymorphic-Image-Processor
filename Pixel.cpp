#include "Pixel.h"
Pixel::Pixel() : value(0) {}


Pixel::Pixel(int value){}

Pixel::Pixel(unsigned char red, unsigned char green, unsigned char blue)
    : red(red), green(green), blue(blue) {}

unsigned char Pixel::getRed() const {
    return red;
}

unsigned char Pixel::getGreen() const {
    return green;
}

unsigned char Pixel::getBlue() const {
    return blue;
}

void Pixel::setRed(unsigned char red) {
    this->red = red;
}

void Pixel::setGreen(unsigned char green) {
    this->green = green;
}

void Pixel::setBlue(unsigned char blue) {
    this->blue = blue;
}

