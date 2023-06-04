#ifndef RANDOM_GENERATOR_HPP
#define RANDOM_GENERATOR_HPP

#include <string>
#include <random>
#include "vehicle.hpp"
#include "intensity.hpp"


/** @brief Random generáló függvényeket tartalmazó osztály*/
class random_generator
{

public:
    /** @brief Random rendszám generáló */
    std::string generate_license_plate();
    /** @brief Random Poisson-eloszlás generáló
     * @param level: a forgalom intenzitása
     * @param simulation_time: a szimuláció ideje
     * @return vektor, ami a másodpercenként generálandó autókat tartalmazza */
    std::vector<int> poisson_distribution(const intensity &level, const int &simulation_time);
    /** @brief Random jármű generáló */
    vehicle *random_vehicle();

};

#endif
