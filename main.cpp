#include "views_fun.h"
#include <map>

// Problems
// Take a list of the numbers [1,100] and square every 5th number
// Generate all powers of two greater less than 10,000
// Print all numbers less than 10,000 that are palindrome numbers (the same forward and backwards)
// Sum two vectors index by index

int main()
{
    auto vector = std::vector<int> { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    auto array = std::list<double> {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    auto map = std::map<int, std::string>{{1, "one"}, {2, "two"}};
    views16(vector);
    views12(map);


//    Part 3
//    views3(vector);
//    std::cout << "Separating" << std::endl;
//    views3(array);

    return 0;
}


