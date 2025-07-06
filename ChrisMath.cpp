#include "ChrisMath.h"
#include <stack>
#include <iostream>
#include "funct.h"

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

int Parser::getPrecedence(const std::string &op) {
    if (op == "+" || op == "-") {
        return 1;
    } else if (op == "*" || op == "/") {
        return 2;
    } else if (op == "^") {
        return 3;
    } else {
        return 0;
    }
}

bool Parser::isLeftAssociative(const std::string &op) {
    if (op == "^") return false;
    else return true;
}


std::vector<token> Parser::infixToPostfix(const std::vector<token> &tokens) {
    std::vector<token> outputQueue;
    std::stack<token> operatorStack;

    for (const auto &token: tokens) {
        switch (token.type) {
            case tokenType::NUMBER: {
                outputQueue.emplace_back(token);
                break;
            }
            case tokenType::FUNCTION: {
                operatorStack.push(token);
                break;
            }
            case tokenType::OPERATOR: {
                while (!operatorStack.empty()) {
                    const struct token &top = operatorStack.top();
                    if (top.type == tokenType::OPERATOR) {
                        int prec1 = getPrecedence(token.word);
                        int prec2 = getPrecedence(top.word);
                        if ((isLeftAssociative(token.word) && prec1 <= prec2) ||
                            (!isLeftAssociative(token.word) && prec1 < prec2)) {
                            outputQueue.emplace_back(top);
                            operatorStack.pop();
                            continue;
                        }
                    }
                    break;
                }
                operatorStack.push(token);
                break;
            }
            case tokenType::PARENTHESIS: {
                if (token.word == "(") {
                    operatorStack.push(token);
                } else if (token.word == ")") {
                    while (!operatorStack.empty() && operatorStack.top().word != "(") {
                        outputQueue.emplace_back(operatorStack.top());
                        operatorStack.pop();
                    }
                    if (!operatorStack.empty() && operatorStack.top().word == "(") {
                        operatorStack.pop();
                    }
                    if (!operatorStack.empty() && operatorStack.top().type == tokenType::FUNCTION) {
                        outputQueue.emplace_back(operatorStack.top());
                        operatorStack.pop();
                    }
                }
                break;
            }
        }
    }
    while (!operatorStack.empty()) {
        outputQueue.emplace_back(operatorStack.top());
        operatorStack.pop();
    }
    return outputQueue;
}

double Evaluator::evaluatePostfix(const std::vector<token> &postfix) {
    std::stack<double> Stack;
    for (const auto &token: postfix) {
        switch (token.type) {
            case tokenType::NUMBER: {
                double num = std::stod(token.word);
                Stack.push(num);
                break;
            }
            case tokenType::OPERATOR: {
                if (Stack.size() < 2) {
                    throw std::runtime_error("Insufficient operands");
                }
                double right = Stack.top();
                Stack.pop();
                double left = Stack.top();
                Stack.pop();
                double result = applyOperator(token.word, left, right);
                Stack.push(result);
                break;
            }
            case tokenType::FUNCTION: {
                if (Stack.empty()) throw std::runtime_error("No argument for function");
                double arg = Stack.top();
                Stack.pop();
                double result = applyFunction(token.word, arg);
                Stack.push(result);
                break;
            }
            default: throw std::runtime_error("Unknown token");
        }
    }
    if (Stack.size() != 1) throw std::runtime_error("Invalid postfix expression");
    return Stack.top();
}

double Evaluator::applyFunction(const std::string &functName, const double argument) {
    if (functName == "sin") return funct::sine(argument);
    else if (functName == "cos") return funct::cosine(argument);
    else if (functName == "tan") return funct::tangent(argument);
    else if (functName == "asin") return funct::arcSine(argument);
    else if (functName == "acos") return funct::arcCosine(argument);
    else if (functName == "atan") return funct::arcTangent(argument);
    else if (functName == "exp") return funct::expon(argument);
    else if (functName == "ln") return funct::natLog(argument);
    else if (functName == "sqrt") return funct::squareRoot(argument);
    else if (functName == "PI") return funct::PI();
    else if (functName == "!") return funct::factorial(argument);
    else if (functName == "abs") return funct::dabs(argument);
    else {
        throw std::runtime_error("Unknown function");
    }
}

double Evaluator::applyOperator(const std::string &op, const double left, const double right) {
    if (op == "+") return left + right;
    else if (op == "-") return left - right;
    else if (op == "*") return left * right;
    else if (op == "/") return left / right;
    else if (op == "^") return funct::power(left, right);
    else throw std::runtime_error("Unknown operator");
}


double ChrisMathParser::evaluate(const std::string &input) {
    const auto tokens = Tokenizer::tokenize(input);
    const auto postfix = Parser::infixToPostfix(tokens);
    return Evaluator::evaluatePostfix(postfix);
}
