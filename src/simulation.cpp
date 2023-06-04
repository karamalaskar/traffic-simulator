#include "../include/simulation.hpp"


statistics simulation::get_stats()
{
    return stats;
}

void simulation::run(bool readable = true)
{
    // poisson eloszlas generalas minden utra
    std::vector<int> pod_ns = rand_gen.poisson_distribution(traffic, simulation_time);
    if (pod_ns.empty())
        throw std::runtime_error("NS poisson values empty");
    std::vector<int> pod_sn = rand_gen.poisson_distribution(traffic, simulation_time);
    if (pod_sn.empty())
        throw std::runtime_error("SN poisson values empty");
    std::vector<int> pod_ew = rand_gen.poisson_distribution(traffic, simulation_time);
    if (pod_ew.empty())
        throw std::runtime_error("EW poisson values empty");
    std::vector<int> pod_we = rand_gen.poisson_distribution(traffic, simulation_time);
    if (pod_we.empty())
        throw std::runtime_error("WE poisson values empty");

    // lampak beallitasa
    the_intersection.get_light_north_south().set_green(true);
    the_intersection.get_light_east_west().set_green(false);

    std::cout << std::endl;
    std::cout << "Starting simulation" << std::endl;

    // a szimulacio ideje alatt
    for (int time = 0; time < simulation_time; time++)
    {
        // ha 10 masodperc eltelt
        if (time % 10 == 0)
        {
            // a lampak valtakoznak
            the_intersection.get_light_north_south().cycle();
            the_intersection.get_light_east_west().cycle();
            std::cout << std::endl;

            // kiirja a lampak allapotat
            the_intersection.get_light_north_south().get_green() ? std::cout << "\033[1;32mNS traffic light GREEN" : std::cout << "\033[1;31mNS traffic light RED";
            std::cout << "\033[0m" << std::endl;

            the_intersection.get_light_east_west().get_green() ? std::cout << "\033[1;32mEW traffic light GREEN" : std::cout << "\033[1;31mEW traffic light RED";
            std::cout << "\033[0m" << std::endl;

            std::cout << "\033[0m" << std::endl;

            stats.add_lamp_cycle(); // szamoljon egy ciklust
        }

        // ha nem tesztprogram, akkor 1 masodpercet varjon a kiirasnal
        if (readable)
            std::this_thread::sleep_for(std::chrono::seconds(1));

        // poissonbol generaljon annyi db random autot, statisztikahoz + info
        for (int i = 0; i < pod_ns[time]; i++)
        {
            vehicle *v = rand_gen.random_vehicle();
            // ha jarmu nem letezik, kivetelt dob
            if (v == nullptr)
                throw "Vehicle was not generated";
            // ha a jarmu teherauto, a teher sulyat szamoljuk
            if (v->get_type() == truck_)
            {
                truck *t = dynamic_cast<truck *>(v);
                if (t != nullptr)
                {
                    stats.add_cargo_weight(t->get_cargo_weight());
                }
            }
            // ha a jarmu szirenas, be van kapcsolva a szirena? ha igen szamoljuk
            if (v->get_type() == emergency_ && dynamic_cast<emergency *>(v)->get_siren() == 1)
            {
                emergency *e = dynamic_cast<emergency *>(v);
                if (e != nullptr)
                {
                    stats.add_sirens();
                }
            }
            // jarmu hozzadasa a statisztikahoz
            stats.add_vehicle(*v);
            // jarmu co2 kibocsatas hozzadasa a statisztikahoz
            stats.add_co2_emissions(v->get_co2_emission());
            // jarmu hozzadasa a keresztezodeshez
            the_intersection.add_vehicle_north_south(v);
        }

        for (int i = 0; i < pod_sn[time]; i++)
        {
            vehicle *v = rand_gen.random_vehicle();
            if (v == nullptr)
                throw "Vehicle was not generated";
            if (v->get_type() == truck_)
            {
                truck *t = dynamic_cast<truck *>(v);
                if (t != nullptr)
                {
                    stats.add_cargo_weight(t->get_cargo_weight());
                }
            }
            if (v->get_type() == emergency_ && dynamic_cast<emergency *>(v)->get_siren() == 1)
            {
                emergency *e = dynamic_cast<emergency *>(v);
                if (e != nullptr)
                {
                    stats.add_sirens();
                }
            }
            stats.add_vehicle(*v);
            stats.add_co2_emissions(v->get_co2_emission());
            the_intersection.add_vehicle_south_north(v);
        }

        for (int i = 0; i < pod_ew[time]; i++)
        {
            vehicle *v = rand_gen.random_vehicle();
            if (v == nullptr)
                throw "Vehicle was not generated";
            if (v->get_type() == truck_)
            {
                truck *t = dynamic_cast<truck *>(v);
                if (t != nullptr)
                {
                    stats.add_cargo_weight(t->get_cargo_weight());
                }
            }
            if (v->get_type() == emergency_ && dynamic_cast<emergency *>(v)->get_siren() == 1)
            {
                emergency *e = dynamic_cast<emergency *>(v);
                if (e != nullptr)
                {
                    stats.add_sirens();
                }
            }
            stats.add_vehicle(*v);
            stats.add_co2_emissions(v->get_co2_emission());
            the_intersection.add_vehicle_east_west(v);
        }

        for (int i = 0; i < pod_we[time]; i++)
        {
            vehicle *v = rand_gen.random_vehicle();
            if (v == nullptr)
                throw "Vehicle was not generated";
            if (v->get_type() == truck_)
            {
                truck *t = dynamic_cast<truck *>(v);
                if (t != nullptr)
                {
                    stats.add_cargo_weight(t->get_cargo_weight());
                }
            }
            if (v->get_type() == emergency_ && dynamic_cast<emergency *>(v)->get_siren() == 1)
            {
                emergency *e = dynamic_cast<emergency *>(v);
                if (e != nullptr)
                {
                    stats.add_sirens();
                }
            }
            stats.add_vehicle(*v);
            stats.add_co2_emissions(v->get_co2_emission());
            the_intersection.add_vehicle_west_east(v);
        }

        // ha ns zold, mozogjanak ns sn. ew we alljon meg
        if (the_intersection.get_light_north_south().get_green())
        {
            move_vehicles(the_intersection.get_vehicles_north_south(), the_intersection.get_north_south(), "Stroustrup Road N->S");
            move_vehicles(the_intersection.get_vehicles_south_north(), the_intersection.get_south_north(), "Stroustrup Road S->N");
            stop_vehicles(the_intersection.get_vehicles_east_west(), the_intersection.get_east_west(), "Bit Boulevard E->W");
            stop_vehicles(the_intersection.get_vehicles_west_east(), the_intersection.get_west_east(), "Bit Boulevard W->E");
        }
        // ha ew zold, mozogjanak ew we. ns sn alljon meg
        if (the_intersection.get_light_east_west().get_green())
        {
            move_vehicles(the_intersection.get_vehicles_east_west(), the_intersection.get_east_west(), "Bit Boulevard E->W");
            move_vehicles(the_intersection.get_vehicles_west_east(), the_intersection.get_west_east(), "Bit Boulevard W->E");
            stop_vehicles(the_intersection.get_vehicles_north_south(), the_intersection.get_north_south(), "Stroustrup Road N->S");
            stop_vehicles(the_intersection.get_vehicles_south_north(), the_intersection.get_south_north(), "Stroustrup Road S->N");
        }
    }
}

