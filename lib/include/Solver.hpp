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

    static bool validate_expression(std::string input) noexcept;

    static inline void ignore_white_spaces(std::string& expression) noexcept
    {
        expression.erase(std::remove_if(expression.begin(), expression.end(), ::isspace), expression.end());
    }

    static std::string get_variable(std::string& expression) noexcept;

    static Polynomial build_polynomial(std::string& expression, std::string variable) noexcept;

    static size_t get_grade(Polynomial& pN) noexcept;

    static std::vector<double> grade_1_Polynomial(Polynomial& pN) noexcept;

    static std::vector<double> grade_2_polynomial(Polynomial& pN, std::vector<double>& solutions) noexcept;

    static std::vector<double> grade_3_or_greater_polynomial(Polynomial& pN, size_t& grade) noexcept;

    static std::vector<double> Ruffini(Polynomial& pN) noexcept;

    static Polynomial derivative(Polynomial& pn);

    static std::vector<double> Newton_Raphson_loop(Polynomial& pN, std::vector<double>& solutions, size_t& grade) noexcept;

    static std::pair<double, double> Newton_Raphson(Polynomial& pN, Polynomial& derivative, double& aproximation, size_t& grade) noexcept;

    std::vector<double> get_roots() noexcept;
};

size_t superindex(char prefix, size_t& i, std::string& expression);

std::pair<Polynomial, double> synthetic_division(Polynomial& pN, double divisor) noexcept;

double absolute_value(double value);

bool repeated(double num, std::vector<double>& solutions);