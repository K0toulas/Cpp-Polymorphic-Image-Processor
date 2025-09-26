#include "GSCPixel.h"

GSCPixel::GSCPixel() : value(0) {}

GSCPixel::GSCPixel(unsigned char value) : value(value) {}

unsigned char GSCPixel::getValue() const {
    return value;
}

void GSCPixel::setValue(unsigned char value) {
    this->value = value;
}

