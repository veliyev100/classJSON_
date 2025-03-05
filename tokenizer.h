#ifndef PARSER_JSON_TOKEN
#define PARSER_JSON_TOKEN

#include <string>
#include <fstream>
#include <iostream>

enum class TOKEN
{
    CURLY_OPEN,
    CURLY_CLOSE,
    COLON,
    STRING,
    NUMBER,
    ARRAY_OPEN,
    ARRAY_CLOSE,
    COMMA,
    BOOLEAN,
    NULL_TYPE
};

struct  Token
{
    std::string value;
    TOKEN type;
    std::string toString();
};

class Tokenizer
{
private:
    std::fstream file;
    size_t prevPos;

public:
    Tokenizer(std::string fileName);
    auto getWithoutWhiteSpace();
    auto getToken();
    auto hasMoreTokens();
    void rollBackToken();
};


#endif //PARSER_JSON_TOKEN