#pragma once

#include <SFML/Graphics.hpp>
#include <math.h>

using namespace std;

float Dist(const sf::Vector2f &v, const sf::Vector2f &u)
{
	return sqrt(pow(v.x-u.x, 2) + pow(v.y-u.y, 2));
}