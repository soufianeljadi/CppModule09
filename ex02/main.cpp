#include "PmergeMe.hpp"

int main(int ac, char **av)
{
    if (ac < 2)
    {
        std::cerr << "Usage: ./PmergeMe [numbers...]" << std::endl;
        return 1;
    }

    PmergeMe pmerge(av);
    //USING VECTOR
    std::cout << "Original vector: ";
    pmerge.printVector();
    pmerge.sortVector(pmerge._vector, 0, pmerge._vector.size() - 1);
    std::cout << "Sorted vector: ";
    pmerge.printVector();

    //USING LIST
    std::cout << "Original list: ";
    pmerge.printList();
    pmerge.sortList(pmerge._list);
    std::cout << "Sorted list: ";
    pmerge.printList();

    // std::cout << "Time to process a range of "<< list.size() <<" elements with std::list: " << elapsedTimeList << " seconds" << std::endl;
    // std::cout << "Time to process a range of "<< vector.size() <<" elements with std::list: " << elapsedTimeVector << " seconds" << std::endl;

    return 0;
}