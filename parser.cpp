#include "parser.h"
#include "JSON.h"
#include <iostream>
#include <memory>
#include <stdexcept>

void JSONParser::parse()
{
    std::string key = "";

    while (tokenizer.hasMoreTokens())
    {
        Token token;

        try
        {
            token = tokenizer.getToken();
            std::cout << token.toString() << "\n";

            switch (token.type)
            {
                case TOKEN::CURLY_OPEN:
                {
                    std::shared_ptr<JSON_Node> parsedObject = parseObject();
                    if (!root)
                    {
                        root = parsedObject;
                    }
                    break;
                }
                case TOKEN::ARRAY_OPEN:
                {
                    std::shared_ptr<JSON_Node> parsedList = parseList();
                    if (!root)
                    {
                        root = parsedList;
                    }
                    break;
                }
                case TOKEN::STRING:
                {
                    tokenizer.rollBackToken();
                    std::shared_ptr<JSON_Node> parsedString = parseString();
                    if (!root)
                    {
                        root = parsedString;
                    }
                    break;
                }
                case TOKEN::NUMBER:
                {
                    tokenizer.rollBackToken();
                    std::shared_ptr<JSON_Node> parsedNumber = parseNumber();
                    if (!root)
                    {
                        root = parsedNumber;
                    }
                    break;
                }
                case TOKEN::BOOLEAN:
                {
                    tokenizer.rollBackToken();
                    std::shared_ptr<JSON_Node> parsedBoolean = parseBoolean();
                    break;
                }
            }
        }
        catch (const std::logic_error &e)
        {
            break;
        }
    }
}

std::shared_ptr<JSON::JSONNode> JSONParser::parseList()
{
    std::cout << "Parse list \n";
    std::shared_ptr<JSON::JSONNode> node = std::make_shared<JSON::JSONNode>();
    std::shared_ptr<JSON::JSONList> list = std::make_shared<JSON::JSONList>();
    bool hasCompleted = false;

    while (!hasCompleted)
    {
        if (!tokenizer.hasMoreTokens())
        {
            throw std::logic_error("No more tokens");
        }
        else
        {
            Token nextToken = tokenizer.getToken();
            std::shared_ptr<JSON::JSONNode> node;
            switch (nextToken.type)
            {
                case TOKEN::ARRAY_OPEN:
                    node = parseList();
                    break;
                case TOKEN::CURLY_CLOSE:
                    node = parseObject();
                    break;
                case TOKEN::STRING:
                    tokenizer.rollBackToken();
                    node = parseString();
                    break;
                case TOKEN::NUMBER:
                    tokenizer.rollBackToken();
                    node = parseNumber();
                    break;
                case TOKEN::BOOLEAN:
                    tokenizer.rollBackToken();
                    node = parseBoolean();
                    break;
                case TOKEN::NULL_TYPE:
                    node = parseNull();
                    break;
            }

            list->push_back(node);
            nextToken = tokenizer.getToken();
            if (nextToken.type == TOKEN::ARRAY_CLOSE)
            {
                hasCompleted = true;
            }
        }
    }
    node->setList(list);
    return node;
}

std::shared_ptr<JSON::JSONNode> JSONParser::parseObject()
{
    std::cout << "Parsing object \n";
    std::shared_ptr<JSON::JSONNode> node = std::make_shared<JSON::JSONNode>();
    std::shared_ptr<JSON::JSONObject> keyObjectmap = std::make_shared<JSON::JSONObject>();
    bool hasCompleted = false;

    while (!hasCompleted)
    {
        if (tokenizer.hasMoreTokens())
        {
            Token nextToken = tokenizer.getToken();
            std::string key = nextToken.value();
            std::cout << "key: " << key << "\n";

            nextToken = tokenizer.getToken();
            std::shared_ptr<JSON::JSONNode> node;

            switch (nextToken.type)
            {
                case TOKEN::STRING:
                    tokenizer.rollBackToken();
                    (*keyObjectmap)[key] = parseString();
                    break;
                case TOKEN::ARRAY_OPEN:
                    (*keyObjectmap)[key] = parseList();
                    break;
                case TOKEN::NUMBER:
                    tokenizer.rollBackToken();
                    (*keyObjectmap)[key] = parseNumber();
                    break;
                case TOKEN::CURLY_OPEN:
                    (*keyObjectmap)[key] = parseObject();
                    break;
                case TOKEN::BOOLEAN:
                    tokenizer.rollBackToken();
                    (*keyObjectmap)[key] = parseBoolean();
                    break;
                case TOKEN::NULL_TYPE:
                    (*keyObjectmap)[key] = parseNull();
                    break;
            }

            nextToken = tokenizer.getToken();
            if (nextToken.type == TOKEN::CURLY_CLOSE)
            {
                hasCompleted = true;
                break;
            }
        }
        else
        {
            throw std::logic_error("No more tokens");
        }
    }

    node->setObject(keyObjectmap);
    return node;
}

std::shared_ptr<JSON::JSONNode> JSONParser::parseString()
{
    std::cout << "Parsing string \n";
    std::shared_ptr<JSON::JSONNode> node = std::make_shared<JSON::JSONNode>();
    Token token = tokenizer.getToken();
    std::string sValue = token.value();
    node->setString(sValue);
    return node;
}

std::shared_ptr<JSON::JSONNode> JSONParser::parseNumber()
{
    std::cout << "Parsing number \n";
    std::shared_ptr<JSON::JSONNode> node = std::make_shared<JSON::JSONNode>();
    Token nextToken = tokenizer.getToken();
    std::string value = nextToken.value();
    std::cout << "value: " << value << "\n";
    float fvalue = std::stof(value);
    node->setFloat(fvalue);
    return node;
}

std::shared_ptr<JSON::JSONNode> JSONParser::parseBoolean()
{
    std::cout << "Parsing boolean \n";
    std::shared_ptr<JSON::JSONNode> node = std::make_shared<JSON::JSONNode>();
    Token nextToken = tokenizer.getToken();
    node->setBool(nextToken.value() == "True" ? true : false);
    return node;
}

std::shared_ptr<JSON::JSONNode> JSONParser::parseNull()
{
    std::cout << "Parsing null \n";
    std::shared_ptr<JSON::JSONNode> node = std::make_shared<JSON::JSONNode>();
    Token nextToken = tokenizer.getToken();
    node->setNull();
    return node;
}
