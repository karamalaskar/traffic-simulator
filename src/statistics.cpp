#include "../include/statistics.hpp"




void statistics::add_vehicle(const vehicle &v)
{   
    if (dynamic_cast<const car *>(&v))
        num_cars++;
    else if (dynamic_cast<const bus *>(&v))
        num_buses++;
    else if (dynamic_cast<const truck *>(&v))
        num_trucks++;
    else if (dynamic_cast<const emergency *>(&v))
        num_emergencies++;
    num_vehicles++;
}

void statistics::add_lamp_cycle()
{
    lamp_cycles++;
}

void statistics::add_average_speed(const int &speed)
{
    average_speed += speed;
    speeds++;
}


void statistics::add_co2_emissions(const int &emissions)
{
    total_co2_emissions += emissions;
}

void statistics::add_cargo_weight(const int& weight) {
    total_cargo_weight += weight;
}

void statistics::add_sirens() {
    num_sirens++;
};


void statistics::print_statistics()
{
    std::cout<< std::endl;
    std::cout << "Statistics: " << std::endl;
    std::cout << "Number of vehicles: " << num_vehicles << std::endl;
    std::cout << "Number of cars " << num_cars << std::endl;
    std::cout << "Number of busses: " << num_buses << std::endl;
    std::cout << "Number of trucks: " << num_trucks << std::endl;
    std::cout << "Number of emergency vehicles: " << num_emergencies << std::endl;
    std::cout << "Number of emergencies (sirens on): " << num_sirens << std::endl;
    std::cout << "Number of lamp cycles: " << lamp_cycles << std::endl;
    std::cout << "Average speed: " << average_speed/speeds << std::endl;
    std::cout << "Average CO2 emissions g/km: " << total_co2_emissions/num_vehicles << std::endl;
    std::cout << "Total cargo weight passed: " << total_cargo_weight << std::endl;
    std::cout<< std::endl;
}

