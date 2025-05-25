#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange(const std::string &filename) : _filename(filename)
{
    parseFile();

}

BitcoinExchange::~BitcoinExchange()
{

}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &other) : _filename(other._filename)
{
}

BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &other)
{
    if (this != &other)
    {
        _filename = other._filename;
        _data = other._data;
    }
    return *this;
}

void BitcoinExchange::parseFile()
{
    std::string line;
    std::fstream inputFile(_filename.c_str());
    if (!inputFile.is_open())
    {
        std::cerr << "Error: could not open file." << std::endl;
        return ;
    }
    // Skipi lia line lwl "date | value"
    std::getline(inputFile, line);
    if (line != "date | value")
    {
        std::cerr << "Error: invalid file format." << std::endl;
        return ;
    }
    while (std::getline(inputFile, line))
    {
        std::string date = line.substr(0, 10);
        std::string value = line.substr(11);
        if (validateDate(date) != 0)
            continue;
        if (validateValue(value) != 0)
            continue;
        char* endptr;
        double num = std::strtod(value.c_str(), &endptr);
        _data[date] = num;
        std::cout << date << " => " << value << " = " << num << std::endl;
    }
}

int BitcoinExchange::validateDate(const std::string &date)
{
    if (date.size() != 10 || date[4] != '-' || date[7] != '-')
    {

        std::cerr << "Error: bad input => " << date << std::endl;
        return 1; 
    }
    std::string yearStr = date.substr(0, 4);
    std::string monthStr = date.substr(5, 2);
    std::string dayStr = date.substr(8, 2);

    char* endptr;
    int year = std::strtol(yearStr.c_str(), &endptr, 10);
    if (*endptr != '\0' || year < 2009 || year > 2023)
    {
        std::cerr << "Error: bad input => " << date << std::endl;
        return 1; 
    }
    
    int month = std::strtol(monthStr.c_str(), &endptr, 10);
    if (*endptr != '\0' || month < 1 || month > 12)
    {
        std::cerr << "Error: bad input => " << date << std::endl;
        return 1; 
    }
    
    int day = std::strtol(dayStr.c_str(), &endptr, 10);
    if (*endptr != '\0' || day < 1 || day > 31)
    {
        std::cerr << "Error: bad input => " << date << std::endl;
        return 1; 
    }
    return 0;
}

int BitcoinExchange::validateValue(const std::string &value)
{
    char* endptr;
    float val = std::strtof(value.c_str(), &endptr);

    if (val < 0)
    {
        std::cerr << "Error: not a positive number." << std::endl;
        return 1; 
    }
    if (val > 1000)
    {
        std::cerr << "Error: too large a number." << std::endl;
        return 1;
    }
    return 0;
}