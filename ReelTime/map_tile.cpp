#include "map_tile.h"

MapTile::MapTile(const bool passable, const int weight, const std::string fileName)
{
	this->passable = passable;
	this->weight = weight;
	this->fileName = fileName;
	this->loadFromFile("Graphics/Images/" + this->fileName);

	Image::Image();
}