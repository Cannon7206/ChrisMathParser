//
// Created by christian on 7/4/25.
//

#include "token.h"

void tokenizer::tokenize(const std::string &input) {
    const size_t len = input.length();
    size_t i = 0;

    while (i < len) {
        char c = input[i];
        //skipping whitespace
        if (isspace(c)) {
            i++;
            continue;
        }
        //number, digit or "."
        else if (isdigit(c) || c == '.') {
            const size_t start = i;
            while (i < len && (isalnum(input[i])) || input[i] == '.') {
                i++;
            }
            std::string word = input.substr(start, i - start);
            double value = stod(word);
            tokens.emplace_back(tokenType::NUMBER, value);
            continue;
        }
        //letter, is it a function or variable
        else if (isalpha(c)) {
            size_t start = i;
            while (i < len && (isalnum(input[i]))) {
                i++;
            }
            std::string word = input.substr(start, i - start);
            tokenType type = isFunction(word) ? tokenType::FUNCTION : tokenType::VARIABLE;
            tokens.emplace_back(type, word);
        } else if (c == '+' || c == '-' || c == '*' || c == '/' || c == '^') {
            tokens.emplace_back(tokenType::OPERATOR, std::string(1, input[i]));
            i++;
            continue;
        } else if (c == '(' || c == ')') {
            tokens.emplace_back(tokenType::PARENTHESIS, std::string(1, input[i]));
        }
    }
}
