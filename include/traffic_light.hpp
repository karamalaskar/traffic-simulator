#ifndef TRAFFIC_LIGHT_HPP
#define TRAFFIC_LIGHT_HPP



/** @brief Lámpa osztály */
class traffic_light
{
protected:
    /** @brief Lámpa állapota */
    bool is_green;
    /** @brief Lámpa ciklus ideje */
    int cycle_time;

public:
    /** @brief Konstruktor */
    traffic_light() : is_green(false), cycle_time(10){};
    /** @brief Lámpa állapotának beállítása
     * @param state: a lámpa állapota */
    void set_green(const bool &state);
    /** @brief Lámpa állapotának lekérdezése */
    bool get_green() const;
    /** @brief Lámpa váltakozása*/
    void cycle();

};


#endif
