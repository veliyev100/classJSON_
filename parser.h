#ifndef PARSER_JSON_PARSER
#define PARSER_JSON_PARSER

#include "tokenizer.h"
#include <memory>

class JSONParser
{
private:
    std::fstream file;
    std::shared_ptr<JSON::JSONNode> root;
    std::unique_ptr<JSON::JSONNode> current;
    Tokenizer tokenizer;

public:
    JSONParser(const std::string filename): tokenizer(filename) {}
    void parse();

    std::shared_ptr<JSONNode> parseObject();
    std::shared_ptr<JSONNode> parseString();
    std::shared_ptr<JSONNode> parseNumber();
    std::shared_ptr<JSONNode> parseList();
    std::shared_ptr<JSONNode> parseBoolean();
    std::shared_ptr<JSONNode> parseNull();
};

#endif //PARSER_JSON_PARSER
