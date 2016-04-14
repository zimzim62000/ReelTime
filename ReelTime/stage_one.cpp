#include "stage_one.h"
#include <iostream>
#include <string> 
#include <math.h>
#include "cat.h"

void stage_one::Initialize(sf::RenderWindow* window)
{
	this->manager = new EntityManager();
	this->mapGame = new MapGame();
	this->mapGame->Load("map2.json");

	this->Menu = new MenuInterface();

	std::pair<int, int> pair = this->mapGame->getPositionAvailable();
	std::cout << "cat x : " << pair.first << " cat y : " << pair.second << std::endl;
	Cat* cat = new Cat(this->manager, this->mapGame, pair.first*this->mapGame->tileWidth, pair.second*this->mapGame->tileHeight, 100);
	this->manager->Add("cat", cat);

	this->camera = new Camera();
	this->camera->reset(sf::FloatRect(0, 0, window->getSize().x, window->getSize().y));
	this->camera->folowEntity(cat);
}

void stage_one::Update(game_speed* gameSpeed, sf::RenderWindow* window)
{
	gameSpeed->Update(window);

	if(!gameSpeed->Paused()){
		this->manager->Update(gameSpeed, window);

		Entity* cat = this->manager->Get("cat");
		this->camera->folowEntity(cat);
	}
}

void stage_one::Render(game_speed* gameSpeed, sf::RenderWindow* window)
{
	window->setView(*this->camera);
	window->draw(*this->mapGame);

	this->manager->Render(gameSpeed, window);

	sf::View defaultView = window->getDefaultView();
	window->setView(defaultView);
	window->draw(*this->Menu);
	window->draw(*gameSpeed);
	window->draw(*gameSpeed->speedText);
	window->draw(*gameSpeed->fpsText);
	window->draw(*gameSpeed->counterSecondText);
}

void stage_one::Destroy(sf::RenderWindow* window)
{
	
}