#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <vector>
#include <deque>
#include <string>
#include <sys/time.h>
#include <algorithm>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <cstdlib>
#include <cctype>
// #include <utility>


class PmergeMe 
{
    private:
        std::vector<int> vec;
        std::deque<int> deq;
        
        void sortVector();
        void fordJohnsonVector(std::vector<int>& arr);
        void mergePairsVector(std::vector<std::pair<int, int> >& pairs, std::vector<int>& mainChain, std::vector<int>& pend);
        void binaryInsertVector(std::vector<int>& mainChain, std::vector<int>& pend);
        
        void sortDeque();
        void fordJohnsonDeque(std::deque<int>& arr);
        void mergePairsDeque(std::deque<std::pair<int, int> >& pairs, std::deque<int>& mainChain, std::deque<int>& pend);
        void binaryInsertDeque(std::deque<int>& mainChain, std::deque<int>& pend);
        
        void generateJacobsthalSequence(int n, std::vector<int>& jacob);

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