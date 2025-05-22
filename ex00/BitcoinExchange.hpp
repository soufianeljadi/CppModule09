#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <iostream>
#include <fstream>
#include <string>
#include <map>


class BitcoinExchange 
{
    private:
        std::string _filename;
        std::map<std::string, float> _data;
    public:
        BitcoinExchange(const std::string &filename);
        ~BitcoinExchange();
        BitcoinExchange(const BitcoinExchange &other);
        BitcoinExchange &operator=(const BitcoinExchange &other);

        void parseFile();
        void validateDate(const std::string &date);
        void validateValue(const std::string &value);

};


#endif