#ifndef GSCIMAGE_H
#define GSCIMAGE_H
#include "Image.h"
#include "GSCPixel.h"
#include "RGBImage.h"

class GSCImage : public Image {
private:
    GSCPixel** gpixels;

public:
    GSCImage();
    GSCImage(const GSCImage& img);
    GSCImage(const RGBImage& grayscaled);
    GSCImage(std::istream& stream);

    GSCImage& operator=(const GSCImage& img);

    virtual Image& operator+=(int times) override;
    virtual Image& operator*=(double factor) override;
    virtual Image& operator!() override;
    virtual Image& operator*() override;
    virtual Image& operator~() override;
    virtual GSCPixel& getPixel(int row, int col) const override;
	
    friend std::ostream& operator<<(std::ostream& out, const GSCImage& image);

    virtual ~GSCImage();
};

#endif // GSCIMAGE_H

