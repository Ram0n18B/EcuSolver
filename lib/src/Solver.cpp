/**
 * @JohanMaldonado
 * @RamonBelandria
 */

#include <Solver.hpp>

Solver::Solver(std::string expression)
{
    if(!validate_expression(expression))
    {
        std::cerr<< "Elemento inesperado en la expresión: "<< (char)34 << expression<< (char)34;
        abort();
    }
    ignore_white_spaces(expression);
    std::string variable = get_variable(expression);
    if(variable == "")
    {
        std::cerr<< "La expresión tiene más de una variable o no tiene ninguna"<< std::endl;
        abort();
    }
    this->in_polynomial = build_polynomial(expression, variable);
}

Solver::Solver(Polynomial& pn): in_polynomial{pn}
{
    //empty
}

bool Solver::validate_expression(std::string input) noexcept
{
    for(size_t i = 0; i < input.size(); ++i)
    {
        int current = int(input[i]);
        if(!(isdigit(input[i]))
            && !(current > 64 && current < 91)
            && !(current > 96 && current < 123)
            && input[i] != '+'
            && input[i] != '-'
            && input[i] != '.'
            && input[i] != '^'
            && !(std::isspace(input[i]))
            && input[i] != '\342'
            && input[i] != '\201'
            && input[i] != '\260'
            && input[i] != '\302'
            && input[i] != '\271'
            && input[i] != '\262'
            && input[i] != '\263'
            && input[i] != '\264'
            && input[i] != '\265'
            && input[i] != '\266'
            && input[i] != '\267'
            && input[i] != '\270')
        {
            return false;
        }
    }
    return true;
}

std::string Solver::get_variable(std::string& expression) noexcept
{
    size_t i = 0;
    std::string variable = "";
    for(; (expression[i] != '+' && expression[i] != '-') && i != expression.size(); ++i)
    {
        if((int(expression[i]) > 64 && int(expression[i]) < 91)
        || (int(expression[i]) > 96 && int(expression[i]) < 123))
        {
            variable += expression[i];
        }
    }
    for(; i < expression.size(); ++i)
    {
        std::string mnvar = "";
        for(size_t j = i; (int(expression[j]) > 64 && int(expression[j]) < 91)
        || (int(expression[j]) > 96 && int(expression[j]) < 123); ++j)
        {
            mnvar += expression[j];
        }
        if(mnvar != "" && variable != mnvar)
        {
            return "";
        }
    }
    return variable;
}

size_t Solver::get_grade(Polynomial& pN) noexcept
{
    return pN.top()->get_exponent();
}

std::vector<double> Solver::grade_1_Polynomial(Polynomial& pN) noexcept
{
    double a = pN.top()->get_coefficient();
    double b = 0;
    pN.pop();
    if(!(pN.empty()))
    {
        b = pN.top()->get_coefficient();
    }
    return {-b/a};
}

std::vector<double> Solver::grade_2_polynomial(Polynomial& pN, std::vector<double>& solutions) noexcept
{
    double a = pN.top()->get_coefficient();
    pN.pop();
    double b = 0;
    double c = 0;
    if(!(pN.empty()) && pN.top()->get_exponent() == 1)
    {
        b = pN.top()->get_coefficient();
        pN.pop();
    }
    if(!(pN.empty()))
    {
        c = pN.top()->get_coefficient();
        pN.pop();
    }
    double discriminator = pow(b, 2) - 4*a*c;
    if(discriminator < 0)
    {
        return solutions;
    }
    solutions.emplace_back((-b - sqrt(discriminator))/(2*a));
    if(discriminator == 0)
    {
        return solutions;
    }
    solutions.emplace_back((-b + sqrt(discriminator))/(2*a));
    return solutions;
}

std::vector<double> Solver::grade_3_or_greater_polynomial(Polynomial& pN) noexcept
{
    size_t initial_grade = get_grade(pN);
    std::vector<double> solutions = Solver::Ruffini(pN);
    if(solutions.size() < initial_grade && get_grade(pN))
    {
        return Newton_Raphson(pN, solutions);
    }
    if(get_grade(pN) == 2)
    {
        return grade_2_polynomial(pN, solutions);
    }
    return {};
}

Polynomial Solver::derivative(Polynomial& pn)
{
    Polynomial derivative;
    for(size_t i = 0; i < pn.size() - 1; ++i)
    {
        derivative.emplace(new Monomial(pn.get_container()[i]->get_exponent() * pn.get_container()[i]->get_coefficient(),
            pn.top()->get_variable(),
            pn.get_container()[i]->get_exponent() - 1));
    }
    return derivative;
}

Polynomial Solver::build_polynomial(std::string& expression, std::string variable) noexcept
{
    Polynomial pN;
    size_t i = 0;
    while(i < expression.size())
    {
        std::string coefficient = "";
        while(isdigit(expression[i])
            || expression[i] == '.' || expression[i] == '-' || expression[i] == '+')
        {
            coefficient += expression[i];
            ++i;
            if(i == expression.size())
            {break;}
        }
        if(coefficient == "")
        {coefficient = "1";}
        if(i == expression.size())
        {
            pN.emplace(new Monomial(std::stod(coefficient), variable, 0));
            break;
        }
        if(expression[i] == variable[0])
        {
            i += variable.size();
        }
        if(expression[i] == '\302')
        {
            pN.emplace(new Monomial(std::stod(coefficient), variable, superindex('\302', i, expression)));
            ++i;
            continue;
        }
        if(expression[i] == '\342')
        {
            pN.emplace(new Monomial(std::stod(coefficient), variable, superindex('\342', i, expression)));
            ++i;
            continue;
        }
        std::string exponent = "";
        if(expression[i] == '^')
        {++i;}
        while(isdigit(expression[i]))
        {
            exponent += expression[i];
            ++i;
            if(i == expression.size())
            {break;}
        }
        if(exponent == "")
        {pN.emplace(new Monomial(std::stod(coefficient), variable));}
        else
        {pN.emplace(new Monomial(std::stod(coefficient), variable, std::stoi(exponent)));}
    }
    return pN;
}

size_t superindex(char prefix, size_t& i, std::string& expression)
{
    if(prefix == '\302')
    {
        ++i;
        if(expression[i] == '\271')
        return 1;

        if(expression[i] == '\262')
        return 2;

        if(expression[i] == '\263')
        return 3;
    }

    i += 2;
    if(expression[i] == '\264')
    return 4;

    if(expression[i] == '\265')
    return 5;

    if(expression[i] == '\266')
    return 6;

    if(expression[i] == '\267')
    return 7;

    if(expression[i] == '\270')
    return 8;

    if(expression[i] == '\271')
    return 9;

    return 0;
}

std::vector<double> Solver::Ruffini(Polynomial& pN) noexcept
{
    return {};
}

std::vector<double> Solver::Newton_Raphson(Polynomial& pN, std::vector<double> solutions) noexcept
{
    return {};
}

std::vector<double> Solver::get_roots() noexcept
{
    std::vector<double> solutions = {};
    size_t grade = get_grade(in_polynomial);
    switch (grade)
    {
    case 1:
        return grade_1_Polynomial(in_polynomial);
    case 2:
        grade_2_polynomial(in_polynomial, solutions);
        return solutions;
    default:
        return grade_3_or_greater_polynomial(in_polynomial);
    }
    return {};
}