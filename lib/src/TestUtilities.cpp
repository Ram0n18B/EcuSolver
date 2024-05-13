/**
 * @JohanMaldonado
 * @RamonBelandria
 */

#include <TestUtilities.hpp>

void assert_equal(const bool& current, const bool& expected) noexcept
{
    if(current != expected)
    {
        std::cerr << "Test failed!" << std::endl;
        std::cerr << "Current: ";
        if(current)
        {
            std::cerr << "true";
        }
        else
        {
            std::cerr << "false";
        }
        std::cerr << std::endl;
        std::cerr << "Expected: ";
        if(expected)
        {
            std::cerr << "true";
        }
        else
        {
            std::cerr << "false";
        }
        std::cerr << std::endl;
        abort();
    }
    std::cout << "Test ok!" << std::endl;
}