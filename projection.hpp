#pragma once

#include <cmath>
#include "vector.hpp"
#include <sfml/Graphics.hpp>



Vector GetLocalPosition(Vector pos1, Vector pos2, sf::Vector2<double> rotation);

sf::Vector2f Project(Vector locap_position, double focal_length);


