#include "PmergeMe.hpp"

///////////////////////////////////////////////////////////////CANONICAL

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

///////////////////////////////////////////////////////////////UTILS

double PmergeMe::getCurrentTime() 
{
    struct timeval tv;

    if (gettimeofday(&tv, NULL) == -1) { 
        std::cerr << "gettimeofday failed" << std::endl;
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
        long int num;

        iss >> num;
        if (num < 0 || num >= 2147483647)
            throw std::runtime_error("Value out of range: "  + numStr +", try a valid possitive integer ");
        
        vec.push_back(num);
        deq.push_back(num);
    }
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

///////////////////////////////////////////////////////////////VECTOR

void PmergeMe::generateJacobsthalInsertionOrderV(int n, std::vector<int>& jacob) 
{
    if (n >= 0)
        jacob.push_back(0);
    if (n >= 1)
        jacob.push_back(1);

    int a = 1, b = 1;
    while (771) 
    {
        int next = a + 2 * b;
        if (next > n)
            break;

        for (int j = next - 1; j > a; --j) 
        {
            if (j <= n)
                jacob.push_back(j);
        }
        jacob.push_back(next);
        a = b;
        b = next;
    }
}

void PmergeMe::mergeVector(std::vector<std::pair<int, int> >& pairs, int left, int mid, int right) 
{
    int n1 = mid - left + 1;
    int n2 = right - mid;

    std::vector<std::pair<int, int> > L(n1), R(n2);

    for (int i = 0; i < n1; i++)
        L[i] = pairs[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = pairs[mid + 1 + j];

    int i = 0, j = 0, k = left;
    
    while (i < n1 && j < n2) 
    {
        if (L[i].first <= R[j].first) 
        {
            pairs[k] = L[i];
            i++;
        } 
        else {
            pairs[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) 
    {
        pairs[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) 
    {
        pairs[k] = R[j];
        j++;
        k++;
    }
}

void PmergeMe::recursiveMergeSortVector(std::vector<std::pair<int, int> >& pairs, int left, int right) 
{
    if (left < right) 
    {
        int mid = left + (right - left) / 2;
        recursiveMergeSortVector(pairs, left, mid);
        recursiveMergeSortVector(pairs, mid + 1, right);
        mergeVector(pairs, left, mid, right);
    }
}

void PmergeMe::binaryInsertVector(std::vector<int>& mainChain, std::vector<int>& pend) 
{
    std::vector<int> insertionOrder;
    generateJacobsthalInsertionOrderV(pend.size(), insertionOrder);
    
    for (size_t i = 0; i < insertionOrder.size(); ++i) 
    {
        int index = insertionOrder[i];
        
        if (index >= 0 && index < (int)pend.size()) 
        {
            int value = pend[index];
            
            std::vector<int>::iterator pos = std::lower_bound(
                mainChain.begin(), 
                mainChain.end(), 
                value);
                
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
    
    
    recursiveMergeSortVector(pairs, 0, pairs.size() - 1);
    
    std::vector<int> mainChain;
    std::vector<int> pend;
    for (size_t i = 0; i < pairs.size(); ++i) 
    {
        mainChain.push_back(pairs[i].first);
        pend.push_back(pairs[i].second);
    }
    
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

///////////////////////////////////////////////////////////////DEQUE

void PmergeMe::generateJacobsthalInsertionOrderD(int n, std::deque<int>& jacob) 
{
    if (n >= 0)
        jacob.push_back(0);
    if (n >= 1)
        jacob.push_back(1);

    int a = 1, b = 1;
    while (771) 
    {
        int next = a + 2 * b;
        if (next > n)
            break;

        for (int j = next - 1; j > a; --j) 
        {
            if (j <= n)
                jacob.push_back(j);
        }
        jacob.push_back(next);
        a = b;
        b = next;
    }
}

void PmergeMe::mergeDeque(std::deque<std::pair<int, int> >& pairs, int left, int mid, int right) 
{
    int n1 = mid - left + 1;
    int n2 = right - mid;

    std::deque<std::pair<int, int> > L(n1), R(n2);

    for (int i = 0; i < n1; i++)
        L[i] = pairs[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = pairs[mid + 1 + j];

    int i = 0, j = 0, k = left;
    
    while (i < n1 && j < n2) 
    {
        if (L[i].first <= R[j].first) 
        {
            pairs[k] = L[i];
            i++;
        } 
        else 
        {
            pairs[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) 
    {
        pairs[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) 
    {
        pairs[k] = R[j];
        j++;
        k++;
    }
}

void PmergeMe::recursiveMergeSortDeque(std::deque<std::pair<int, int> >& pairs, int left, int right) 
{
    if (left < right) 
    {
        int mid = left + (right - left) / 2;
        recursiveMergeSortDeque(pairs, left, mid);
        recursiveMergeSortDeque(pairs, mid + 1, right);
        mergeDeque(pairs, left, mid, right);
    }
}

void PmergeMe::binaryInsertDeque(std::deque<int>& mainChain, std::deque<int>& pend) 
{
    std::deque<int> insertionOrder;
    generateJacobsthalInsertionOrderD(pend.size(), insertionOrder);
    
    for (size_t i = 0; i < insertionOrder.size(); ++i) 
    {
        int index = insertionOrder[i];
        
        if (index >= 0 && index < (int)pend.size()) 
        {
            int value = pend[index];
            
            std::deque<int>::iterator pos = std::lower_bound(
                mainChain.begin(), 
                mainChain.end(), 
                value);
                
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
    
    recursiveMergeSortDeque(pairs, 0, pairs.size() - 1);
    
    std::deque<int> mainChain;
    std::deque<int> pend;
    
    for (size_t i = 0; i < pairs.size(); ++i) 
    {
        mainChain.push_back(pairs[i].first);
        pend.push_back(pairs[i].second);
    }
    
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

