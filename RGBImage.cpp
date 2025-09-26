#include "RGBImage.h"
#include <cmath>

RGBImage::RGBImage() : rgbpixel(nullptr) {}

RGBImage::RGBImage(const RGBImage& img) : Image(img) {
    // Obtain width and height from the img object
    int imgWidth = img.getWidth();
    int imgHeight = img.getHeight();

    rgbpixel = new RGBPixel*[imgHeight];
    for (int i = 0; i < imgHeight; i++) {
        rgbpixel[i] = new RGBPixel[imgWidth];
        for (int j = 0; j < imgWidth; j++) {
            rgbpixel[i][j] = img.rgbpixel[i][j];
        }
    }
    
//////////////////////////////////
//    std::cout << "RGBIMAGE CREATION\n";
//     //Output modified pixel values from the RGBImage
//    std::cout << "\nModified RGBImage Pixel Values after ! operator:\n";
//    for (int i = 0; i < img.getHeight(); i++) {
//        for (int j = 0; j < img.getWidth(); j++) {
//            std::cout << "Modified RGBImage Pixel Values at (" << i << ", " << j << "): "
//                      << static_cast<int>(img.getPixel(i, j).getRed()) << " "
//                      << static_cast<int>(img.getPixel(i, j).getGreen()) << " "
//                      << static_cast<int>(img.getPixel(i, j).getBlue()) << std::endl;
//        }
//    }


////////////////////////////////
}


RGBImage::RGBImage(std::istream& stream) : Image() {
    std::string magicNumber;
    //stream >> magicNumber;

    // Read the width, height, and maximum luminosity
    stream  >> width >> height >> max_luminocity;
	
    // Allocate memory for pixels
    rgbpixel = new RGBPixel*[height];
    for (int i = 0; i < height; i++) {
        rgbpixel[i] = new RGBPixel[width];
    }

    // Read pixel values from the stream
    int red, green, blue;
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            stream >> red;
            stream >> green;
            stream >> blue;
            rgbpixel[i][j] = RGBPixel(static_cast<unsigned char>(red), static_cast<unsigned char>(green), static_cast<unsigned char>(blue));
        }
    }  
//    
//     std::cout << "Pixel Values:" << std::endl;
//    for (int i = 0; i < height; i++) {
//        for (int j = 0; j < width; j++) {
//            std::cout << "(" << static_cast<int>(rgbpixel[i][j].getRed()) << ", "
//                      << static_cast<int>(rgbpixel[i][j].getGreen()) << ", "
//                      << static_cast<int>(rgbpixel[i][j].getBlue()) << ") ";
//        }
//        std::cout << std::endl;
//    }
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
}

RGBImage& RGBImage::operator=(const RGBImage& img) {
    if (this == &img) {
        return *this;
    }

    // Delete existing pixels
    if (rgbpixel != nullptr) {
        for (int i = 0; i < height; i++) {
            delete[] rgbpixel[i];
        }
        delete[] rgbpixel;
    }

    // Copy the data from img
    width = img.width;
    height = img.height;
    max_luminocity = img.max_luminocity;

    rgbpixel = new RGBPixel*[height];
    for (int i = 0; i < height; i++) {
        rgbpixel[i] = new RGBPixel[width];
        for (int j = 0; j < width; j++) {
            rgbpixel[i][j] = img.rgbpixel[i][j];
        }
    }

    return *this;
}

Image& RGBImage::operator+=(int times) {
	
	
	
    
    int rotations = times % 4;
    if (rotations < 0)
        rotations += 4;

    // Perform the rotations
    for (int r = 0; r < rotations; ++r) {
        RGBPixel** tempImg = new RGBPixel*[width];
        for (int i = 0; i < width; ++i) {
            tempImg[i] = new RGBPixel[height];
            for (int j = 0; j < height; ++j) {
                tempImg[i][j] = rgbpixel[height - j - 1][i];
            }
        }

        std::swap(width, height);
        delete[] rgbpixel;
        rgbpixel = tempImg;
    }

    return *this;
}

Image& RGBImage::operator*=(double factor) {
    RGBPixel** tempimg;
    int w = round(width * factor);
    int h = round(height * factor);
    int r1, r2, c1, c2, mean;
    RGBPixel p11, p12, p21, p22;

    tempimg = new RGBPixel*[h];
    for (int row = 0; row < h; row++) {
        tempimg[row] = new RGBPixel[w];
        for (int col = 0; col < w; col++) {
            r1 = std::min(static_cast<int>(floor(row / factor)), height - 1);
            r2 = std::min(static_cast<int>(ceil(row / factor)), height - 1);
            c1 = std::min(static_cast<int>(floor(col / factor)), width - 1);
            c2 = std::min(static_cast<int>(ceil(col / factor)), width - 1);

            p11 = rgbpixel[r1][c1];
            p12 = rgbpixel[r1][c2];
            p21 = rgbpixel[r2][c1];
            p22 = rgbpixel[r2][c2];

            mean = (p11.getRed() + p12.getRed() + p22.getRed() + p21.getRed()) / 4;

            RGBPixel tempixel;
            tempixel.setRed(mean);
            mean = (p11.getBlue() + p12.getBlue() + p22.getBlue() + p21.getBlue()) / 4;
            tempixel.setBlue(mean);
            mean = (p11.getGreen() + p12.getGreen() + p22.getGreen() + p21.getGreen()) / 4;
            tempixel.setGreen(mean);
            tempimg[row][col] = tempixel;
        }
    }

    for (int i = 0; i < height; i++) {
        delete[] rgbpixel[i];
    }
    delete[] rgbpixel;
    rgbpixel = tempimg;
    width = w;
    height = h;
    return *this;
}

