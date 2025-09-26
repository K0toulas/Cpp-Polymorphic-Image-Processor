#include "RGBPixel.h"

RGBPixel::RGBPixel() : red(0), green(0), blue(0) {}

RGBPixel::RGBPixel(unsigned char red, unsigned char green, unsigned char blue)
    : red(red), green(green), blue(blue) {}

unsigned char RGBPixel::getRed() const {
    return red;
}

unsigned char RGBPixel::getGreen() const {
    return green;
}

unsigned char RGBPixel::getBlue() const {
    return blue;
}

void RGBPixel::setRed(unsigned char red) {
    this->red = red;
}

void RGBPixel::setGreen(unsigned char green) {
    this->green = green;
}

void RGBPixel::setBlue(unsigned char blue) {
    this->blue = blue;
}
#include "RGBPixel.h"


