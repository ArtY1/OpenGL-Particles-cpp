#pragma once

#include <SFML/Graphics.hpp>

using namespace std;

inline float Dist(const sf::Vector2f &v, const sf::Vector2f &u)
{
	return sqrt(pow(v.x-u.x, 2) + pow(v.y-u.y, 2));
}

inline float Norm(const sf::Vector2f &v)
{
	return sqrt(pow(v.x, 2) + pow(v.y, 2));
}