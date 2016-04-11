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
	Entity* cat = new Cat(this->manager, this->mapGame, pair.first*this->mapGame->tileWidth, pair.second*this->mapGame->tileHeight, 100);
	this->manager->Add("cat", cat);
}

void stage_one::Update(game_speed* gameSpeed, sf::RenderWindow* window)
{
	gameSpeed->Update(window);
	if(!gameSpeed->Paused()){
		this->manager->Update(gameSpeed, window);
	}
}

void stage_one::Render(game_speed* gameSpeed, sf::RenderWindow* window)
{
	window->draw(*this->mapGame);
	this->manager->Render(gameSpeed, window);

	window->draw(*gameSpeed);
	window->draw(*gameSpeed->speedText);
	window->draw(*gameSpeed->fpsText);
}

void stage_one::Destroy(sf::RenderWindow* window)
{
	
}