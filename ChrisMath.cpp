#include "ChrisMath.h"

std::vector<token> Tokenizer::tokenize(const std::string &input) {
    std::vector<token> tokens;
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
            while (i < len && (isdigit(input[i]) || input[i] == '.')) {
                i++;
            }
            std::string word = input.substr(start, i - start);
            tokenType type = tokenType::NUMBER;
            tokens.emplace_back(type, word);
            continue;
        }
        //Functions
        else if (isalpha(c)) {
            size_t start = i;
            while (i < len && (isalnum(input[i]))) {
                i++;
            }
            std::string word = input.substr(start, i - start);
            tokenType type = tokenType::FUNCTION;
            tokens.emplace_back(type, word);
        }
        //Operator
        else if (c == '+' || c == '-' || c == '*' || c == '/' || c == '^') {
            tokens.emplace_back(tokenType::OPERATOR, std::string(1, input[i]));
            i++;
            continue;
        }
        //Parenthesis
        else if (c == '(' || c == ')') {
            tokens.emplace_back(tokenType::PARENTHESIS, std::string(1, input[i]));
            i++;
            continue;
        } else {
            std::cout << "Unknown character" << c << std::endl;
            i++;
        }
    }
    return tokens;
}

std::vector<token> Parser::infixToPostfix(const std::vector<token> &tokens) {
}

double ChrisMathParser::evaluate(const std::string &input) {
    auto tokens = tokenizer.tokenize(input);
    auto postfix = parser.infixToPostfix(tokens);
    return evaluator.evaluatePostfix(postfix);
}
