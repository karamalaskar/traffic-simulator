#ifndef INTERSECTION_HPP
#define INTERSECTION_HPP

#include <iostream>
#include <vector>
#include "road.hpp"
#include "traffic_light.hpp"
#include "vehicle.hpp"


/** @brief Az utak kereszteződését reprezentáló osztály */
class intersection
{
    /** @brief Észak-Déli út */
    road &north_south;
    /** @brief Dél-Északi út */
    road &south_north;
    /** @brief Az Észak-Déli úton lévő autók */
    std::vector<vehicle *> north_south_vehicles;
    /** @brief Az Északi és Déli utakon lévő autók */
    std::vector<vehicle *> south_north_vehicles;
    /** @brief Észak-Dél lámpa */
    traffic_light &north_south_light;

    /** @brief Kelet-Nyugati út */
    road &east_west;
    /** @brief Nyugat-Keleti út */
    road &west_east;
    /** @brief A Kelet-Nyugati úton lévő autók */
    std::vector<vehicle *> east_west_vehicles;
    /** @brief A Nyugat-Keleti úton lévő autók */
    std::vector<vehicle *> west_east_vehicles;
    /** @brief Kelet-Nyugat lámpa */
    traffic_light &east_west_light;

public:
    /** @brief Kereszteződés konstruktor */
    intersection(road &north_south, road &south_north, traffic_light &north_south_light, road &east_west,
                 road &west_east, traffic_light &east_west_light) : north_south(north_south), south_north(south_north),
                                                                    north_south_light(north_south_light), east_west(east_west), west_east(west_east), east_west_light(east_west_light) {}

    /** @brief Észak-Déli út lekérdezése */
    road &get_north_south() const;
    /** @brief Dél-Északi út lekérdezése */
    road &get_south_north() const;
    /** @brief Kelet-Nyugati út lekérdezése */
    road &get_east_west() const;
    /** @brief Nyugat-Keleti út lekérdezése */
    road &get_west_east() const;

    /** @brief Autó hozzáadása Észak-Déli útra
     *  @param v: Hozzáadandó autó */
    void add_vehicle_north_south(vehicle *const v);
    /** @brief Autó hozzáadása Dél-Északi útra
     *  @param v: Hozzáadandó autó */
    void add_vehicle_south_north(vehicle *const v);
    /** @brief Autó hozzáadása Kelet-Nyugati útra
     *  @param v: Hozzáadandó autó */
    void add_vehicle_east_west(vehicle *const v);
    /** @brief Autó hozzáadása Nyugat-Keleti útra
     *  @param v: Hozzáadandó autó */
    void add_vehicle_west_east(vehicle *const v);

    /** @brief Észak-Déli úton lévő autók lekérdezése */
    const std::vector<vehicle *> &get_vehicles_north_south() const;
    /** @brief Dél-Északi úton lévő autók lekérdezése */
    const std::vector<vehicle *> &get_vehicles_south_north() const;
    /** @brief Kelet-Nyugati úton lévő autók lekérdezése */
    const std::vector<vehicle *> &get_vehicles_east_west() const;
    /** @brief Nyugat-Keleti úton lévő autók lekérdezése */
    const std::vector<vehicle *> &get_vehicles_west_east() const;

    /** @brief Észak-Dél lámpa beállitása */
    void set_light_north_south(const traffic_light &light);
    /** @brief Kelet-Nyugat lámpa beállitása */
    void set_light_east_west(const traffic_light &light);

    /** @brief Észak-Dél lámpa lekérdezése */
    traffic_light &get_light_north_south() const;
    /** @brief Észak-Dél lámpa lekérdezése */
    traffic_light &get_light_east_west() const;

    ~intersection();
};

#endif
