#include "BitcoinExchange.hpp"

int main(int ac, char **av)
{
    if(ac != 2)
    {
        std::cerr << "Error: could not open file." << std::endl;
        return 1;
    }
    BitcoinExchange bitcoinExchange(av[1]);
    bitcoinExchange.parseFile();

    return 0;
}