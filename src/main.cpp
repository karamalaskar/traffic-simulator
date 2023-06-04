#include <iostream>
#include "../include/simulation.hpp"
#include "../include/statistics.hpp"
#include "../include/intersection.hpp"
#include "../include/traffic_light.hpp"
#include "../include/road.hpp"
#include "../include/random_generator.hpp"
#include "../include/vehicle.hpp"
#include "../include/intensity.hpp"
#include "../include/gtest_lite.h"


using std::cout;

int main(int argc, char *argv[])
{
    // random seed
    srand(int(time(NULL)));

    // szimuláció időtartama
    int sim_time;
    // forgalom intenzitása
    int intensity_choice;

    // ha 3 argumentum van, a program nem kerdezi a felhasznalotol a szimulacio idotartamat es a forgalom intenzitasat
    if (argc == 3)
    {
        sim_time = std::stod(argv[1]);
        intensity_choice = std::stoi(argv[2]);
    }
    else
    {
        // kulonben kerdezi
        cout << "Simulation time: ";
        std::cin >> sim_time;
        // ha a szimulacio ido kisebb vagy egyenlo mint 0, kivetelt dob
        if (sim_time <= 0)
            throw std::runtime_error("Simulation time must be positive");
        // forgalom intenzitas beallitasa
        cout << "Traffic intensity (1. light, 2. medium, 3. heavy): ";
        std::cin >> intensity_choice;
        if (intensity_choice < 1 || intensity_choice > 3)
            throw std::runtime_error("Traffic intensity must be between 1 and 3");
    }
    // 0. light, 1. medium, 2. heavy
    intensity_choice -= 1;

    // random generátor
    random_generator rand_gen;

    // poisson eloszlas generalasa
    std::vector<int> arrival_times = rand_gen.poisson_distribution(static_cast<intensity>(intensity_choice), sim_time);
    if (arrival_times.size() != (size_t)sim_time)
        throw std::runtime_error("Error in poisson distribution, simulation time and arrival times vector size must be equal");

    // utak letrehozasa
    road road1(1000, 30, 500);
    road road2(1000, 30, 500);
    road road3(1000, 30, 500);
    road road4(1000, 30, 500);

    // forgalmi lampak letrehozasa
    traffic_light light1;
    traffic_light light2;

    // utkozet letrehozasa
    intersection intersection1(road1, road2, light1, road3, road4, light2);
    if (intersection1.get_north_south().get_length() != intersection1.get_south_north().get_length() || intersection1.get_east_west().get_length() != intersection1.get_west_east().get_length())
        throw std::runtime_error("Error in intersection, parallel road lengths must be equal");

    // szimulacio letrehozasa
    simulation sim(sim_time, intersection1, static_cast<intensity>(intensity_choice));
    // szimulacio futtatasa
    bool readable = true;
    //ha teszt program, nem kell hogy olvashato legyen a kiiras
    if (argc == 3)
        sim.run(!readable);
    else 
        sim.run(readable);
    // statisztika kiirasa
    sim.get_stats().print_statistics();
    
    if (argc == 3) {
        /** @brief Test Unit 1: autók hozzáadása a kereszteződéshez*/
        TEST(intersection, add_vehicle)
        
            random_generator rand_gen_test;

            vehicle *v1 = rand_gen_test.random_vehicle();
            vehicle *v2 = rand_gen_test.random_vehicle();
            vehicle *v3 = rand_gen_test.random_vehicle();
            vehicle *v4 = rand_gen_test.random_vehicle();

            road road_test(42, 42, 42);

            traffic_light light_test;

            intersection intersection_test(road_test, road_test, light_test, road_test, road_test, light_test);

            intersection_test.add_vehicle_north_south(v1);
            intersection_test.add_vehicle_south_north(v2);
            intersection_test.add_vehicle_east_west(v3);
            intersection_test.add_vehicle_west_east(v4);

            EXPECT_EQ(intersection_test.get_vehicles_north_south().size(), size_t(1));
            EXPECT_EQ(intersection_test.get_vehicles_south_north().size(), size_t(1));
            EXPECT_EQ(intersection_test.get_vehicles_east_west().size(), size_t(1));
            EXPECT_EQ(intersection_test.get_vehicles_west_east().size(), size_t(1));
            EXPECT_THROW(intersection_test.add_vehicle_north_south(nullptr), std::runtime_error);



        END


        /** @brief Test Unit 2: poisson elemei száma akkora, mint a szimuláció idő*/
        TEST(random_generator, poisson_distribution_elements)
            size_t sim_time_test = 10000;
            random_generator rand_gen_test;
            std::vector<int> poisson = rand_gen_test.poisson_distribution(light, sim_time_test);
            EXPECT_EQ(poisson.size(), sim_time_test);
        END

        /** @brief Test Unit 3: Poisson helyessége, középérték és variancia számolással*/
        TEST(random_generator, poisson_distribution_functionality) double lambda = 0.5;
            size_t sim_time_test = 10000;
            random_generator rand_gen_test;
            std::vector<int> poisson = rand_gen_test.poisson_distribution(light, sim_time_test);
            double sum = 0;
            for (int value : poisson)
                sum += value;
            double mean = static_cast<double>(sum) / sim_time_test;
            double sum_squared_diff = 0.0;
            for (double value : poisson)
            {
                double diff = value - mean;
                sum_squared_diff += diff * diff;
            }
            double variance = sum_squared_diff / sim_time_test;

            EXPECT_TRUE(std::abs(mean - lambda) < 0.1);
            EXPECT_TRUE(std::abs(variance - lambda) < 0.1);

        END

        /** @brief Test Unit 4: Autók mozgása*/
        TEST(simulation, move_vehicles)

            random_generator rand_gen_test;


            road road_test(42, 42, 42);


            traffic_light light_test;
            
            std::vector<vehicle*>vehicles;
            vehicle *v = rand_gen_test.random_vehicle();
            vehicles.push_back(v);

            intersection intersection_test(road_test, road_test, light_test, road_test, road_test, light_test);

            simulation sim_test(42, intersection_test, light);
            sim_test.move_vehicles(vehicles, road_test, "test");
            EXPECT_TRUE(vehicles[0]->is_moving());
            delete v;
        END

        /** @brief Test Unit 5: Autók megállítása*/
        TEST(simulation, stop_vehicles)

            random_generator rand_gen_test;


            road road_test(1000, 30, 500);

            traffic_light light_test;
            
            std::vector<vehicle*>vehicles;
            vehicle *v = rand_gen_test.random_vehicle();
            vehicles.push_back(v);

            intersection intersection1(road_test, road_test, light_test, road_test, road_test, light_test);

            simulation sim_test(1, intersection1, light);
            sim_test.move_vehicles(vehicles, road_test, "test");
            sim_test.stop_vehicles(vehicles, road_test, "test");
            EXPECT_FALSE(vehicles[0]->is_moving());
            delete v;
        END
    }
}

