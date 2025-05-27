#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <iterator>


class PmergeMe
{
    public:

        std::vector<int> _vector;
        std::list<int> _list;

        PmergeMe(char **av);
        PmergeMe(const PmergeMe &other);
        PmergeMe &operator=(const PmergeMe &other);
        ~PmergeMe();

        void sortVector(std::vector<int> &vec, size_t left, size_t right);
        void sortList(std::list<int> &lst);

        void printVector() const;
        void printList() const;

};

#endif