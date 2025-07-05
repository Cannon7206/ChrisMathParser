//
// Created by christian on 7/4/25.
//

#ifndef TOKEN_H
#define TOKEN_H
#include <utility>

#include "ChrisMath.h"
enum class tokenType {
    NUMBER,
    OPERATOR,
    FUNCTION,
    PARENTHESIS,
    VARIABLE
};


class token {
public:
    tokenType type;
    double numberValue;
    std::string text;

    explicit token(const tokenType type)
        : type(type), numberValue(0.0) {
    }

    token(const tokenType type, const double numberValue)
        : type(type), numberValue(numberValue) {
    }

    token(const tokenType type, std::string str)
        : type(type), numberValue(0.0), text(std::move(str)) {
    }

    [[nodiscard]] std::string toString() const;
};
class tokenizer {
private:
    std::vector<token> tokens;

public:
    void tokenize(const std::string& input);
    const std::vector<token>& getTokens() const;
};




#endif //TOKEN_H
