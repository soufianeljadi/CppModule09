#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <iostream>
#include <fstream>
#include <map>
#include <cstdlib>

class BitcoinExchange 
{
    private:
        std::string _filename;
        std::map<std::string, double> _data;
        std::map<std::string, double> _input;
    public:
        BitcoinExchange(const std::string &filename);
        BitcoinExchange(const BitcoinExchange &other);
        BitcoinExchange &operator=(const BitcoinExchange &other);
        ~BitcoinExchange();

        void parseFile();
        int validateDate(const std::string &date);
        int validateValue(const std::string &value);

};


#endif