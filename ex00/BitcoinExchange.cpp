#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange(const std::string &filename) : _filename(filename)
{
    _file.open(_filename);
    if (!_file.is_open())
    {
        std::cerr << "Error: could not open file." << std::endl;
        exit(1);
    }
}

BitcoinExchange::~BitcoinExchange()
{
    if (_file.is_open())
        _file.close();
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &other) : _filename(other._filename), _file(other._file), _data(other._data)
{
}

BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &other)
{
    if (this != &other)
    {
        _filename = other._filename;
        _file = other._file;
        _data = other._data;
    }
    return *this;
}

void BitcoinExchange::parseFile()
{
    std::string line;
    while (std::getline(_file, line))
    {
        std::istringstream iss(line);
        std::string date, value;
        if (!(iss >> date >> value))
            continue;
        validateDate(date);
        validateValue(value);
        _data[date] = std::stof(value);
    }
}

void BitcoinExchange::validateDate(const std::string &date)
{
    if (date.size() != 10 || date[4] != '-' || date[7] != '-')
    {
        std::cerr << "Error: bad input => " << date << std::endl;
        exit(1);
    }
}

void BitcoinExchange::validateValue(const std::string &value)
{
    try
    {
        float val = std::stof(value);
        if (val < 0)
        {
            std::cerr << "Error: not a positive number." << std::endl;
            exit(1);
        }
        if (val > 1000)
        {
            std::cerr << "Error: value should be lower than 1000." << std::endl;
            exit(1);
        }
    }
    catch (const std::invalid_argument &e)
    {
        std::cerr << "Error: not a number." << std::endl;
        exit(1);
    }
}

