/**
 * @JohanMaldonado
 * @RamonBelandria
 */

#pragma once

#include <string>
#include <cmath>
#include <memory>
#include <iostream>

class Monomial
{
private:
    double coefficient;
    std::string variable;
    size_t exponent;
public:

    Monomial(double c, std::string v, size_t e = 1);

    std::string get_strcoefficient();

    double get_coefficient();

    std::string get_variable();

    std::string get_strexponent();
    
    size_t get_exponent();

    double evaluate(double value);

    friend bool operator !=(const Monomial& first, const Monomial& second) noexcept;

    friend std::ostream& operator << (std::ostream& out, const Monomial& mn) noexcept;
};

using MonomialPtr = std::shared_ptr<Monomial>;
