//
// Created by Tom Marks on 10/26/23.
//

#ifndef VIEWS_FUN_VIEWS_FUN_H
#define VIEWS_FUN_VIEWS_FUN_H
#include <algorithm>
#include <array>
#include <iostream>
#include <list>
#include <numeric>
#include <ranges>
#include <string>
#include <vector>

auto square(auto input)
{
    return input * input;
}

[[maybe_unused]] auto non_range1(const std::vector<int>& vector)
{
    // Unsafe and complicated :(
    for (int i = 0; i <= vector.size(); i++) {
        std::cout << square(vector[i]) << std::endl;
    }
}

[[maybe_unused]] auto non_range2(const std::vector<int>& vector)
{
    // Catches errors at runtime
    for (int i = 0; i <= vector.size(); i++) {
        std::cout << square(vector.at(i)) << std::endl;
    }
}

[[maybe_unused]] auto non_range3(const std::vector<int>& vector)
{
    // Is correct
    for (const auto& value : vector) {
        std::cout << square(value) << std::endl;
    }
}

[[maybe_unused]] auto non_range4(const std::vector<int>& vector)
{
    // What is the safe way for this since we need two indexes?
    for (int i = 1; i <= vector.size(); i++) {
        std::cout << square(vector.at(i)) - square(vector.at(i - 1)) << std::endl;
    }
}

[[maybe_unused]] auto views1(const std::vector<int>& vector)
{
    // Ranges fix buffer overflows and simplify for loops
    const auto view = vector | std::views::transform([](const auto& input) {
        return square(input);
    });
    // The view isn't computed until it is required, they are lazy.
    // This helps with chaining...
    for (const auto& value : view) {
        std::cout << value << std::endl;
    }
}

[[maybe_unused]] auto views2(const std::vector<int>& vector)
{
    // Views can separate out the steps of a calculation
    const auto view = vector
        | std::views::transform([](const auto& input) { return square(input); }) // square the elements
        | std::views::adjacent<2> // take elements that are next to each other
        | std::views::transform([](const auto& input) { // Get the difference between elements
        return std::get<1>(input) - std::get<0>(input);
    });

    // The view isn't computed until it is required, they are lazy.
    // This helps with chaining...
    for (const auto& value : view) {
        std::cout << value << std::endl;
    }
}

// They're good for generic programming as well
[[maybe_unused]] auto views3(const auto& vector)
{
    // Views can separate out the steps of a calculation
    const auto view = vector
        | std::views::transform([](const auto& input) { return square(input); }) // square the elements
        | std::views::adjacent<2> // take elements that are next to each other
        | std::views::transform([](const auto& input) { // Get the difference between elements
        return std::get<1>(input) - std::get<0>(input);
    });

    // The view isn't computed until it is required, they are lazy.
    // This helps with chaining...
    for (const auto& value : view) {
        std::cout << value << std::endl;
    }
}

// They can also filter out elements that don't match a predicate
[[maybe_unused]] auto views4(const auto& vector)
{
    auto view = vector
        | std::views::filter([](const auto& input){return input % 2 == 0;})
        | std::views::transform([](const auto& input) { return square(input); }); // square the elements

    for (const auto& value : view) {
        std::cout << value << std::endl;
    }
}

// They can also take an initial amount of elements, first 3 elements here
[[maybe_unused]] auto views5(const auto& vector)
{
    auto view = vector
        | std::views::take(3)
        | std::views::transform([](const auto& input) { return square(input); }); // square the elements

    for (const auto& value : view) {
        std::cout << value << std::endl;
    }
}

// They can also drop an initial amount of elements, first 3 elements here
[[maybe_unused]] auto views6(const auto& vector)
{
    auto view = vector
        | std::views::drop(3)
        | std::views::transform([](const auto& input) { return square(input); }); // square the elements

    for (const auto& value : view) {
        std::cout << value << std::endl;
    }
}

// Can also take or drop until a condition
[[maybe_unused]] auto views7(const auto& vector)
{
    auto view = vector
        | std::views::drop_while([](const auto& value){return value > 6;})
        | std::views::transform([](const auto& input) { return square(input); }); // square the elements

    for (const auto& value : view) {
        std::cout << value << std::endl;
    }
}

// Can split an iterable
[[maybe_unused]] auto views8()
{
    const auto input = std::string("We finally have split!");
    auto view = std::views::split(input, std::string(" "));
    for(const auto& value : view){
        std::cout << std::string_view(value) << std::endl;
    }
}

// Or can join it
[[maybe_unused]] auto views9()
{
    auto input = std::vector<std::string>{"Let's", "join", "now"};
    auto view = input | std::views::join_with(std::string("-"));
    auto string = std::string(view.begin(), view.end());
    std::cout << string << std::endl;
}

// Can reverse
[[maybe_unused]] auto views10(const auto& vector)
{
    auto view = vector
        | std::views::reverse
        | std::views::transform([](const auto& input) { return square(input); }); // square the elements

    for (const auto& value : view) {
        std::cout << value << std::endl;
    }
}

// Can take keys or values
[[maybe_unused]] auto views11(const auto& map)
{
    auto view = map
        | std::views::keys; // square the elements

    for (const auto& value : view) {
        std::cout << value << std::endl;
    }
}

// Can take keys or values
[[maybe_unused]] auto views12(const auto& map)
{
    auto view = map
        | std::views::values; // square the elements

    for (const auto& value : view) {
        std::cout << value << std::endl;
    }
}

// Can reverse
[[maybe_unused]] auto views13(const auto& vector)
{
    auto view = vector
        | std::views::reverse
        | std::views::transform([](const auto& input) { return square(input); }); // square the elements

    for (const auto& value : view) {
        std::cout << value << std::endl;
    }
}

[[maybe_unused]] auto views14(const auto& vector)
{
    auto view = vector
        | std::views::enumerate
        | std::views::transform([](const auto& pair) {
            auto [index, value] = pair;
            return std::make_pair(index, square(value));
        }); // enumerate and then square the elements

    for (const auto& [index, value] : view) {
        std::cout << "Index: " << index << ", Value: " << value << std::endl;
    }
}

// Can also zip
[[maybe_unused]] auto views15(const auto& vector1, const auto& vector2)
{
    auto view = std::views::zip(vector1, vector2); // enumerate and then square the elements

    for (const auto& [value1, value2] : view) {
        std::cout << "Value 1: " << value1 << ", Value 2: " << value2 << std::endl;
    }
}

// Can also do normal things like accumulate them
[[maybe_unused]] auto views16(const auto& vector)
{
    auto view = vector | std::views::transform([](int value) {
            return square(value);
        });
    auto sum = std::accumulate(view.begin(), view.end(), 0);

    std::cout << sum << std::endl;
}

// Can also generate some ints
[[maybe_unused]] auto views17()
{
    for (const std::weakly_incrementable auto& i : std::ranges::iota_view{1, 10}){
        std::cout << i << ' ';
    }
    std::cout << '\n';
}

#endif // VIEWS_FUN_VIEWS_FUN_H
