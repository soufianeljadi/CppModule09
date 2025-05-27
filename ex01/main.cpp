#include "RPN.hpp"


int main(int ac, char **av)
{
    if (ac != 2)
    {
        std::cerr << "Usage: ./RPN [Polish mathematical]" << std::endl;
        return 1;
    }
    RPN rpn(av[1]);
    rpn.parseFile();

    return 0;
}