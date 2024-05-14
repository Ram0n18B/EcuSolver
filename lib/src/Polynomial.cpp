/**
 * @JohanMaldonado
 * @RamonBelandria
 */

#include <Polynomial.hpp>

bool ExponentComparer::operator () (MonomialPtr first, MonomialPtr second) noexcept
{
    return first->get_exponent() < second->get_exponent();
}

double Polynomial::evaluate(double value) noexcept
{
    double total = 0;
    for(size_t i = 0; i < this->size(); ++i)
    {
        total += this->get_container()[i]->evaluate(value);
    }
    return total;
}

void Polynomial::fill_null_terms() noexcept
{
    if(this->empty())
    {
        return;
    }
    Polynomial newPolynomial;
    newPolynomial.emplace(this->top());
    this->pop();
    for(int i = newPolynomial.top()->get_exponent() - 1; i > -1; --i)
    {
        if(!(this->empty() || this->top()->get_exponent() != i))
        {
            newPolynomial.emplace(this->top());
            this->pop();
            continue;
        }
        newPolynomial.emplace(new Monomial(0, newPolynomial.top()->get_variable(), i));
    }
    *this = newPolynomial;
}

MonomialPtr Polynomial::operator [] (size_t i) noexcept
{
    return this->get_container()[i];
}

const Polynomial::container_type& Polynomial::get_container() const noexcept
{
    return Polynomial::Base::c;
}

double Polynomial::independant_term() noexcept
{
    for(size_t i = 0; i < this->size(); ++i)
    {
        if(this->get_container()[i]->get_exponent() == 0)
        {
            return this->get_container()[i]->get_coefficient();
        }
    }
    return 0;
}

bool operator !=(const Polynomial& first, const Polynomial& second) noexcept
{
    if(first.size() != second.size())
    {
        return true;
    }
    for(size_t i = 0; i < first.size(); ++i)
    {
        if(*(first.get_container()[i]) != *(second.get_container()[i]))
        {
            return true;
        }
    }
    return false;
}