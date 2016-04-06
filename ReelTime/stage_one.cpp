#include "stage_one.h"
#include <iostream>
#include <string> 
#include <math.h>


void stage_one::Initialize(sf::RenderWindow* window)
{
	this->manager = new EntityManager();

	this->gameSpeed = new game_speed();
	this->gameSpeed->Initialize(window);
}

void stage_one::Update(float const dt, sf::RenderWindow* window)
{
	this->gameSpeed->Update(dt, window);
	if(!this->gameSpeed->Paused()){
		this->manager->Update(dt, this->gameSpeed, window);
	}
}

void stage_one::Render(float const dt, sf::RenderWindow* window)
{
	window->draw(*this->gameSpeed);
	this->gameSpeed->Render(dt, window);
	this->manager->Render(dt, this->gameSpeed, window);
}

void stage_one::Destroy(sf::RenderWindow* window)
{
	
}