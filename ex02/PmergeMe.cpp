#include "PmergeMe.hpp"


PmergeMe::PmergeMe() {}

PmergeMe::PmergeMe(const PmergeMe& other) 
{
    *this = other;
}

PmergeMe::~PmergeMe() {}

PmergeMe& PmergeMe::operator=(const PmergeMe& other) 
{
    if (this != &other) 
    {
        this->vec = other.vec;
        this->deq = other.deq;
    }
    return *this;
}

double PmergeMe::getCurrentTime() 
{
    struct timeval tv;

    if (gettimeofday(&tv, NULL) == -1) { 
        perror("gettimeofday failed");
        return 0.0;
    }
    return (tv.tv_sec * 1000000.0 + tv.tv_usec);
}

int  PmergeMe::isNumber(const std::string& str) 
{
    if (str.empty())
         return 0;
    std::string::const_iterator it = str.begin();
    if (*it == '-') 
    {
        if (str.length() == 1)
            return 0;
        ++it;
    }
    while (it != str.end()) 
    {
        if (!std::isdigit(*it))
             return 0;
        ++it;
    }
    return 1;
}

void PmergeMe::printContainer(const std::vector<int>& container) 
{
    for (std::vector<int>::const_iterator it = container.begin(); it != container.end(); ++it) 
    {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
}

void PmergeMe::printContainer(const std::deque<int>& container) 
{
    for (std::deque<int>::const_iterator it = container.begin(); it != container.end(); ++it) 
    {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
}

void PmergeMe::parseInput(int argc, char** argv) 
{
    for (int i = 1; i < argc; ++i) 
    {
        std::string numStr(argv[i]);
        if (!isNumber(numStr))
            throw std::runtime_error("Invalid number: " + numStr);
        
        std::istringstream iss(numStr);
        int num;
        iss >> num;
        
        if (num < 0)
            throw std::runtime_error("Negative number: " + numStr);
        
        vec.push_back(num);
        deq.push_back(num);
    }
}
#include <cstdio>
void PmergeMe::generateJacobsthalSequence(int n, std::vector<int>& jacob) 
{
    if (n >= 0) 
        jacob.push_back(0);
    if (n >= 1) 
        jacob.push_back(1);
    for (int i = 2; ; i++) 
    {
        int next = jacob[i-1] + 2 * jacob[i-2];         // J(i) = J(i-1) + 2*J(i-2)
        if (next > n) 
            break;
        jacob.push_back(next);
    }
}

void PmergeMe::mergePairsVector(std::vector<std::pair<int, int> >& pairs, std::vector<int>& mainChain, std::vector<int>& pend) 
{
    for (size_t i = 0; i < pairs.size(); ++i) 
    {
        if (pairs[i].first < pairs[i].second) 
        {
            mainChain.push_back(pairs[i].second);
            pend.push_back(pairs[i].first);
        }
        else
        {
            mainChain.push_back(pairs[i].first);
            pend.push_back(pairs[i].second);
        }
    }
    
    if (!pend.empty())
        mainChain.insert(mainChain.begin(), pend[0]);
}

void PmergeMe::binaryInsertVector(std::vector<int>& mainChain, std::vector<int>& pend) 
{
    std::vector<int> jacob;
    generateJacobsthalSequence(pend.size(), jacob);
    
    for (size_t i = 1; i < jacob.size(); ++i) 
    {
        int start = jacob[i-1];
        int end = jacob[i];
        
        for (int j = end; j > start; --j) 
        {
            if (static_cast<size_t>(j - 1) >= pend.size()) 
                continue;
            
            int value = pend[j - 1];

            std::vector<int>::iterator pos = std::lower_bound(mainChain.begin()
                                        ,std::lower_bound(mainChain.begin(),mainChain.end(), value)
                                        ,value);
            mainChain.insert(pos, value);
        }
    }
    
    if (!pend.empty() && pend.size() > static_cast<size_t>(jacob.back())) 
    {
        for (size_t j = jacob.back() + 1; j <= pend.size(); ++j) 
        {
            int value = pend[j - 1];

            std::vector<int>::iterator pos = std::lower_bound(mainChain.begin()
                                        ,std::lower_bound(mainChain.begin(),mainChain.end(), value)
                                        ,value);
            mainChain.insert(pos, value);
        }
    }
}

void PmergeMe::fordJohnsonVector(std::vector<int>& arr) 
{
    if (arr.size() <= 1) 
        return ;
    std::vector<std::pair<int, int> > pairs;
    for (size_t i = 0; i < arr.size() - 1; i += 2) 
    {
        pairs.push_back(std::make_pair(arr[i], arr[i+1]));
    }
    //large -> first
    for (size_t i = 0; i < pairs.size(); ++i) 
    {
        if (pairs[i].first < pairs[i].second)
            std::swap(pairs[i].first, pairs[i].second);
    }
    
    for (size_t i = 0; i < pairs.size(); ++i) 
    {
        for (size_t j = i + 1; j < pairs.size(); ++j) 
        {
            if (pairs[i].first > pairs[j].first) 
                std::swap(pairs[i], pairs[j]);
        }
    }
    
    std::vector<int> mainChain;
    std::vector<int> pend;
    mergePairsVector(pairs, mainChain, pend);
    
    if (arr.size() % 2 != 0) 
        pend.push_back(arr.back());
    
    binaryInsertVector(mainChain, pend);
    
    arr = mainChain;
}

void PmergeMe::sortVector() 
{
    if (vec.empty())
        return;
    fordJohnsonVector(vec);
}

void PmergeMe::mergePairsDeque(std::deque<std::pair<int, int> >& pairs, std::deque<int>& mainChain, std::deque<int>& pend) 
{
    for (size_t i = 0; i < pairs.size(); ++i) 
    {
        if (pairs[i].first < pairs[i].second) 
        {
            mainChain.push_back(pairs[i].second);
            pend.push_back(pairs[i].first);
        } else 
        {
            mainChain.push_back(pairs[i].first);
            pend.push_back(pairs[i].second);
        }
    }
    
    if (!pend.empty())
        mainChain.push_front(pend[0]);
}

void PmergeMe::binaryInsertDeque(std::deque<int>& mainChain, std::deque<int>& pend) 
{
    std::vector<int> jacob;
    generateJacobsthalSequence(pend.size(), jacob);
    
    for (size_t i = 1; i < jacob.size(); ++i) 
    {
        int start = jacob[i-1];
        int end = jacob[i];
        
        for (int j = end; j > start; --j) 
        {
            if (static_cast<size_t>(j - 1) >= pend.size())
                continue;
            
            int value = pend[j - 1];

            std::vector<int>::iterator pos = std::lower_bound(mainChain.begin()
                                        ,std::lower_bound(mainChain.begin(),mainChain.end(), value)
                                        ,value);
            mainChain.insert(pos, value);
        }
    }
    
    if (!pend.empty() && pend.size() > static_cast<size_t>(jacob.back())) 
    {
        for (size_t j = jacob.back() + 1; j <= pend.size(); ++j) 
        {
            int value = pend[j - 1];

            std::vector<int>::iterator pos = std::lower_bound(mainChain.begin()
                                        ,std::lower_bound(mainChain.begin(),mainChain.end(), value)
                                        ,value);
            mainChain.insert(pos, value);
        }
    }
}

void PmergeMe::fordJohnsonDeque(std::deque<int>& arr) 
{
    if (arr.size() <= 1)
        return;
    
    std::deque<std::pair<int, int> > pairs;
    for (size_t i = 0; i < arr.size() - 1; i += 2) 
    {
        pairs.push_back(std::make_pair(arr[i], arr[i+1]));
    }
    
    for (size_t i = 0; i < pairs.size(); ++i) 
    {
        if (pairs[i].first < pairs[i].second) 
        {
            std::swap(pairs[i].first, pairs[i].second);
        }
    }
    
    for (size_t i = 0; i < pairs.size(); ++i)
     {
        for (size_t j = i + 1; j < pairs.size(); ++j) 
        {
            if (pairs[i].first > pairs[j].first) 
            {
                std::swap(pairs[i], pairs[j]);
            }
        }
    }
    
    std::deque<int> mainChain;
    std::deque<int> pend;
    mergePairsDeque(pairs, mainChain, pend);
    
    if (arr.size() % 2 != 0)
        pend.push_back(arr.back());
    
    binaryInsertDeque(mainChain, pend);
    arr = mainChain;
}

void PmergeMe::sortDeque() 
{
    if (deq.empty()) 
        return;
    fordJohnsonDeque(deq);
}

void PmergeMe::sortAndDisplay() 
{
    std::vector<int> vecCopy = vec;
    std::deque<int> deqCopy = deq;
    
    std::cout << "Before: ";
    printContainer(vec);
    
    double startVec = getCurrentTime();
    fordJohnsonVector(vecCopy);
    double endVec = getCurrentTime();
    double vectorTime = endVec - startVec;
    
    double startDeq = getCurrentTime();
    fordJohnsonDeque(deqCopy);
    double endDeq = getCurrentTime();
    double dequeTime = endDeq - startDeq;
    
    vec = vecCopy;
    deq = deqCopy;
    
    std::cout << "After: ";
    printContainer(vec);
    
    std::cout.precision(5);
    std::cout << std::fixed;
    std::cout << "Time to process a range of " << vec.size() 
              << " elements with std::vector: " << vectorTime << " us" << std::endl;
    std::cout << "Time to process a range of " << deq.size() 
              << " elements with std::deque: " << dequeTime << " us" << std::endl;
}