#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <iostream>
#include <fstream>
#include <string>

enum class TOKEN
{
    CURLY_OPEN,
    CURLY_CLOSE,
    COLON,
    NUMBER,
    STRING,
    BOOLEAN,
    ARRAY_OPEN,
    ARRAY_CLOSE,
    NULL_TYPE,
    COMMA
};

class Token
{
public:
    TOKEN type;
    std::string value;
    std::string toString();
};

class Tokenizer
{
private:
    std::fstream file;
    std::streampos prevPos;

public:
    Tokenizer(std::string fileName);
    auto getToken();
    auto getWithoutWhiteSpace();
    void rollBackToken();
    auto hasMoreTokens();
};

#endif //TOKENIZER_H
