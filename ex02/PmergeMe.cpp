#include "PmergeMe.hpp"


PmergeMe::PmergeMe() {}

PmergeMe::PmergeMe(const PmergeMe& other) 
{
    *this = other;
}

PmergeMe::~PmergeMe() {}

PmergeMe& PmergeMe::operator=(const PmergeMe& other) 
{
    if (this != &other) {
        this->vec = other.vec;
        this->deq = other.deq;
    }
    return *this;
}

double PmergeMe::getCurrentTime() 
{
    struct timeval tv;

    gettimeofday(&tv, NULL);
    return (tv.tv_sec * 1000000.0 + tv.tv_usec);
}

int PmergeMe::isNumber(const std::string& str) 
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
        std::cout << *it << " ";
    std::cout << std::endl;
}

void PmergeMe::printContainer(const std::deque<int>& container) 
{
    for (std::deque<int>::const_iterator it = container.begin(); it != container.end(); ++it) 
        std::cout << *it << " ";
    std::cout << std::endl;
}

void PmergeMe::parseInput(int argc, char** argv) {
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

void PmergeMe::insertSortVector(std::vector<int>& arr, int left, int right) 
{
    for (int i = left + 1; i <= right; ++i) 
    {
        int key = arr[i];
        int j = i - 1;
        
        while (j >= left && arr[j] > key) 
        {
            arr[j + 1] = arr[j];
            --j;
        }
        arr[j + 1] = key;
    }
}

void PmergeMe::mergeVector(std::vector<int>& arr, int left, int mid, int right) 
{
    int n1 = mid - left + 1;
    int n2 = right - mid;
    
    std::vector<int> L(n1), R(n2);
    
    for (int i = 0; i < n1; ++i)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; ++j)
        R[j] = arr[mid + 1 + j];
    
    int i = 0, j = 0, k = left;
    
    while (i < n1 && j < n2) 
    {
        if (L[i] <= R[j]) 
        {
            arr[k] = L[i];
            ++i;
        } else 
        {
            arr[k] = R[j];
            ++j;
        }
        ++k;
    }
    
    while (i < n1) 
    {
        arr[k] = L[i];
        ++i;
        ++k;
    }
    
    while (j < n2) 
    {
        arr[k] = R[j];
        ++j;
        ++k;
    }
}

void PmergeMe::mergeInsertSortVector(std::vector<int>& arr, int left, int right) 
{
    if (right - left > 16) 
    {
        int mid = left + (right - left) / 2;
        mergeInsertSortVector(arr, left, mid);
        mergeInsertSortVector(arr, mid + 1, right);
        mergeVector(arr, left, mid, right);
    } else
        insertSortVector(arr, left, right);
}

void PmergeMe::sortVector() 
{
    if (vec.empty()) 
        return;
    mergeInsertSortVector(vec, 0, vec.size() - 1);
}

void PmergeMe::insertSortDeque(std::deque<int>& arr, int left, int right) 
{
    for (int i = left + 1; i <= right; ++i) 
    {
        int key = arr[i];
        int j = i - 1;
        
        while (j >= left && arr[j] > key) 
        {
            arr[j + 1] = arr[j];
            --j;
        }
        arr[j + 1] = key;
    }
}

void PmergeMe::mergeDeque(std::deque<int>& arr, int left, int mid, int right) 
{
    int n1 = mid - left + 1;
    int n2 = right - mid;
    
    std::deque<int> L(n1), R(n2);
    
    for (int i = 0; i < n1; ++i)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; ++j)
        R[j] = arr[mid + 1 + j];
    
    int i = 0, j = 0, k = left;
    
    while (i < n1 && j < n2) 
    {
        if (L[i] <= R[j]) 
        {
            arr[k] = L[i];
            ++i;
        } else 
        {
            arr[k] = R[j];
            ++j;
        }
        ++k;
    }
    
    while (i < n1) 
    {
        arr[k] = L[i];
        ++i;
        ++k;
    }
    
    while (j < n2) 
    {
        arr[k] = R[j];
        ++j;
        ++k;
    }
}

void PmergeMe::mergeInsertSortDeque(std::deque<int>& arr, int left, int right) 
{
    if (right - left > 16) 
    {
        int mid = left + (right - left) / 2;
        mergeInsertSortDeque(arr, left, mid);
        mergeInsertSortDeque(arr, mid + 1, right);
        mergeDeque(arr, left, mid, right);
    } else
        insertSortDeque(arr, left, right);
}

void PmergeMe::sortDeque() 
{
    if (deq.empty())
        return;
    mergeInsertSortDeque(deq, 0, deq.size() - 1);
}

void PmergeMe::sortAndDisplay() 
{
    std::vector<int> vecCopy = vec;
    std::deque<int> deqCopy = deq;
    
    std::cout << "Before: ";
    printContainer(vec);
    
    double startVec = getCurrentTime();
    mergeInsertSortVector(vecCopy, 0, vecCopy.size() - 1);
    double endVec = getCurrentTime();
    double vectorTime = endVec - startVec;
    
    double startDeq = getCurrentTime();
    mergeInsertSortDeque(deqCopy, 0, deqCopy.size() - 1);
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