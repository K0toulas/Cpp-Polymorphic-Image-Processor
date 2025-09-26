#ifndef IMAGE_H
#define IMAGE_H

#include <iostream>
#include "Pixel.h"  // Include the Pixel base class header

class Image {
protected:
    int width;
    int height;
    int max_luminocity;

public:
    int getWidth() const { return width; }
    int getHeight() const { return height; }
    int getMaxLuminocity() const { return max_luminocity; }
    void setWidth(int width) { this->width = width; }
    void setHeight(int height) { this->height = height; }
    void setMaxLuminocity(int lum) { this->max_luminocity = lum; }

    virtual Image& operator+=(int times) = 0;
    virtual Image& operator*=(double factor) = 0;
    virtual Image& operator!() = 0;
    virtual Image& operator~() = 0;
    virtual Image& operator*() = 0;
    virtual Pixel& getPixel(int row, int col) const = 0;
    friend std::ostream& operator<<(std::ostream& out, Image& image);
    virtual ~Image() {}
    
    
    
};

#endif // IMAGE_H

