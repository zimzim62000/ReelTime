#include "stage_one.h"
#include <iostream>
#include <string> 
#include <math.h>
#include "field.h"

void stage_one::Initialize(sf::RenderWindow* window)
{
	this->manager = new EntityManager();

	Entity* fields = new Field(this->manager, 150 , 150, 100);
	this->manager->Add("field", fields);
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
	window->draw(*gameSpeed);
	window->draw(*gameSpeed->speedText);
	window->draw(*gameSpeed->fpsText);
	this->manager->Render(gameSpeed, window);
}

void stage_one::Destroy(sf::RenderWindow* window)
{
	
}