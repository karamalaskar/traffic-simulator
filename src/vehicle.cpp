#include "../include/vehicle.hpp"


// vehicle
void vehicle::set_speed(const int &speed) { this->speed = speed; }
int vehicle::get_speed() const { return speed; }
void vehicle::stop()
{
    moving = false;
    speed = 0;
}
int vehicle::get_position() const { return position; }
void vehicle::set_co2_emission(const int &co2_emission) { this->co2_emission = co2_emission; }
double vehicle::get_co2_emission() const { return co2_emission; }
vehicle_type vehicle::get_type() { return type; }

std::string vehicle::get_license_plate() const {return license_plate;}
std::string vehicle::get_type_name() const
{
    switch (type)
    {
    case car_:
        return "Car";
        break;
    case bus_:
        return "Bus";
        break;
    case truck_:
        return "Truck";
        break;
    case emergency_:
        return "Emergency vehicle";
        break;
    default:
        return "Ferrari";
        break;
    }
}

vehicle::~vehicle() {}

// car
void car::move(const int &time)
{
    moving = true;
    position += speed * time;
}

// bus
void bus::move(const int &time)
{
    moving = true;
    position += speed * 0.6 * time;
}

// truck

int truck::get_cargo_weight() const { return cargo_weight; }
void truck::move(const int &time)
{
    moving = true;
    position += speed * 0.5 * time;
}

// emergency

bool emergency::get_siren() const { return siren; }
void emergency::move(const int &time)
{
    moving = true;
    if (siren)
        position += speed * 1.5 * time;
    else
        position += speed * time;
}

/** Az új formátumú magyar rendszámok 2 random magánhanzó vagy mássalhangzóból, 2 random betűből, és 3 random számból állnak  */
std::string vehicle::generate_license_plate()
{


        std::string license_plate;
        std::string vowels = "AEOUI";
        std::string consonants = "BCDFGHJKLMNPQRSTVWXYZ";

        if (std::rand() % 2 == 0) {
            for (int i = 0; i < 2; i++) {
                license_plate += vowels[std::rand() % vowels.length()];
            }
        } else {
            for (int i = 0; i < 2; i++) {
                license_plate += consonants[std::rand() % consonants.length()];

            }
        }
    license_plate += "-";

        for (int i = 0; i < 2; i++) {
            license_plate += (std::rand() % 26 + 'A');
            
        }
    license_plate += "-";

        for (int i = 0; i < 3; i++) {
            license_plate += std::to_string(std::rand() % 10);
        }
        std::string blue_background = "\033[44m";
        std::string white_background = "\033[107m";
        std::string black_text = "\033[1m\033[30m";
        std::string reset_format = "\033[0m";


    license_plate =  blue_background + " " + white_background + black_text + license_plate + reset_format;
    

    
    return license_plate;
}

bool vehicle::is_moving() const {
    return moving;
}
