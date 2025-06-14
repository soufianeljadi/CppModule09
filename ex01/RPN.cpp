#include "RPN.hpp"

RPN::RPN(const std::string &expression) : _expression(expression)
{
}
RPN::~RPN()
{
}
RPN::RPN(const RPN &other) : _expression(other._expression)
{
}
RPN &RPN::operator=(const RPN &other)
{
    if (this != &other)
    {
        _expression = other._expression;
    }
    return *this;
}

void RPN::parseFile()
{
    if (calculate() == -1)
        std::cerr << "Error: Invalid expression." << std::endl;
}

int RPN::calculate()
{
    std::stack<int> stack;
    for (size_t i = 0; i < _expression.size(); i++)
    {
        char c = _expression[i];
        if (isdigit(c))
            stack.push(c - '0');
        else if (isOperator(c))
        {
            if (stack.size() < 2)
                return -1; 
            int b = stack.top();
            stack.pop();
            int a = stack.top();
            stack.pop();
            stack.push(applyOperation(a, b, c));
        }
        else if (c != ' ')
            return -1; 
    }
    if (stack.size() != 1)
        return -1; 
    std::cout << stack.top() << std::endl;
    return 0;
}

bool RPN::isOperator(char c)
{
    return c == '+' || c == '-' || c == '*' || c == '/';
}

int RPN::applyOperation(int a, int b, char op)
{
    switch (op)
    {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/':
            if (b == 0)
            {
                std::cerr << "Error: Division by zero." << std::endl;
                return -1;
            }
            return a / b;
        default:
            return -1;
    }
}