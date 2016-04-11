#include "cat.h"
#include <iostream>
#include "utility.h"
#include "path_finding.h"

Cat::Cat(EntityManager* entityManager, MapGame* mapGame, float x, float y, const int speed) : Entity(speed)
{
	this->Load("doudou.png");
	this->setPosition(x, y);
	this->groupId = 2;
	this->entityManager = entityManager;
	this->direction.x = 0;
	this->direction.y = 0;
	this->setOrigin(0, 0);
	this->IsONScene = true;
}

bool Cat::Update(game_speed* gameSpeed, sf::RenderWindow* window)
{
	if (this->getBusy() == false) {
		//@todo implement after sleeping lol
		/*
		PathFinding path;
		std::pair<int, int> pair = this->mapGame->getPositionAvailable();
		path.findRoad(this->mapGame, this->getPosition().x/this->mapGame->tileWidth, this->getPosition().y / this->mapGame->tileHeight, pair.first*this->mapGame->tileWidth, pair.second*this->mapGame->tileWidth);
		path.chemin;
		*/
	}

	Entity::Update(gameSpeed, window);

	return true;
}