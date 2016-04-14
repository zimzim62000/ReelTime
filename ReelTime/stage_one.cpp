#include "stage_one.h"
#include <iostream>
#include <string> 
#include <math.h>
#include "cat.h"

void stage_one::Initialize(sf::RenderWindow* window)
{
	this->manager = new EntityManager();
	this->mapGame = new MapGame();
	this->mapGame->Load("map.json");

	std::pair<int, int> pair = this->mapGame->getPositionAvailable();
	std::cout << "cat x : " << pair.first << " cat y : " << pair.second << std::endl;
	Cat* cat = new Cat(this->manager, this->mapGame, pair.first*this->mapGame->tileWidth, pair.second*this->mapGame->tileHeight, 50);
	this->manager->Add("cat", cat);

	this->camera = new Camera();
	this->camera->reset(sf::FloatRect(0, 0, window->getSize().x, window->getSize().y));
	this->camera->folowEntity(cat);

	this->target = new sf::CircleShape();
	this->target->setFillColor(sf::Color::Blue);
	this->target->setRadius(this->mapGame->tileWidth / 2);

	this->targetOne = new sf::CircleShape();
	this->targetOne->setFillColor(sf::Color::Cyan);
	this->targetOne->setRadius(this->mapGame->tileWidth / 4);
	this->targetOne->setOrigin(-this->mapGame->tileWidth / 4, -this->mapGame->tileHeight / 4);

}

void stage_one::Update(game_speed* gameSpeed, sf::RenderWindow* window)
{
	gameSpeed->Update(window);

	if(!gameSpeed->Paused()){
		this->manager->Update(gameSpeed, window);

		Entity* cat = this->manager->Get("cat");
		this->camera->folowEntity(cat);
		this->target->setPosition(cat->getTarget().first*this->mapGame->tileWidth, cat->getTarget().second*this->mapGame->tileHeight);
		this->targetOne->setPosition(cat->getTargetOne().first, cat->getTargetOne().second);
	}
}

void stage_one::Render(game_speed* gameSpeed, sf::RenderWindow* window)
{
	window->setView(*this->camera);

	window->draw(*this->mapGame);
	this->manager->Render(gameSpeed, window);

	window->draw(*this->target);
	window->draw(*this->targetOne);

	window->draw(*gameSpeed);
	window->draw(*gameSpeed->speedText);
	window->draw(*gameSpeed->fpsText);
	window->draw(*gameSpeed->counterSecondText);
}

void stage_one::Destroy(sf::RenderWindow* window)
{
	
}