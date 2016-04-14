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
	this->setOrigin(0, 0);
	this->IsONScene = true;
	this->listPoint.empty();
	this->countMove = 0;
	this->countMoveMax = 500;
	this->target = std::pair<int, int>(0, 0);

	this->targetView = new sf::CircleShape();
	this->targetView->setFillColor(sf::Color::Blue);
	this->targetView->setRadius(this->mapGame->tileWidth / 2);

	this->targetOneView = new sf::CircleShape();
	this->targetOneView->setFillColor(sf::Color::Magenta);
	this->targetOneView->setRadius(this->mapGame->tileWidth / 4);
	this->targetOneView->setOrigin(-this->mapGame->tileWidth / 4, -this->mapGame->tileHeight / 4);
}


bool Cat::Update(game_speed* gameSpeed, sf::RenderWindow* window)
{
	if(this->countMove == 0){
		PathFinding path;
		bool find = false;
		while (find == false) {
			this->target = this->mapGame->getPositionAvailable();
			if (this->target.first * this->mapGame->tileWidth != this->getPosition().x && this->target.second * this->mapGame->tileHeight != this->getPosition().y) {
				find = true;
			}
			else {
				std::cout << "FAILLLLLLLLURE" << std::endl;
			}
		}

		//std::cout << "target x : " << this->target.first << " target y : " << this->target.second << std::endl;
		path.findRoad(this->mapGame, int(this->getPosition().x/this->mapGame->tileWidth), int(this->getPosition().y / this->mapGame->tileHeight), this->target.first, this->target.second);
		//std::cout << "chemin size : " << path.chemin.size() << std::endl;
		while (path.chemin.size() > 0) {
			point pt = path.chemin.front();
			this->AddTarget(pt.x*this->mapGame->tileWidth, pt.y*this->mapGame->tileHeight);
			path.chemin.pop_front();
		}
	}
	if(this->listPoint.size() != 0){
		this->MoveOnTarget(gameSpeed);
		Entity::Update(gameSpeed, window);
	}
	if (this->listPoint.size() == 0) {
		//std::cout << "end path" << std::endl;
		this->countMove = -1;
	}
	this->countMove++;
	return true;
}

void Cat::AddTarget(const int x, const int y)
{
	this->listPoint.push(std::pair<int, int>(x, y));
}

void Cat::MoveOnTarget(game_speed* gameSpeed)
{
	this->targetOne = this->listPoint.front();
	if (this->countMove == 0 || (this->velocity.x == 0 && this->velocity.y == 0)) {
		//std::cout << "new point " << std::endl;
		sf::Vector2f diff = utility::diffVecteur2(sf::Vector2f(this->targetOne.first, this->targetOne.second), sf::Vector2f(this->getPosition().x, this->getPosition().y));
		//utility::dumpVecteur2(diff);
		sf::Vector2f normalise = utility::normalizeVecteur(diff);
		//utility::dumpVecteur2(normalise);
		this->velocity = normalise;
	}
	float distanceX = abs(this->targetOne.first - this->getPosition().x);
	float distanceY = abs(this->targetOne.second - this->getPosition().y);
	float speedX = abs(this->velocity.x * this->speed * gameSpeed->getGameSpeedDeltaTime());
	float speedY = abs(this->velocity.y * this->speed * gameSpeed->getGameSpeedDeltaTime());

	//std::cout << "distanceX " << distanceX <<  " distance y " << distanceY << " speedx " << speedX << " speed y "  << speedY << std::endl;
	if (distanceX <= speedX && distanceY <= speedY) {
		//std::cout << "aye aye" << std::endl;
		this->setPosition(this->targetOne.first, this->targetOne.second);
		this->velocity.x = 0;
		this->velocity.y = 0;
		this->listPoint.pop();
	}
}