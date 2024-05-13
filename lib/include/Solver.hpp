/**
 * @JohanMaldonado
 * @RamonBelandria
 */

#pragma once

#include <Polynomial.hpp>
#include <cctype>
#include <algorithm>

class Solver
{
private:
    Polynomial in_polynomial;

public:
    Solver(std::string input);

    Solver(Polynomial& pN);
    
    Solver() = delete;
    Solver(const Solver&) = delete;
    Solver(Solver&&) = delete;
    Solver operator = (Solver) = delete;

    //Validates if there isn't any characters other than letters, numbers and operator"
    static bool validate_expression(std::string input) noexcept;

    //Removes all the spaces from the input expression
    static inline void ignore_white_spaces(std::string& expression) noexcept
    {
        expression.erase(std::remove_if(expression.begin(), expression.end(), ::isspace), expression.end());
    }

    //Gets the variable used in the polynomium. There must be only one varibale otherwise retruns an empty string
    static std::string get_variable(std::string& expression) noexcept;

    //Takes a string and builds a "Polynomial" object from it
    static Polynomial build_polynomial(std::string& expression, std::string variable) noexcept;

    //Determinates the grade of the Polynomial based on the biggest exponent in it
    static size_t get_grade(Polynomial& pN) noexcept;

    //Gets the root of a grade 1 polynomial
    static std::vector<double> grade_1_Polynomial(Polynomial& pN) noexcept;

    //Gets the roots of a grade 2 polynomial
    static std::vector<double> grade_2_polynomial(Polynomial& pN, std::vector<double>& solutions) noexcept;

    //Gets the root of a polynomial if its grade is  3 o greater
    static std::vector<double> grade_3_or_greater_polynomial(Polynomial& pN) noexcept;

    //Gets the roots of a polynomial by the Ruffini method
    static std::vector<double> Ruffini(Polynomial& pN) noexcept;

    //Derivates a polynomial
    static Polynomial derivative(Polynomial& pn);

    /*Aproximates the roots of a polynomial by the Newton-Raphson itertion method if it hasn't
    integer roots*/
    static std::vector<double> Newton_Raphson(Polynomial& pN, std::vector<double> solutions) noexcept;

    //Returns the real roots of a polynomial if it has any
    std::vector<double> get_roots() noexcept;
};

size_t superindex(char prefix, size_t& i, std::string& expression);