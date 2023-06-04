#ifndef ROAD_HPP
#define ROAD_HPP

#include "traffic_light.hpp"


/** @brief Út osztály*/
class road
{
    /** @brief út hossza*/
    int length;
    /** @brief lámpa pozíciója*/
    int light_position;
    /** @brief sebesség limit*/
    int speed_limit;

public:
    /** @brief Út konstruktor*/
    road();
    /** @brief Út inicializáló konstruktor */
    road(const int &length, const int &speed_limit, const int &light_position) : length(length), light_position(light_position), speed_limit(speed_limit) {}
    /** @brief Út hossz lekerdezese */
    int get_length() const;
    /** @brief lámpa pozíció lekerdezese */
    int get_light_position();
    /** @brief sebesség limit lekerdezese */
    int get_speed_limit() const;
};

#endif