#ifndef GSCPIXEL_H
#define GSCPIXEL_H

#include "Pixel.h"

class GSCPixel : public Pixel {
private:
    unsigned char value;

public:
    GSCPixel();
    GSCPixel(unsigned char value);

    unsigned char getValue() const;
    void setValue(unsigned char value);

    virtual ~GSCPixel() {}
};

#endif // GSCPIXEL_H

