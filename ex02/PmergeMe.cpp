#include "PmergeMe.hpp"

PmergeMe::PmergeMe(char **av)
{
    for (int i = 1; av[i]; ++i)
    {
        int num = std::atoi(av[i]);
        if (num < 0)
        {
            std::cerr << "Error: negative numbers are not allowed." << std::endl;
            exit(1);
        }
        _vector.push_back(num);
        _list.push_back(num);
    }

}

PmergeMe::PmergeMe(const PmergeMe &other) : _vector(other._vector), _list(other._list)
{
}

PmergeMe &PmergeMe::operator=(const PmergeMe &other)
{
    if (this != &other)
    {
        _vector = other._vector;
        _list = other._list;
    }
    return *this;
}

PmergeMe::~PmergeMe()
{
}

void PmergeMe::sortVector(std::vector<int> &vec, size_t left, size_t right)
{
    (void)vec; // To avoid unused parameter warning
    (void)left; // To avoid unused parameter warning
    (void)right; // To avoid unused parameter warning
}

void PmergeMe::sortList(std::list<int> &lst)
{
    (void)lst; // To avoid unused parameter warning

}

void PmergeMe::printVector() const
{
    for (size_t i = 0; i < _vector.size(); ++i)
    {
        int num = _vector[i];
        if (i == _vector.size() - 1)
            std::cout << num;
        else
            std::cout << num << " ";
    }
    std::cout << std::endl;
}
void PmergeMe::printList() const
{
    for (std::list<int>::const_iterator it = _list.begin(); it != _list.end(); ++it)
    {
        int num = *it;
        std::cout << num;
        ++it;
        if (it != _list.end())
            std::cout << " ";
        else
            --it; 
    }
    std::cout << std::endl;
}
