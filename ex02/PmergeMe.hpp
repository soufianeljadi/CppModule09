#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <vector>
#include <deque>
#include <string>
#include <sys/time.h>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <cstdlib>
#include <cctype>

class PmergeMe 
{
    private:
        std::vector<int> vec;
        std::deque<int> deq;
        
        void sortVector();
        void mergeInsertSortVector(std::vector<int>& arr, int left, int right);
        void insertSortVector(std::vector<int>& arr, int left, int right);
        void mergeVector(std::vector<int>& arr, int left, int mid, int right);
        
        void sortDeque();
        void mergeInsertSortDeque(std::deque<int>& arr, int left, int right);
        void insertSortDeque(std::deque<int>& arr, int left, int right);
        void mergeDeque(std::deque<int>& arr, int left, int mid, int right);
        
        int isNumber(const std::string& str);
        void printContainer(const std::vector<int>& container);
        void printContainer(const std::deque<int>& container);
        double getCurrentTime();
        
    public:
        PmergeMe();
        PmergeMe(const PmergeMe& other);
        ~PmergeMe();
        PmergeMe& operator=(const PmergeMe& other);
        
        void parseInput(int argc, char** argv);
        void sortAndDisplay();
};

#endif