Image& RGBImage::operator!() {
    RGBPixel** tempImg = new RGBPixel*[height];
    for (int i = 0; i < height; i++) {
        tempImg[i] = new RGBPixel[width];
        for (int j = 0; j < width; j++) {
            unsigned char red = max_luminocity - rgbpixel[i][j].getRed();
            unsigned char blue = max_luminocity - rgbpixel[i][j].getBlue();
            unsigned char green = max_luminocity - rgbpixel[i][j].getGreen();
            tempImg[i][j].setRed(red);
            tempImg[i][j].setBlue(blue);
            tempImg[i][j].setGreen(green);
        }
    }

    for (int i = 0; i < height; i++) {
        delete[] rgbpixel[i];
    }
    delete[] rgbpixel;
    rgbpixel = tempImg;

    return *this;
}

Image& RGBImage::operator*() {
    RGBPixel** tempImg = new RGBPixel*[height];
    for (int i = 0; i < height; i++) {
        tempImg[i] = new RGBPixel[width];
        for (int j = 0; j < width; j++) {
            tempImg[i][j] = rgbpixel[height - i - 1][j];
        }
    }

    for (int i = 0; i < height; i++) {
        delete[] rgbpixel[i];
    }
    delete[] rgbpixel;
    rgbpixel = tempImg;


    return *this;
}

Image& RGBImage::operator~() {
    // Step 1: Reset relevant table to zero
    int histogramR[256] = {0};
    int histogramG[256] = {0};
    int histogramB[256] = {0};

    // Calculate histograms for each color channel
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            histogramR[rgbpixel[i][j].getRed()]++;
            histogramG[rgbpixel[i][j].getGreen()]++;
            histogramB[rgbpixel[i][j].getBlue()]++;
        }
    }

    // Calculate probability distribution for each channel
    double probabilityR[256];
    double probabilityG[256];
    double probabilityB[256];
    int totalPixels = width * height;
    for (int i = 0; i < 256; i++) {
        probabilityR[i] = static_cast<double>(histogramR[i]) / totalPixels;
        probabilityG[i] = static_cast<double>(histogramG[i]) / totalPixels;
        probabilityB[i] = static_cast<double>(histogramB[i]) / totalPixels;
    }

    // Calculate cumulative probability distribution for each channel
    double cumulativeProbabilityR[256] = {0};
    double cumulativeProbabilityG[256] = {0};
    double cumulativeProbabilityB[256] = {0};
    cumulativeProbabilityR[0] = probabilityR[0];
    cumulativeProbabilityG[0] = probabilityG[0];
    cumulativeProbabilityB[0] = probabilityB[0];
    for (int i = 1; i < 256; i++) {
        cumulativeProbabilityR[i] = cumulativeProbabilityR[i - 1] + probabilityR[i];
        cumulativeProbabilityG[i] = cumulativeProbabilityG[i - 1] + probabilityG[i];
        cumulativeProbabilityB[i] = cumulativeProbabilityB[i - 1] + probabilityB[i];
    }

    // Step 4: Set maximum brightness value
    int maxBrightness = 235;

    // Step 5: Calculate transformed brightness values for each channel
    int transformedBrightnessR[256];
    int transformedBrightnessG[256];
    int transformedBrightnessB[256];
    for (int i = 0; i < 256; i++) {
        transformedBrightnessR[i] = static_cast<int>(cumulativeProbabilityR[i] * maxBrightness);
        transformedBrightnessG[i] = static_cast<int>(cumulativeProbabilityG[i] * maxBrightness);
        transformedBrightnessB[i] = static_cast<int>(cumulativeProbabilityB[i] * maxBrightness);
    }

    // Step 6: Apply brightness transformation to the image
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            int oldRed = rgbpixel[i][j].getRed();
            int oldGreen = rgbpixel[i][j].getGreen();
            int oldBlue = rgbpixel[i][j].getBlue();
            
            int newRed = transformedBrightnessR[oldRed];
            int newGreen = transformedBrightnessG[oldGreen];
            int newBlue = transformedBrightnessB[oldBlue];

            rgbpixel[i][j].setRed(newRed);
            rgbpixel[i][j].setGreen(newGreen);
            rgbpixel[i][j].setBlue(newBlue);
        }
    }

    return *this;
}

























Pixel& RGBImage::getPixel(int row, int col) const {
    return rgbpixel[row][col];
}

std::ostream& operator<<(std::ostream& out, const RGBImage& image) {
    out << "P3\n";
    out << image.getWidth() << " " << image.getHeight() << "\n";
    out << image.getMaxLuminocity() << "\n";
    for (int i = 0; i < image.getHeight(); i++) {
        for (int j = 0; j < image.getWidth(); j++) {
            out << static_cast<int>(image.rgbpixel[i][j].getRed()) << " ";
            out << static_cast<int>(image.rgbpixel[i][j].getGreen()) << " ";
            out << static_cast<int>(image.rgbpixel[i][j].getBlue()) << " ";
        }
        out << "\n";
    }
    return out;
}

RGBImage::~RGBImage() {
    if (rgbpixel != nullptr) {
        for (int i = 0; i < height; i++) {
            delete[] rgbpixel[i];
        }
        delete[] rgbpixel;
    }
}

