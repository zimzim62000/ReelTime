#include <iostream>
#include <fstream>
#include <sstream>
#include "map_game.h"
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include "utility.h"

using namespace rapidjson;

MapGame::MapGame()
{
	this->texture = new sf::Texture();

	this->width = 0;
	this->height = 0;
	this->tileWidth = 0;
	this->tileHeight = 0;
}

void MapGame::Load(std::string filename)
{
	std::ifstream mapFile("Graphics/Maps/" + filename);
	std::string mapFileData((std::istreambuf_iterator<char>(mapFile)),
	std::istreambuf_iterator<char>());
	Document mapFileDoc;
	mapFileDoc.Parse(mapFileData.c_str());

	this->width = mapFileDoc["width"].GetInt();
	this->height = mapFileDoc["height"].GetInt();
	this->tileWidth = mapFileDoc["tilewidth"].GetInt();
	this->tileHeight = mapFileDoc["tileheight"].GetInt();

	Value& dataArray = mapFileDoc["layers"];

	this->black_case = new MapTile(false, 1000, "black.png");
	this->white_case = new MapTile(true, 1, "white.png");

	this->data = new int[this->width * this->height];

	if (dataArray.IsArray())
	{
		for (int i = 0; i < dataArray.Capacity(); i += 1)
		{
			Value& dataTileset = dataArray[i]["data"];

			for (int y = 0; y < this->height; y += 1)
			{
				for (int x = 0; x < this->width; x += 1)
				{
					int tmp = dataTileset[x + y * this->width].GetInt();
					this->data[x + y * this->width] = tmp;
				}
			}
		}
	}

	this->texture->create(this->width * this->tileWidth, this->height * this->tileHeight);

	for (int y = 0; y < this->height; y += 1)
	{
		for (int x = 0; x < this->width; x += 1)
		{
			switch (this->data[x + y *  this->width])
			{
			case 1:
				this->texture->update(*this->white_case, x * this->tileWidth, y * this->tileHeight);
				break;
			case 2:
				this->texture->update(*this->black_case, x * this->tileWidth, y * this->tileHeight);
				break;
			default:
				break;
			}
		}
	}

	this->setTexture(*this->texture);
}

void MapGame::Update(game_speed* gameSpeed, sf::RenderWindow* window)
{

}

MapTile* MapGame::getOnThisPositionNoeud(const int x, const int y)
{
	switch (this->data[x + y *  this->width])
	{
	case 1:
		return this->white_case;
		break;
	case 2:
	default:
		return this->black_case;
		break;
	}
}

std::pair<int, int> MapGame::getPositionAvailable()
{
	int x, y;
	bool find = false;
	while (find == false)
	{
		x = utility::randInt(this->width, false);
		y = utility::randInt(this->height, false);
		if (this->getOnThisPositionNoeud(x, y)->passable == true) {
			find = true;
		}
	}
	return std::pair<int, int>(x, y);
}


MapGame::~MapGame()
{

}