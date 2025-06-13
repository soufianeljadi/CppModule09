#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <vector>
#include <deque>

#include <sys/time.h>
#include <iostream>
#include <sstream>


class PmergeMe 
{
    private:
        std::vector<int> vec;
        std::deque<int> deq;
        
        void sortVector();
        void generateJacobsthalInsertionOrderV(int n, std::vector<int>& jacob);
        void fordJohnsonVector(std::vector<int>& arr);
        void recursiveMergeSortVector(std::vector<std::pair<int, int> >& pairs, int left, int right);
        void mergeVector(std::vector<std::pair<int, int> >& pairs, int left, int mid, int right);
        void binaryInsertVector(std::vector<int>& mainChain, std::vector<int>& pend);
        
        void sortDeque();
        void generateJacobsthalInsertionOrderD(int n, std::deque<int>& jacob);
        void fordJohnsonDeque(std::deque<int>& arr);
        void recursiveMergeSortDeque(std::deque<std::pair<int, int> >& pairs, int left, int right);
        void mergeDeque(std::deque<std::pair<int, int> >& pairs, int left, int mid, int right);
        void binaryInsertDeque(std::deque<int>& mainChain, std::deque<int>& pend);
        
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