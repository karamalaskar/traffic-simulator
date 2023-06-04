#ifndef VEHICLE_HPP
#define VEHICLE_HPP

#include <iostream>



/** @brief jarmu tipusa */
enum vehicle_type
{
    car_,
    bus_,
    truck_,
    emergency_
};

/** @brief Jármű osztály */
class vehicle
{
protected:
    /** @brief Jármű típusa */
    vehicle_type type;
    /** @brief Jármű sebessége */
    int speed;
    /** @brief Jármű sebessége */
    double position;
    /** @brief Jármű sebessége */
    bool moving;
    /** @brief Jármű rendszáma */
    std::string license_plate;
    /** @brief Jármű CO2 kibocsátása */
    double co2_emission;

public:
    /** @brief Jármű konstruktor */
    vehicle(const vehicle_type &type) : type(type), speed(0), position(0), moving(false), license_plate(generate_license_plate()){} //) 
    /** @brief Sebesseg beállítása */
    void set_speed(const int &speed);
    /** @brief Sebesség beállítása */
    int get_speed() const;
    /** @brief Pozíció beállítása/mozgás */
    virtual void move(const int &time) = 0;
    /** @brief Megállítás */
    void stop();
    /** @brief Mozság állapota */
    bool is_moving() const;
    /** @brief Pozíció lekérdezése */
    int get_position() const;
    /** @brief CO2 kibocsátás beállítása
     * @param co2_emission: a CO2 érték */
    void set_co2_emission(const int &co2_emission);
    /** @brief CO2 kibocsátás lekérdezése */
    double get_co2_emission() const;
    /** @brief Jármű típusának lekérdezése */
    vehicle_type get_type();
    /** @brief Jármű típus nevének lekérdezése */
    std::string get_type_name() const;
    /** @brief Rendszám generálása */
    std::string generate_license_plate();
    /** @brief Renszám lekérdezése */
    std::string get_license_plate() const;
    /** @brief Jármű destruktor */
    virtual ~vehicle();
};

/** @brief Autó típus */
class car : public vehicle
{
public:
    /** @brief Autó konstruktor */
    car() : vehicle(car_) {co2_emission = (rand() % 2 == 0) ? 120 : 0;} //lehet zero emission, elektromos
    virtual void move(const int &time);
};

/** @brief Busz típus */
class bus : public vehicle
{
public:
    /** @brief konstruktor */
    bus() : vehicle(bus_) {co2_emission = 250;}
    virtual void move(const int &time);
};

/** @brief Teherautó típus */
class truck : public vehicle
{
    /** @brief Teher súlya */
    int cargo_weight;

public:
    /** @brief Teherautó konstruktor */
    truck() : vehicle(truck_) {co2_emission = 300; cargo_weight = rand() % 3000;} // teher 0 es 3000 kozott barmi lehet
    /** @brief Teher súly beallitasa
     * @param cargo_weight: a teher sulya */
    /** @brief Teher súly lekérdezése */
    int get_cargo_weight() const;
    virtual void move(const int &time);
};

/** @brief Mentő típus */
class emergency : public vehicle
{
    /** @brief sziréna állapota 0/1 */
    int siren;

public:
    /** @brief konstruktor */
    emergency() : vehicle(emergency_) {co2_emission = 180; siren = rand() % 2 == 0;} // szirena random be/ki kapcsolva
    /** @brief szirena allapotanak beallitasa
     * @param state: a szirena allapota */
    bool get_siren() const;
    void move(const int &time);
    

};

#endif
