#include "Token.h"

Token::Token(const std::string& name, Image* ptr) : name(name), ptr(ptr) {}

Token::~Token() {
    // Implement the destructor logic here
}

std::string Token::getName() const {
    return name;
}

Image* Token::getPtr() const {
    return ptr;
}

void Token::setName(const std::string& newName) {
    name = newName;
}

void Token::setPtr(Image* newPtr) {
    ptr = newPtr;
}


