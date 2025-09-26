#ifndef RGBPIXEL_H
#define RGBPIXEL_H

#include "Pixel.h"

class RGBPixel : public Pixel {
private:
    unsigned char red;
    unsigned char green;
    unsigned char blue;

public:
    RGBPixel();
    RGBPixel(unsigned char red, unsigned char green, unsigned char blue);

    unsigned char getRed() const;
    unsigned char getGreen() const;
    unsigned char getBlue() const;

    void setRed(unsigned char red);
    void setGreen(unsigned char green);
    void setBlue(unsigned char blue);

    virtual ~RGBPixel() {}
};

#endif // RGBPIXEL_H

