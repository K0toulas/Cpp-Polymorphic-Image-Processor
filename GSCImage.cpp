#include "GSCImage.h"
#include <cmath>

GSCImage::GSCImage() : gpixels(nullptr) {}

GSCImage::GSCImage(const GSCImage& img) : Image(img) {
    gpixels = new GSCPixel*[height];
    for (int i = 0; i < height; i++) {
        gpixels[i] = new GSCPixel[width];
        for (int j = 0; j < width; j++) {
            gpixels[i][j] = img.gpixels[i][j];
        }
    }
}

 GSCImage::GSCImage(const RGBImage& grayscaled) : Image(grayscaled) {
     gpixels = new GSCPixel*[height];
     for (int i = 0; i < height; i++) {
         gpixels[i] = new GSCPixel[width];
         for (int j = 0; j < width; j++) {
             unsigned char value = grayscaled.rgbpixel[i][j].getRed() * 0.3 +
                                   grayscaled.rgbpixel[i][j].getBlue() * 0.11 +
                                   grayscaled.rgbpixel[i][j].getGreen() * 0.59;
             gpixels[i][j] = GSCPixel(value);
         }
     }
 }

GSCImage::GSCImage(std::istream& stream) : Image() {
    std::string magicNumber;
    //stream >> magicNumber;

    // Read the width, height, and maximum luminosity
    stream >> width >> height >> max_luminocity;

    // Allocate memory for pixels
    gpixels = new GSCPixel*[height];
    for (int i = 0; i < height; i++) {
        gpixels[i] = new GSCPixel[width];
    }

    // Read pixel values from the stream
    int pixelValue;
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            stream >> pixelValue;
            gpixels[i][j].setValue(static_cast<unsigned char>(pixelValue));
        }
    }
}

GSCImage& GSCImage::operator=(const GSCImage& img) {
    if (this == &img) {
        return *this;
    }

    // Delete existing pixels
    if (gpixels != nullptr) {
        for (int i = 0; i < height; i++) {
            delete[] gpixels[i];
        }
        delete[] gpixels;
    }

    // Copy the data from img
    width = img.width;
    height = img.height;
    max_luminocity = img.max_luminocity;

    gpixels = new GSCPixel*[height];
    for (int i = 0; i < height; i++) {
        gpixels[i] = new GSCPixel[width];
        for (int j = 0; j < width; j++) {
            gpixels[i][j] = img.gpixels[i][j];
        }
    }

    return *this;
}

Image& GSCImage::operator+=(int times) {
    int rotations = times % 4;
    if (rotations < 0)
        rotations += 4;

    // Perform the rotations
    for (int r = 0; r < rotations; ++r) {
        GSCPixel** tempImg = new GSCPixel*[width];
        for (int i = 0; i < width; ++i) {
            tempImg[i] = new GSCPixel[height];
            for (int j = 0; j < height; ++j) {
                tempImg[i][j] = gpixels[height - j - 1][i];
            }
        }

        std::swap(width, height);
        delete[] gpixels;
        gpixels = tempImg;
    }

    return *this;
}

Image& GSCImage::operator*=(double factor) {
    GSCPixel** tempimg;
    int w = round(width * factor);
    int h = round(height * factor);
    int r1, r2, c1, c2, mean;
    GSCPixel p11, p12, p21, p22;

    tempimg = new GSCPixel*[h];
    for (int row = 0; row < h; row++) {
        tempimg[row] = new GSCPixel[w];
        for (int col = 0; col < w; col++) {
            r1 = std::min(static_cast<int>(floor(row / factor)), height - 1);
            r2 = std::min(static_cast<int>(ceil(row / factor)), height - 1);
            c1 = std::min(static_cast<int>(floor(col / factor)), width - 1);
            c2 = std::min(static_cast<int>(ceil(col / factor)), width - 1);

            p11 = gpixels[r1][c1];
            p12 = gpixels[r1][c2];
            p21 = gpixels[r2][c1];
            p22 = gpixels[r2][c2];

            mean = (p11.getValue() + p12.getValue() + p22.getValue() + p21.getValue()) / 4;

            GSCPixel tempixel(static_cast<unsigned char>(round(mean)));
            tempimg[row][col] = tempixel;
        }
    }

    for (int i = 0; i < height; i++) {
        delete[] gpixels[i];
    }
    delete[] gpixels;
    gpixels = tempimg;
    width = w;
    height = h;
    return *this;
}

Image& GSCImage::operator!() {
    GSCPixel** tempImg = new GSCPixel*[height];
    for (int i = 0; i < height; i++) {
        tempImg[i] = new GSCPixel[width];
        for (int j = 0; j < width; j++) {
            unsigned char lumi = max_luminocity - gpixels[i][j].getValue();
            tempImg[i][j].setValue(lumi);
        }
    }

    for (int i = 0; i < height; i++) {
        delete[] gpixels[i];
    }
    delete[] gpixels;
    gpixels = tempImg;

    return *this;
}

Image& GSCImage::operator*() {
    GSCPixel** tempImg = new GSCPixel*[height];
    for (int i = 0; i < height; i++) {
        tempImg[i] = new GSCPixel[width];
        for (int j = 0; j < width; j++) {
            tempImg[i][j] = gpixels[height - i - 1][j];
        }
    }

    for (int i = 0; i < height; i++) {
        delete[] gpixels[i];
    }
    delete[] gpixels;
    gpixels = tempImg;

    return *this;
}


Image& GSCImage::operator~() {
    // Step 1: Calculate histogram
    int histogram[256] = {0};
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            histogram[gpixels[i][j].getValue()]++;
        }
    }

    // Step 2: Calculate probability distribution
    double probability[256];
    int totalPixels = width * height;
    for (int i = 0; i < 256; i++) {
        probability[i] = static_cast<double>(histogram[i]) / totalPixels;
    }

    // Step 3: Calculate cumulative probability distribution
    double cumulativeProbability[256] = {0};
    cumulativeProbability[0] = probability[0];
    for (int i = 1; i < 256; i++) {
        cumulativeProbability[i] = cumulativeProbability[i - 1] + probability[i];
    }

    // Step 4: Set maximum brightness value
    int maxBrightness = 235;

    // Step 5: Calculate transformed brightness values
    int transformedBrightness[256];
    for (int i = 0; i < 256; i++) {
        transformedBrightness[i] = static_cast<int>(cumulativeProbability[i] * maxBrightness);
    }

    // Step 6: Apply brightness transformation to the image
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            int oldBrightness = gpixels[i][j].getValue();
            int newBrightness = transformedBrightness[oldBrightness];
            gpixels[i][j].setValue(newBrightness);
        }
    }

    return *this;
}























GSCPixel& GSCImage::getPixel(int row, int col) const {
    return gpixels[row][col];
}

std::ostream& operator<<(std::ostream& out, const GSCImage& image) {
    out << "P2\n";
    out << image.getWidth() << " " << image.getHeight() << " " ;
    out << image.getMaxLuminocity() << "\n";
    for (int i = 0; i < image.getHeight(); i++) {
        for (int j = 0; j < image.getWidth(); j++) {
            out << static_cast<int>(image.gpixels[i][j].getValue()) << " ";
        }
        out << "\n";
    }
    return out;
}

GSCImage::~GSCImage() {
    if (gpixels != nullptr) {
        for (int i = 0; i < height; i++) {
            delete[] gpixels[i];
        }
        delete[] gpixels;
    }
}
