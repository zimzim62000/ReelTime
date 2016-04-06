#pragma once

#include "entity_manager.h"

EntityManager::EntityManager() { this->numberId = 0; }

void EntityManager::Add(std::string name, Entity* entity)
{
	std::unordered_map<std::string, Entity*>::const_iterator found = this->entities.find(name);
	if(found !=  this->entities.end()){
		name += "0";
		found = this->entities.find(name);
	}
	entity->setName(name);
	entity->setId(this->numberId);
	entity->setOnScene(true);
	this->entities.insert(std::make_pair(name, entity));
	this->numberId++;
}

bool EntityManager::Update(float const dt, game_speed* gameSpeed, sf::RenderWindow* window)
{
	for(auto& iterator : this->entities){
		iterator.second->Update(dt, window);
	}
	return true;
}

void EntityManager::Render(float const dt, game_speed* gameSpeed, sf::RenderWindow* window)
{
	for (auto& iterator : this->entities) {
		window->draw(*iterator.second);
	}
}

Entity* EntityManager::Get(std::string name)
{
	std::unordered_map<std::string, Entity*>::const_iterator found = this->entities.find(name);
	
	if (found == this->entities.end())
	{
		return NULL;
	}
	else
	{
		return found->second;
	}
}

Entity* EntityManager::GetAtThisPosition(const int x, const int y, const int tileWidth, const int tileHeight)
{
	for (auto& iterator : this->entities) {
		if(iterator.second->getGlobalBounds().intersects(sf::FloatRect(x, y, 1 , 1))){
			return iterator.second;
		}
	}
	return new Entity();
}