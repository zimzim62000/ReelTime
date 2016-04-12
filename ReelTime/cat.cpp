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
	this->mapGame = mapGame;
	this->direction.x = 0;
	this->direction.y = 0;
	this->setOrigin(0, 0);
	this->IsONScene = true;
}

bool Cat::Update(game_speed* gameSpeed, sf::RenderWindow* window)
{
	if (this->getBusy() == false) {
		this->busy = true;
		this->onMove = true;
		PathFinding path;
		this->target = this->mapGame->getPositionAvailable();
		path.findRoad(this->mapGame, int(this->getPosition().x/this->mapGame->tileWidth), int(this->getPosition().y / this->mapGame->tileHeight), this->target.first, this->target.second);
		for (int i(0); i < path.chemin.size(); i++) {
			point pt = path.chemin.front();
			this->AddTarget(pt.x*this->mapGame->tileWidth, pt.y*this->mapGame->tileHeight);
			path.chemin.pop_front();
		}
	}

	this->MoveOnTarget(gameSpeed);

	Entity::Update(gameSpeed, window);

	return true;
}

void Cat::AddTarget(const int x, const int y)
{
	std::pair<int, int> pair = std::pair<int, int>(x, y);
	this->listPoint.push(pair);
}

void Cat::MoveOnTarget(game_speed* gameSpeed)
{
	if (this->listPoint.size() > 0) {
		std::pair<int, int> pair = this->listPoint.front();

		if (this->velocity.x == 0 && this->velocity.y == 0) {
			sf::Vector2f diff = utility::diffVecteur2(sf::Vector2f(pair.first, pair.second), sf::Vector2f(this->getPosition().x, this->getPosition().y));
			this->velocity = utility::normalizeVecteur(diff);
			return;
		}
		if (abs(abs(pair.first) - abs(this->getPosition().x)) <= abs(this->speed*this->velocity.x*gameSpeed->getGameSpeedDeltaTime())) {
			this->setPosition(pair.first, pair.second);
			this->velocity.x = 0;
			this->velocity.y = 0;
			this->listPoint.pop();
			return;
		}
		if (abs(abs(pair.second) - abs(this->getPosition().y)) <= abs(this->speed*this->velocity.y*gameSpeed->getGameSpeedDeltaTime())) {
			this->setPosition(pair.first, pair.second);
			this->velocity.x = 0;
			this->velocity.y = 0;
			this->listPoint.pop();
			return;
		}
	}
	else {
		this->listPoint.empty();
		this->target.first = 0;
		this->target.second = 0;
		this->onMove = false;
		this->busy = false;
	}
}