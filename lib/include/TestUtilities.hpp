/**
 * @JohanMaldonado
 * @RamonBelandria
 */

#pragma once

#include <IOUtilities.hpp>

void assert_equal(const bool& current, const bool& expected) noexcept;

template <typename T>
void assert_equal(const T& current, const T& expected) noexcept
{
    if(current != expected)
    {
        std::cerr << "Test failed!" << std::endl;
        std::cerr << "Current: ";
        std::cerr << current << std::endl;
        std::cerr << "Expected: ";
        std::cerr << expected << std::endl;
        abort();
    }
    std::cout << "Test ok!" << std::endl;
}