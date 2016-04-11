#pragma once


#include <SFML/Graphics.hpp>
#include <string>

class MapTile : public sf::Image
{
public:
	MapTile(const bool passable, const int weight, const std::string fileName);
	bool passable;
	int weight;
	std::string fileName;
};