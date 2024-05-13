/**
 * @JohanMaldonado
 * @RamonBelandria
 */

#include <IOUtilities.hpp>

std::ostream& operator<< (std::ostream& out, const Polynomial& pn) noexcept
{
    if(pn.empty())
    {
        out << "{}";
        return out;
    }
    out<< "{";
    out << *(pn.get_container()[0]);
    for(size_t i = 1; i < pn.size(); ++i)
    {
        out << ", ";
        out << *(pn.get_container()[i]);
    }
    out << "}";
    return out;
}

std::ostream& operator<< (std::ostream& out, const std::vector<double>& doubles) noexcept
{
    if(doubles.empty())
    {
        out << "{}";
        return out;
    }
    out << "{";
    out << doubles[0];
    for(size_t i = 1; i < doubles.size(); ++i)
    {
        out << "; ";
        out << doubles[i];
    }
    out << "}";
    return out;
}