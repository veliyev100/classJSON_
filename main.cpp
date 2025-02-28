#include <iostream>
#include <map>
#include <memory>
#include <vector>
#include <string>
#include <algorithm>
class JSON_Node {
    using JSONObject = std::map<std::string, std::shared_ptr<JSON_Node>>;
    using JSONList = std::vector<std::shared_ptr<JSON_Node>>;
    enum class Type {OBJECT,LIST,STRING,NUMBER,BOOLEAN,NULL_TYPE,FLOAT};
    union Values {
        JSONObject* object;
        JSONList* list;
        std::string* s;
        float fvalue;
        bool bvalue;
    } value;
    Type type;
    auto returnObject() {
        if(type==Type::OBJECT) {
            return* value.object;
        }
        throw std::logic_error("wrong return");
    }
    auto returnList() {
        if (type == Type::LIST) {
            return *value.list;
        }
        throw std::logic_error("wrong return");
    }

    auto returnString() {
        if (type == Type::STRING) {
            return *value.s;
        }
        throw std::logic_error("wrong return");
    }
    auto returnFloat() {
        if (type == Type::FLOAT) {
            return value.fvalue;
        }
        throw std::logic_error("wrong return");
    }

    auto returnBool() {
        if (type == Type::BOOLEAN) {
            return value.bvalue;
        }
        throw std::logic_error("wrong return");
    }
    void setObject(JSONObject* object) {
        this -> value.object = object;
        type = Type::OBJECT;
    }
    void setList(const std::vector<JSONObject>& list) {
        this->value.list = list;
        type = Type::LIST;
    }


    void setString(std::string* str) {
        this->value.s = str;
        type = Type::STRING;
    }

    void setFloat(float f) {
        this->value.fvalue = f;
        type = Type::FLOAT;
    }

    void setBool(bool b) {
        this->value.bvalue = b;
        type = Type::BOOLEAN;
    }


};

int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
