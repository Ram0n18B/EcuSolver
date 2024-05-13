/**
 * @JohanMaldonado
 * @RamonBelandria
 */

#pragma once

#include <queue>
#include <Monomial.hpp>
#include <vector>

class ExponentComparer
{
public:

    bool operator () (MonomialPtr first, MonomialPtr second) noexcept;
};

class Polynomial: public std::priority_queue<MonomialPtr, std::vector<MonomialPtr>, ExponentComparer>
{
    using Base = std::priority_queue<MonomialPtr, std::vector<MonomialPtr>, ExponentComparer>;
    using Base::Base;

public:

    double evaluate(double value) noexcept;

    //Fill the polynomial with null terms in order to keep the esponent decreasing sequence
    void fill_null_terms() noexcept;

    MonomialPtr operator [] (size_t i) noexcept;

    const Polynomial::container_type& get_container() const noexcept;
};

bool operator !=(const Polynomial& first, const Polynomial& second) noexcept;