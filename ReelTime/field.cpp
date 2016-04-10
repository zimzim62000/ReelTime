#include "stage_one.h"
#include "field.h"
#include <iostream>
#include "utility.h"


Field::Field(EntityManager* entityManager, float x, float y, const int speed) : Entity(speed)
{
	this->Load("fields2.png");
	this->setPosition(x, y);
	this->groupId = 1;
	this->entityManager = entityManager;
	this->direction.x = 0;
	this->direction.y = 0;
	this->angle = 0;
	this->setOrigin(0, 0);
	this->IsONScene = true;

	this->count = 10;
	this->countMax = 9;
}

bool Field::Update(game_speed* gameSpeed, sf::RenderWindow* window)
{
	if (gameSpeed->getGameTick() == true) {
		this->count++;
		if (this->count > this->countMax) {
			this->count = 0;
			float tmp;
			tmp = utility::randInt(100, true);
			this->velocity.x = tmp / 50;
			tmp = utility::randInt(100, true);
			this->velocity.y = tmp / 50;
		}
	}

	if (this->getPosition().x < 0){
		this->velocity.x *= -1;
		this->setPosition(0, this->getPosition().y);
	}
	if (this->getPosition().x + this->getGlobalBounds().width > window->getSize().x) {
		this->velocity.x *= -1;
		this->setPosition(window->getSize().x - this->getGlobalBounds().width, this->getPosition().y);
	}
	if (this->getPosition().y < 0 ){
		this->velocity.y *= -1;
		this->setPosition(this->getPosition().x, 0);
	}
	if (this->getPosition().y + this->getGlobalBounds().height > window->getSize().y) {
		this->velocity.y *= -1;
		this->setPosition(this->getPosition().x, window->getSize().y - this->getGlobalBounds().height);
	}

	Entity::Update(gameSpeed, window);

	return true;
}