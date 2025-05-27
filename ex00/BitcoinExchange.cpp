#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange(const std::string &filename) : _filename(filename)
{

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
        _input = other._input;
    }
    return *this;
}

void BitcoinExchange::parseFile()
{
    std::fstream dataFile("data.csv");
    if (!dataFile.is_open())
    {
        std::cerr << "Error: could not open data file." << std::endl;
        return ;
    }
    std::string line;
    std::getline(dataFile, line);
    while(std::getline(dataFile, line))
    {
        std::string date = line.substr(0, 10);
        std::string value = line.substr(11);

        char* endptr;
        double exchange_rate = std::strtod(value.c_str(), &endptr);
        _data[date] = exchange_rate;
    }   

    std::string input_line;
    std::fstream inputFile(_filename.c_str());
    if (!inputFile.is_open())
    {
        std::cerr << "Error: could not open input file." << std::endl;
        return ;
    }
    std::getline(inputFile, input_line);
    if (input_line != "date | value")
    {
        std::cerr << "Error: invalid file format." << std::endl;
        return ;
    }
    while (std::getline(inputFile, input_line))
    {
        if( input_line.size() < 14 || input_line[10] != ' ' || input_line[11] != '|' || input_line[12] != ' ')
        {
            std::cerr << "Error: bad input => " << input_line << std::endl;
            continue;
        }
        std::string date = input_line.substr(0, 10);
        std::string value = input_line.substr(13);
        if (validateDate(date) != 0)
            continue;
        if (validateValue(value) != 0)
            continue;
        char* endptr;
        double num = std::strtod(value.c_str(), &endptr);
        _input[date] = num;

        std::map<std::string, double>::iterator it = _data.lower_bound(date);
        if (it != _data.end() && it->first == date)
        {
            std::cout << date << " => " << value << " = " << it->second * num << std::endl;
            continue;
        }
        if (it == _data.end())
        {
            --it;
        }
        else if (it != _data.begin())
        {
            --it;
        }
        std::cout << date << " => " << value << " = " << it->second * num << std::endl;
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
    int c = 0;
    float val = std::strtof(value.c_str(), &endptr);

    if(isdigit(value[0]) == 0 && value[0] != '-' && value[0] != '+')
    {
        std::cerr << "Error: bad input => " << value << std::endl;
        return 1; 
    }
    for(size_t i = 0; i < value.size(); i++)
    {
        if(value[i] == '.')
            c += 1;
        if ((isdigit(value[i]) == 0 && value[i] != '.' && value[i] != '+' && value[i] != '-') 
            || c > 1 || value[0] == '.')
        {
            std::cerr << "Error: bad input => " << value << std::endl;
            return 1; 
        }
    }
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