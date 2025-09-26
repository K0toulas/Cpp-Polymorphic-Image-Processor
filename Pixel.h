#ifndef PIXEL_H
#define PIXEL_H
#include <iostream>
using namespace std;
class Pixel{
public : 
	//virtual void abstract() = 0;
    Pixel();

    Pixel(int value);

    Pixel(unsigned char red, unsigned char green, unsigned char blue);

    unsigned char getRed() const;

    unsigned char getGreen() const;

    unsigned char getBlue() const;

    void setRed(unsigned char red);

    void setGreen(unsigned char green);

    void setBlue(unsigned char blue);

protected :
	unsigned char red;
	unsigned char green;
	unsigned char blue;
    int value;
 	friend std::ostream& operator<<(std::ostream& out, const Pixel& pixel) {
        out << static_cast<int>(pixel.red) << " "
            << static_cast<int>(pixel.green) << " "
            << static_cast<int>(pixel.blue) << " ";

        return out;
    }

};



#endif // PIXEL_H

