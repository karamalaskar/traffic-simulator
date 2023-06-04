#ifndef SIMULATION_HPP
#define SIMULATION_HPP

#include <iostream>
#include <iomanip>
#include <chrono>
#include <thread>
#include "road.hpp"
#include "traffic_light.hpp"
#include "vehicle.hpp"
#include "intersection.hpp"
#include "random_generator.hpp"
#include "statistics.hpp"


/** @brief Szimuláció osztály*/
class simulation
{
    /** @brief Szimuláció ideje*/
    int simulation_time;
    /** @brief Kereszteződés*/
    intersection the_intersection;
    /** @brief Forgalom intenzitása*/
    intensity traffic;
    /** @brief Random generátor*/
    random_generator rand_gen;
    /** @brief Statisztika*/
    statistics stats;

public:
    /** @brief Szimuláció konstruktor*/
    simulation(const int &time, intersection &the_intersection, const intensity &level) : simulation_time(time), the_intersection(the_intersection), traffic(level) {}
    /** @brief Statisztika lekérdezés*/
    statistics get_stats();
    /** @brief szimuláció futtatása
     * @param readable: ha igaz, akkor a szimulációt lassan írja ki a kimenetre*/
    void run(bool readable);
    /** @brief autók megállítása
     * @param vehicles: az autók
     * @param current_road: az út, amin az autók vannak
     * @param road_name: az út neve*/
    void stop_vehicles(const std::vector<vehicle *> &vehicles, road &current_road, const std::string &road_name);
    /** @brief autók mozgatása
     * @param vehicles: az autók
     * @param current_road: az út, amin az autók vannak
     * @param road_name: az út neve*/
    void move_vehicles(const std::vector<vehicle *> &vehicles, road &current_road, const std::string &road_name);
    /** @brief autók eltávolítása
     * @param current_road: az út, amin az autók vannak
     * @param road_name: az út neve*/
    void remove_vehicle(vehicle *current_vehicle, road &current_road);
    /** @brief lámpa állapotának lekérdezése
     * @param current_road: az út, amin a lámpa van*/
    bool get_light(road &current_road);
};

#endif
