#ifndef TOKEN_H
#define TOKEN_H

#include <string>
#include "Image.h" // Include other necessary headers

class Token {
private:
    std::string name;
    Image* ptr;

public:
    Token(const std::string& name = "", Image* ptr = nullptr);
    ~Token();
    std::string getName() const;
    Image* getPtr() const;
    void setName(const std::string&);
    void setPtr(Image* ptr);
};

#endif // TOKEN_H


