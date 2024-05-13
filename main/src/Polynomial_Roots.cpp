/**
 * @JohanMaldonado
 * @RamonBelandria
 */

#include <TestUtilities.hpp>

int main()
{
    std::cout << "Ingrese un polinomio de la forma \"k_nx^n + ... + k_1x + k_0\" " << std::endl;
    std::cout << "Si introduce exponentes mayores a 9, deje un espacio entre \"^\" y" << std::endl;
    std::cout << "el número" << std::endl;
    std::cout << std::endl;

    std::cout << "Polinomio: ";
    std::string expression;
    std::getline(std::cin, expression);

    Solver solver(expression);
    std::vector<double> solutions = solver.get_roots();
    if(solutions.empty())
    {
        std::cout << "El polinomio no tiene raíces reales" << std::endl;
        return 0;
    }

    if(solutions.size() == 1)
    {
        std::cout << "Solución: ";
        std::cout << solutions[0] << std::endl;
        return 0;
    }

    std::cout << "Soluciones: ";
    std::cout << solutions << std::endl;
    return 0;
}