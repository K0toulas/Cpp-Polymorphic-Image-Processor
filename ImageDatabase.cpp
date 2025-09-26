#include "ImageDatabase.h"
#include "Image.h"
#include <fstream>
#include "RGBImage.h"
#include "GSCImage.h"

ImageDatabase::ImageDatabase() {}

void ImageDatabase::insertImage(Image* img, const std::string& tokenName) {
    Token token(tokenName, img);
    tokens.push_back(token);

    // Determine the image type and call the appropriate constructor
    if (dynamic_cast<RGBImage*>(img)) {
        RGBImage* rgbImg = dynamic_cast<RGBImage*>(img);
        
        
       // std::cout << "RGBIMAGEEEEEEEEEEEEEEEE "  << std::endl;
        RGBImage newRgbImage(*rgbImg); // Create a new instance of RGBImage using the constructor
        // Now you can work with the newRgbImage instance if needed
    } else if (dynamic_cast<GSCImage*>(img)) {
        GSCImage* gscImg = dynamic_cast<GSCImage*>(img);
        GSCImage newGscImage(*gscImg); // Create a new instance of GSCImage using the constructor
        // Now you can work with the newGscImage instance if needed
    }
}


void ImageDatabase::deleteImage(const std::string& tokenName) {
    for (auto it = tokens.begin(); it != tokens.end(); ++it) {
        if (it->getName() == tokenName) {
            delete it->getPtr();
            tokens.erase(it);
            break;
        }
    }
}

Image* ImageDatabase::getImage(const std::string& tokenName) {
    for (const auto& token : tokens) {
        if (token.getName() == tokenName) {
            return token.getPtr();
        }
    }
    return nullptr;
}

int ImageDatabase::getTokenPosition(const std::string& targetTokenName) const {
    for (int position = 0; position < tokens.size(); position++) {
        if (tokens[position].getName() == targetTokenName) {
            return position;
        }
    }
    return -1;
}

ImageDatabase::~ImageDatabase() {
    for (const auto& token : tokens) {
        delete token.getPtr();
    }
}

Image* readNetpbmImage(const char* filename) {
    std::ifstream f(filename);

    if (!f.is_open()) {
        std::cout << "[ERROR] Unable to open " << filename << std::endl;
        return nullptr;
    }

    Image* img_ptr = nullptr;
    std::string type;

    if (f.good() && !f.eof()) {
        f >> type;
    }
	 //Output modified pixel values from the RGBImage
    
    if (!type.compare("P3")) {
        img_ptr = new RGBImage(f);
         RGBImage* rgbImg = dynamic_cast<RGBImage*>(img_ptr);
        RGBImage newRgbImage(*rgbImg);
//        
//        std::cout << "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa\n";
//    for (int i = 0; i < img_ptr->getHeight(); i++) {
//        for (int j = 0; j < img_ptr->getWidth(); j++) {
//            std::cout << "Modified RGBImage Pixel Values at (" << i << ", " << j << "): "
//                      << static_cast<int>(img_ptr->getPixel(i, j).getRed()) << " "
//                      << static_cast<int>(img_ptr->getPixel(i, j).getGreen()) << " "
//                      << static_cast<int>(img_ptr->getPixel(i, j).getBlue())<< std::endl ;
//        }
//    }
        
        
        
        
        
        
        
        
        
    } else if (!type.compare("P2")) {
        img_ptr = new GSCImage(f);
        GSCImage* gscImg = dynamic_cast<GSCImage*>(img_ptr);
    } else if (f.is_open()) {
        std::cout << "[ERROR] Invalid file format" << std::endl;
    }

    return img_ptr;
}
void ImageDatabase::cleanup() {
    for (Token& token : tokens) {
        delete token.getPtr();
    }
    tokens.clear();
}