void simulation::stop_vehicles(const std::vector<vehicle *> &vehicles, road &current_road, const std::string &road_name)
{
    // minden auton vegigmegy
    for (size_t v = 0; v < vehicles.size(); v++)
    {
        // aktualis auto
        vehicle *current_vehicle = vehicles[v];
        if (current_vehicle == nullptr)
            throw "trying to stop a non existing vehicle";
        // ha az auto elhagyta a keresztezodest, mozoghat, (sarga lampa)
        if (current_vehicle->get_position() > current_road.get_light_position() && current_vehicle->get_position() < current_road.get_length())
        {
            current_vehicle->set_speed(current_road.get_speed_limit());
            current_vehicle->move(1);
            stats.add_average_speed((current_vehicle->get_speed()));
            std::cout << std::left << std::setw(10) << current_vehicle->get_license_plate() + " " + (current_vehicle->get_type_name()) << " is moving on "
                      << "\033[1;33m" << road_name << "\033[0m"
                      << ", position: " << current_vehicle->get_position() << std::endl;
        }
        // kulonben alljon meg (piros)
        else if (current_vehicle->is_moving())
        {
            current_vehicle->stop();
            if (current_vehicle->get_position() != 0 && road_name != "test")
                std::cout << std::left << std::setw(10) << current_vehicle->get_license_plate() + " " + (current_vehicle->get_type_name()) << " stopped on "
                          << "\033[1;31m" << road_name << "\033[0m"
                          << ", position: " << current_vehicle->get_position() << std::endl;
        }
    }
}

void simulation::move_vehicles(const std::vector<vehicle *> &vehicles, road &current_road, const std::string &road_name)
{

    std::string color = get_light(current_road) ? "\033[1;32m" : "\033[1;31m";
    for (size_t v = 0; v < vehicles.size(); v++)
    {
        vehicle *current_vehicle = vehicles[v];
        // ha auto nem letezik, kivetelt dob
        if (current_vehicle == nullptr)
            throw "trying to move a non existing vehicle";
        // auto sebesseg beallitasa az ut sebesseg limit-bol
        if (current_vehicle->get_position() <= current_road.get_length()) {
            current_vehicle->set_speed(current_road.get_speed_limit());
            current_vehicle->move(1);
            stats.add_average_speed((current_vehicle->get_speed()));
            // ha nem teszt a program, írja ki a mozgást
            if (road_name != "test")
                std::cout << std::left << std::setw(10) << current_vehicle->get_license_plate() + " " + (current_vehicle->get_type_name()) << " is moving on " << color << road_name << "\033[0m"
                        << ", position: " << current_vehicle->get_position() << std::endl;
        }
        }
}

bool simulation::get_light(road &current_road)
{
    if (&current_road == &the_intersection.get_north_south() || &current_road == &the_intersection.get_south_north())
        return the_intersection.get_light_north_south().get_green();

    if (&current_road == &the_intersection.get_east_west() || &current_road == &the_intersection.get_west_east())
        return the_intersection.get_light_east_west().get_green();
    return false;
}
