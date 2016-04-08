#include "stage_one.h"
#include <iostream>
#include <string> 
#include <math.h>
#include "field.h"


void stage_one::Initialize(sf::RenderWindow* window)
{
	this->manager = new EntityManager();

	Entity* fields = new Field(this->manager, 150 , 150);
	this->manager->Add("field", fields);
	this->gameSpeed = new game_speed();
	this->gameSpeed->Initialize(window);
}

void stage_one::Update(float const dt, sf::RenderWindow* window)
{
	this->gameSpeed->Update(dt, window);
	if(!this->gameSpeed->Paused()){
		this->manager->Update(this->gameSpeed, window);
	}
}

void stage_one::Render(float const dt, sf::RenderWindow* window)
{
	window->draw(*this->gameSpeed);
	this->manager->Render(this->gameSpeed, window);
}

void stage_one::Destroy(sf::RenderWindow* window)
{
	
}