#include <iostream>
#include <fstream>
#include <sstream>
#include "map_game.h"
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"



using namespace rapidjson;

MapGame::MapGame()
{
	this->texture = new sf::Texture();
	this->tileSetTexture = new sf::Image();

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

	/* map case*/
	Value& tilesets = mapFileDoc["tilesets"];
	Value& properties = tilesets[0]["tileproperties"];

	Value& blackcase = tilesets[0]["tileproperties"]["0"];
	this->black_case = new case_game(std::stoi(blackcase["passable"].GetString()), std::stoi(blackcase["weight"].GetString()));
	Value& whitecase = tilesets[0]["tileproperties"]["3"];
	this->white_case = new case_game(std::stoi(whitecase["passable"].GetString()), std::stoi(whitecase["weight"].GetString()));

	this->data = new int[this->width * this->height];

	if (dataArray.IsArray())
	{
		for (int i = 0; i < dataArray.Capacity(); i += 1)
		{
			this->tileSet = dataArray[i]["name"].GetString();
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

	this->tileSetTexture->loadFromFile("Graphics/Tilesets/" + this->tileSet);

	sf::Image tileWhite, tileGrey, tileBurn, tileBlack;

	tileBlack.create(this->tileWidth, this->tileHeight);
	tileWhite.create(this->tileWidth, this->tileHeight);


	tileBlack.copy(*this->tileSetTexture, 0, 0, sf::IntRect(0, 0, this->tileWidth, this->tileHeight), true);
	tileWhite.copy(*this->tileSetTexture, 0, 0, sf::IntRect(this->tileWidth, 0, this->tileWidth, this->tileHeight), true);


	for (int y = 0; y < this->height; y += 1)
	{
		for (int x = 0; x < this->width; x += 1)
		{
			switch (this->data[x + y *  this->width])
			{
			case 1:
				this->texture->update(tileBlack, x * this->tileWidth, y * this->tileHeight);
				break;
			case 2:
				this->texture->update(tileWhite, x * this->tileWidth, y * this->tileHeight);
				break;
			default:
				break;
			}
		}
	}

	this->setTexture(*this->texture);
}
