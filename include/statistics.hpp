#ifndef STATISTICS_HPP
#define STATISTICS_HPP

#include "vehicle.hpp"


/** @brief Statisztika osztály */
class statistics
{
    /** @brief Járművek száma */
    int num_vehicles;
    /** @brief Autók száma */
    int num_cars;
    /** @brief Buszok száma */
    int num_buses;
    /** @brief Teherautók száma */
    int num_trucks;
    /** @brief Mentők száma */
    int num_emergencies;
    /** @brief Lámpa ciklusok száma */
    int lamp_cycles;
    /** @brief Átlagos várakozási idő */
    int average_wait_time;
    /** @brief Átlagos sebesség */
    double average_speed;
    /** @brief Sebességek száma*/
    double speeds;
    /** @brief co2 emisszio */
    int total_co2_emissions;
    /** @brief Teher összege*/
    int total_cargo_weight;
    /** @brief Hányszor volt bekapcsolva a sziréna*/
    int num_sirens;

public:
    /** @brief statisztika konstruktor, beállít mindent 0-ra*/
    statistics()
    {
        num_vehicles = 0;
        num_cars = 0;
        num_buses = 0;
        num_trucks = 0;
        num_emergencies = 0;
        lamp_cycles = 0;
        average_wait_time = 0;
        average_speed = 0;
        speeds = 0;
        total_co2_emissions = 0;
        total_cargo_weight = 0;
        num_sirens = 0;
    }
    /** @brief jármű hozzáadása
     * @param v: jármű */
    void add_vehicle(const vehicle &v);
    /** @brief lámpa ciklus számláló */
    void add_lamp_cycle();
    /** @brief teher számoló
     * @param weight: teher súlya */
    void add_cargo_weight(const int &weight);
    /** @brief co2 számoló
     * @param emissions: co2 emisszió */
    void add_co2_emissions(const int &emissions);
    /** @brief átlagos sebesség számoló
     * @param speed: sebesség */
    void add_average_speed(const int &speed);
    /** @brief átlagos sebesség lekérdezése */
    int get_average_speed();
    /** @brief Statisztika kiírása */
    void print_statistics();
    /** @brief sziréna számláló*/
    void add_sirens();
};

#endif
