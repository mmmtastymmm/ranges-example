#include <iostream>
#include <ranges>
#include <vector>

auto square(auto input){
    return input * input;
}

[[maybe_unused]] auto non_range1(const std::vector<int>& input){
    // Unsafe and complicated :(
    for(int i = 0; i <= input.size(); i++){
        std::cout << square(input[i]) << std::endl;
    }
}

[[maybe_unused]] auto non_range2(const std::vector<int>& input){
    // Catches errors at runtime
    for(int i = 0; i <= input.size(); i++){
        std::cout << square(input.at(i)) << std::endl;
    }
}

[[maybe_unused]] auto non_range3(const std::vector<int>& input){
    // Is correct
    for(const auto& value : input){
        std::cout << square(value) << std::endl;
    }
}

[[maybe_unused]] auto non_range4(const std::vector<int>& input){
    // What is the safe way for this since we need two indexes?
    for(int i = 1; i <= input.size(); i++){
        std::cout << square(input.at(i)) - square(input.at(i - 1)) << std::endl;
    }
}

[[maybe_unused]] auto ranges1(const std::vector<int>& input){
    // What is the safe way for this since we need two indexes?

}






int main() {
    auto vector = std::vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    non_range1(vector);
    return 0;
}
