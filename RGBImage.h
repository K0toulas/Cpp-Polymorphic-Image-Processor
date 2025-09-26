#pragma once
#include "Image.h"
#include "RGBPixel.h"
#include <iostream>

class RGBImage : public Image {
private:
   

public:
	 RGBPixel** rgbpixel;
    RGBImage();
    RGBImage(const RGBImage& image);
    RGBImage(std::istream& stream);
    virtual ~RGBImage();

    RGBImage& operator=(const RGBImage& img);
	virtual Image& operator += (int ) override ;
    Image& operator*=(double factor) override;
    Image& operator!() override;
    Image& operator*() override;
    Image& operator~() override;

    Pixel& getPixel(int row, int col) const override;

    friend std::ostream& operator<<(std::ostream& out, const RGBImage& image);
};

std::ostream& operator<<(std::ostream& out, const RGBImage& image);

