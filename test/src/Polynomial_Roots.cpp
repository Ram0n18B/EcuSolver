/**
 * @JohanMaldonado
 * @RamonBelandria
 */

#include <TestUtilities.hpp>

int main()
{
    std::cout<< "Solver tests:" << std::endl;
    std::string grade1 = "3x-15";
    std::string real_roots = "y²-1";
    std::string grade2 = "7y²+3y+5";
    std::string int_roots = "z³+6z²+11z+6";
    std::string grade4 = "17w⁴+24w³+35w²+27w+5";
    
    {
        std::cout<< "Testing validate_expression:" << std::endl;
        std::string input = "3x - 15";
        assert_equal(Solver::validate_expression(input), true);
    }
    {
        std::string input = "y² - 1";
        assert_equal(Solver::validate_expression(input), true);
    }
    {
        std::string input = "7y² + 3y + 5";
        assert_equal(Solver::validate_expression(input), true);
    }
    {
        std::string input = "z³ + 6z² + 11z + 6";
        assert_equal(Solver::validate_expression(input), true);
    }
    {
        std::string input = "17w⁴ + 24w³ + 35w² + 27w + 5";
        assert_equal(Solver::validate_expression(input), true);
    }
    {
        assert_equal(Solver::validate_expression("`_.!"), false);
    }

    
    std::cout << "Testing ignore_white_spaces:" << std::endl;
    {
        std::string spaced = "3x - 15";
        Solver::ignore_white_spaces(spaced);
        assert_equal(spaced, grade1);
    }
    {
        std::string spaced = "y² - 1";
        Solver::ignore_white_spaces(spaced);
        assert_equal(spaced, real_roots);
    }
    {
        std::string spaced = "7y² + 3y + 5";
        Solver::ignore_white_spaces(spaced);
        assert_equal(spaced, grade2);
    }
    {
        std::string spaced = "z³ + 6z² + 11z + 6";
        Solver::ignore_white_spaces(spaced);
        assert_equal(spaced, int_roots);
    }
    {
        std::string spaced = "17w⁴ + 24w³ + 35w² + 27w + 5";
        Solver::ignore_white_spaces(spaced);
        assert_equal(spaced, grade4);
    }

    std::cout << "Testing get_variable:" << std::endl;
    {
        std::string variable = "x";
        assert_equal(Solver::get_variable(grade1), variable);
    }
    {
        std::string variable = "y";
        assert_equal(Solver::get_variable(real_roots), variable);
        assert_equal(Solver::get_variable(grade2), variable);
    }
    {
        std::string variable = "z";
        assert_equal(Solver::get_variable(int_roots), variable);
    }
    {
        std::string variable = "w";
        assert_equal(Solver::get_variable(grade4), variable);
    }
    {
        std::string variable = "xyzw";
        assert_equal(Solver::get_variable(variable), variable);
    }

    std::cout<< "Testing get_grade:"<< std::endl;
    {
        Polynomial pN;
        pN.emplace(new Monomial(3, "x"));
        pN.emplace(new Monomial(-15, "x", 0));
        size_t grade = 1;
        assert_equal(Solver::get_grade(pN), grade);
    }
    {
        Polynomial pN;
        pN.emplace(new Monomial(1, "y", 2));
        pN.emplace(new Monomial(-1, "y", 0));
        size_t grade = 2;
        assert_equal(Solver::get_grade(pN), grade);
    }
    {
        Polynomial pN;
        pN.emplace(new Monomial(1, "z", 3));
        pN.emplace(new Monomial(6, "z", 2));
        pN.emplace(new Monomial(11, "z"));
        pN.emplace(new Monomial(6, "z", 0));
        size_t grade = 3;
        assert_equal(Solver::get_grade(pN), grade);
    }
    {
        Polynomial pN;
        pN.emplace(new Monomial(17, "w", 4));
        pN.emplace(new Monomial(24,"w", 3));
        pN.emplace(new Monomial(35, "w", 2));
        pN.emplace(new Monomial(27, "w"));
        pN.emplace(new Monomial(5, "w", 0));
        size_t grade = 4;
        assert_equal(Solver::get_grade(pN), grade);
    }

    std::cout<< "Testing grade_1_polynomial"<< std::endl;
    {
        Polynomial pN;
        pN.emplace(new Monomial(3, "x"));
        pN.emplace(new Monomial(-15, "x", 0));
        std::vector<double> expected = {(double)5};
        assert_equal(Solver::grade_1_Polynomial(pN), expected);
    }

    std::cout<< "Testing grade_2_polynomial"<< std::endl;
    {
        Polynomial pN;
        pN.emplace(new Monomial(1, "y", 2));
        pN.emplace(new Monomial(-1, "y", 0));
        std::vector<double> expected = {(double)-1, (double)1};
        std::vector<double> empty;
        assert_equal(Solver::grade_2_polynomial(pN, empty), expected);
    }
    {
        Polynomial pN;
        pN.emplace(new Monomial(7, "y", 2));
        pN.emplace(new Monomial(3, "y"));
        pN.emplace(new Monomial(5, "y", 0));
        std::vector<double> expected = {};
        std::vector<double> empty;
        assert_equal(Solver::grade_2_polynomial(pN, empty), expected);
    }

    std::cout<< "Testing derivative: "<< std::endl;
    {
        Polynomial pN;
        pN.emplace(new Monomial(17, "w", 4));
        pN.emplace(new Monomial(24,"w", 3));
        pN.emplace(new Monomial(35, "w", 2));
        pN.emplace(new Monomial(27, "w"));
        pN.emplace(new Monomial(5, "w", 0));
        Polynomial expected;
        expected.emplace(new Monomial(68, "w", 3));
        expected.emplace(new Monomial(72, "w", 2));
        expected.emplace(new Monomial(70, "w"));
        expected.emplace(new Monomial(27, "w", 0));
        assert_equal(Solver::derivative(pN), expected);
    }

    std::cout<< "Testing build_polynomial:" << std::endl;
    {
        Polynomial expected;
        expected.emplace(new Monomial(3, "x"));
        expected.emplace(new Monomial(-15, "x", 0));
        assert_equal(Solver::build_polynomial(grade1, "x"), expected);
    }
    {
        Polynomial expected;
        expected.emplace(new Monomial(1, "y", 2));
        expected.emplace(new Monomial(-1, "y", 0));
        assert_equal(Solver::build_polynomial(real_roots, "y"), expected);
    }
    {
        Polynomial expected;
        expected.emplace(new Monomial(7, "y", 2));
        expected.emplace(new Monomial(3, "y"));
        expected.emplace(new Monomial(5, "y", 0));
        assert_equal(Solver::build_polynomial(grade2, "y"), expected);
    }
    {
        Polynomial expected;
        expected.emplace(new Monomial(1, "z", 3));
        expected.emplace(new Monomial(6, "z", 2));
        expected.emplace(new Monomial(11, "z"));
        expected.emplace(new Monomial(6, "z", 0));
        assert_equal(Solver::build_polynomial(int_roots, "z"), expected);
    }
    {
        Polynomial expected;
        expected.emplace(new Monomial(17, "w", 4));
        expected.emplace(new Monomial(24,"w", 3));
        expected.emplace(new Monomial(35, "w", 2));
        expected.emplace(new Monomial(27, "w"));
        expected.emplace(new Monomial(5, "w", 0));
        assert_equal(Solver::build_polynomial(grade4, "w"), expected);
    }

    std::cout << "Testing Ruffini: " << std::endl;
    {
        Polynomial pN;
        pN.emplace(new Monomial(1, "z", 3));
        pN.emplace(new Monomial(6, "z", 2));
        pN.emplace(new Monomial(11, "z"));
        pN.emplace(new Monomial(6, "z", 0));
        std::vector<double> expected = {(double)-1, (double)-2, (double)-3};
        assert_equal(Solver::Ruffini(pN), expected);
    }
    {
        Polynomial pN;
        pN.emplace(new Monomial(17, "w", 4));
        pN.emplace(new Monomial(24,"w", 3));
        pN.emplace(new Monomial(35, "w", 2));
        pN.emplace(new Monomial(27, "w"));
        pN.emplace(new Monomial(5, "w", 0));
        assert_equal(Solver::Ruffini(pN), {});
    }

    std::cout<< "Testing Newton_Raphson"<< std::endl;
    {
        std::cout<< "WARNING: Newton_Raphson hasn't been tested yet"<< std::endl;
    }

    std::cout<< "Testing grade_3_or_greater_polynomial"<< std::endl;
    {
        Polynomial pN;
        pN.emplace(new Monomial(1, "z", 3));
        pN.emplace(new Monomial(6, "z", 2));
        pN.emplace(new Monomial(11, "z"));
        pN.emplace(new Monomial(6, "z", 0));
        std::vector<double> expected = {(double)-1, (double)-2, (double)-3};
        assert_equal(Solver::grade_3_or_greater_polynomial(pN), expected);
    }
    {
        //Second test missing;
    }

    std::cout<< "Testing get_roots"<< std::endl;
    {
        Solver pNsolver(grade1);
        std::vector<double> expected = {(double)5};
        assert_equal(pNsolver.get_roots(), expected);
    }
    {
        Solver pNsolver(real_roots);
        std::vector<double> expected = {(double)-1, (double)1};
        assert_equal(pNsolver.get_roots(), expected);
    }
    {
        Solver pNsolver(grade2);
        assert_equal(pNsolver.get_roots(), {});
    }
    {
        Solver pNsolver(int_roots);
        std::vector<double> expected = {(double)-1, (double)-2, (double)-3};
        assert_equal(pNsolver.get_roots(), expected);
    }
    return EXIT_SUCCESS;
}