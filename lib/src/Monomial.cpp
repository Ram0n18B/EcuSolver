/**
 * @JohanMaldonado
 * @RamonBelandria
 */

#include <Monomial.hpp>

Monomial::Monomial(double c, std::string v, size_t e):coefficient{c}, variable{v},
exponent{e}
{
    //empty
}

std::string Monomial::get_strcoefficient()
{
    return std::to_string(this->coefficient);
}

double Monomial::get_coefficient()
{
    return coefficient;
}

std::string Monomial::get_variable()
{
    return this->variable;
}

std::string Monomial::get_strexponent()
{
    return std::to_string(this->exponent);
}

size_t Monomial::get_exponent()
{
    return exponent;
}

double Monomial::evaluate(double value)
{
    return coefficient * pow(value, exponent);
}

bool operator !=(const Monomial& first, const Monomial& second) noexcept
{
    return first.coefficient != second.coefficient
    || first.variable != second.variable
    || first.exponent != second.exponent;
}

std::ostream& operator << (std::ostream& out, const Monomial& mn) noexcept
{
    out << "(" << mn.coefficient << "; " << mn.variable << "; " << mn.exponent << ")";
    return out;
}