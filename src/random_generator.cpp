#include "../include/random_generator.hpp"
#include "../include/vehicle.hpp"


std::vector<int> random_generator::poisson_distribution(const intensity &level, const int &simulation_time)
{

    std::vector<int> poisson;
    double poisson_lambda;

    // a lambda értéke a forgalom intenzitásától függ
    switch (level)
    {
    case light:
        poisson_lambda = 0.5;
        break;
    case medium:
        poisson_lambda = 1.5;
        break;
    case heavy:
        poisson_lambda = 4.5;
        break;
    default:
        poisson_lambda = 1.5;
        break;
    }
    // ha szimulacio ido kisebb vagy egyenlo 0, kivetelt dob
    if (simulation_time <= 0)
        throw std::runtime_error("Error in poisson distribution, simulation time must be positive");
    if (poisson_lambda < 0)
        throw "Error in poisson distribution, lambda must be positive";

    // a poisson eloszlás generálása
    for (int i = 0; i < simulation_time; i++)
    {
        double e = exp(-poisson_lambda);
        double p = 1.0;
        int k = 0;

        while (p > e)
        {
            k++;
            double u = static_cast<double>(rand()) / RAND_MAX;
            p *= u;
        }
        // ha az ertek negativ, kivetelt dob
        if ((k - 1) < 0)
            throw std::runtime_error("Error in poisson distribution, poisson value must be positive");
        poisson.push_back(k - 1);
    }
    return poisson;
}

vehicle *random_generator::random_vehicle()
{
    // sulyozott random jarmu generátor
    int random = rand() % 100;
    if (random <= 70)
        return new car();
    if (random <= 85)
        return new bus();
    if (random <= 90)
        return new truck();
    if (random <= 95)
        return new emergency();
    return new car();
}