#include "../include/traffic_light.hpp"

void traffic_light::set_green(const bool &state) { is_green = state; }
bool traffic_light::get_green() const { return is_green; }
void traffic_light::cycle()
{
    is_green = !is_green;
}

