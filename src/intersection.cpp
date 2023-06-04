#include "../include/intersection.hpp"


road &intersection::get_north_south() const { return north_south; }
road &intersection::get_south_north() const { return south_north; }
road &intersection::get_east_west() const { return east_west; }
road &intersection::get_west_east() const { return west_east; }

void intersection::add_vehicle_north_south(vehicle *const v)
{
    if (v == nullptr)
        throw std::runtime_error("Cannot add nullptr to NS vehicles");
    north_south_vehicles.push_back(v);
}
void intersection::add_vehicle_south_north(vehicle *const v)
{
    if (v == nullptr)
        throw std::runtime_error("Cannot add nullptr to SN vehicles");
    south_north_vehicles.push_back(v);
}
void intersection::add_vehicle_east_west(vehicle *const v)
{
    if (v == nullptr)
        throw std::runtime_error("Cannot add nullptr to EW vehicles");
    east_west_vehicles.push_back(v);
}
void intersection::add_vehicle_west_east(vehicle *const v)
{
    if (v == nullptr)
        throw std::runtime_error("Cannot add nullptr to WE vehicles");
    west_east_vehicles.push_back(v);
}

const std::vector<vehicle *> &intersection::get_vehicles_north_south() const { return north_south_vehicles; }
const std::vector<vehicle *> &intersection::get_vehicles_south_north() const { return south_north_vehicles; }
const std::vector<vehicle *> &intersection::get_vehicles_east_west() const { return east_west_vehicles; }
const std::vector<vehicle *> &intersection::get_vehicles_west_east() const { return west_east_vehicles; }

void intersection::set_light_north_south(const traffic_light &light) { north_south_light = light; }
void intersection::set_light_east_west(const traffic_light &light) { east_west_light = light; }

traffic_light &intersection::get_light_north_south() const { return north_south_light; }
traffic_light &intersection::get_light_east_west() const { return east_west_light; }

intersection::~intersection()
{
    for (size_t i = 0; i < north_south_vehicles.size(); i++)
        delete north_south_vehicles[i];
    for (size_t i = 0; i < south_north_vehicles.size(); i++)
        delete south_north_vehicles[i];
    for (size_t i = 0; i < east_west_vehicles.size(); i++)
        delete east_west_vehicles[i];
    for (size_t i = 0; i < west_east_vehicles.size(); i++)
        delete west_east_vehicles[i];
}
