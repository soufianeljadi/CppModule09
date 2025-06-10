#include "PmergeMe.hpp"
#include <iostream>

int main(int argc, char** argv) {
    if (argc < 2) {
        std::cerr << "Error: No input provided" << std::endl;
        return 1;
    }
    
    try {
        PmergeMe sorter;
        sorter.parseInput(argc, argv);
        sorter.sortAndDisplay();
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}