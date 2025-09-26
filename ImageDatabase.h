#ifndef IMAGEDATABASE_H
#define IMAGEDATABASE_H

#include <vector>
#include "Token.h" // Include other necessary headers

class ImageDatabase {
private:
    std::vector<Token> tokens;

public:
    ImageDatabase();

    void insertImage(Image* img, const std::string& tokenName);
    void deleteImage(const std::string& tokenName);
    Image* getImage(const std::string& tokenName);
    int getTokenPosition(const std::string& targetTokenName) const;
   	Image* readNetpbmImage(const char* filename);
   	void cleanup();
    ~ImageDatabase();
    
};

#endif // IMAGEDATABASE_H


