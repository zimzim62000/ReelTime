#pragma once


#include <SFML/Graphics.hpp>
#include <string>
#include "entity_manager.h"
#include "game_speed.h"
#include <queue>
#include "map_tile.h"


typedef enum
{
	NONE = -1,
	LEFT = 0,
	RIGHT = 1,
	UP = 2,
	DOWN = 3,
	TOP_LEFT = 4,
	TOP_RIGHT = 5,
	BOTTOM_LEFT = 6,
	BOTTOM_RIGHT = 7
}Direction;


class MapGame : public sf::Sprite
{
public:
	MapGame();

	void Load(std::string filename);

	void Update(game_speed* gameSpeed, sf::RenderWindow* window);

	MapTile* getOnThisPositionNoeud(const int x, const int y);

	std::pair<int, int> getPositionAvailable();

	~MapGame();

	std::string tileSet;
	int width, height, tileWidth, tileHeight;
	int* data;

private:

	sf::Texture* texture;
	sf::Image* tileSetTexture;
	EntityManager* entityManager;

	MapTile* black_case;
	MapTile* white_case;
};