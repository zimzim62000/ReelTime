#include "cat.h"
#include <iostream>
#include "utility.h"
#include "path_finding.h"

Cat::Cat(EntityManager* entityManager, MapGame* mapGame, float x, float y, const int speed) : Entity(speed)
{
	this->Load("doudou.png");
	this->setPosition(x, y);
	this->groupId = 1;
	this->entityManager = entityManager;
	this->mapGame = mapGame;
	this->setOrigin(0, 0);
	this->IsONScene = true;
	this->listPoint.empty();
	this->countMove = 0;
	this->countMoveMax = 500;
	this->target = std::pair<int, int>(0, 0);
	this->stock = 0;

	this->font = new sf::Font();
	this->font->loadFromFile("Graphics/font.ttf");

	this->stockText = new sf::Text("000", *this->font, 28U);
	this->stockText->setPosition(this->getPosition());
	this->stockText->setColor(sf::Color::Yellow);

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
		this->pathLine.empty();
		PathFinding path;
		bool find = false;
		while (find == false) {
			this->target = this->mapGame->getPositionAvailable();
			float x, y;
			x = this->target.first * this->mapGame->tileWidth;
			y = this->target.second * this->mapGame->tileHeight;
			this->targetView->setPosition(x, y);
			if (x != this->getPosition().x && y != this->getPosition().y) {
				find = true;
			}
		}

		//std::cout << "target x : " << this->target.first << " target y : " << this->target.second << std::endl;
		path.findRoad(this->mapGame, int(this->getPosition().x/this->mapGame->tileWidth), int(this->getPosition().y / this->mapGame->tileHeight), this->target.first, this->target.second);
		//std::cout << "chemin size : " << path.chemin.size() << std::endl;
		int count = 0;
		while (path.chemin.size() > 0) {
			int x, y;
			point pt = path.chemin.front();
			x = pt.x*this->mapGame->tileWidth;
			y = pt.y*this->mapGame->tileHeight;
			this->pathLine.push_back(sf::Vertex(sf::Vector2f(x+this->mapGame->tileWidth/2, y+this->mapGame->tileHeight / 2), sf::Color::Red));
			this->AddTarget(x, y);
			path.chemin.pop_front();
			count++;
		}
	}
	if(this->listPoint.size() != 0){
		this->MoveOnTarget(gameSpeed);
		Entity::Update(gameSpeed, window);
		this->stockText->setPosition(this->getPosition());
	}
	if (this->listPoint.size() == 0) {
		//std::cout << "end path" << std::endl;
		this->countMove = -1;
	}
	this->countMove++;

	this->CheckCollision();

	return true;
}

bool Cat::Render(game_speed* gameSpeed, sf::RenderWindow* window)
{
	//sf::View defaultView = window->getDefaultView();
	//window->setView(defaultView);
	window->draw(*this->targetView);
	window->draw(*this->targetOneView);
	window->draw(*this->stockText);
	/*
	for (int i(0); i < this->pathLine.size(); i++)
	{
		window->draw(&this->pathLine.at(i), 1, sf::Lines);
	}
	*/
	if(this->pathLine.size()  > 0){
		window->draw(&this->pathLine.at(0), this->pathLine.size(), sf::LinesStrip);
	}

	return Entity::Render(gameSpeed, window);
}

void Cat::AddTarget(const int x, const int y)
{
	this->listPoint.push(std::pair<int, int>(x, y));
}

void Cat::MoveOnTarget(game_speed* gameSpeed)
{
	this->targetOne = this->listPoint.front();
	this->targetOneView->setPosition(this->targetOne.first, this->targetOne.second);
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
		this->pathLine.erase(this->pathLine.begin());
	}
}

void Cat::Collision(Entity* entity)
{
	switch (entity->getGroupID()) {
		case 2:
			this->collisionBuilding(entity);
			break;
		default:
			std::cout << entity->getGroupID() << std::endl;
			break;
	}
}


void Cat::collisionBuilding(Entity* entity)
{
	if (this->getGlobalBounds().intersects(entity->entrance->getGlobalBounds())) {
		this->stock += entity->getStock();
		this->stockText->setString(std::to_string(this->stock));
		entity->Collision(this);
	}

}


bool Cat::CheckCollision()
{
	for (auto& iterator : this->entityManager->getEntities()) {
		if (iterator.second->getId() != this->getId() && this->CaseX == iterator.second->CaseX && this->CaseY == iterator.second->CaseY)
		{
			this->Collision(iterator.second);
		}
	}
	return false;
}

bool Cat::CheckCollision(Entity* entity)
{
	return this->getGlobalBounds().intersects(entity->getGlobalBounds());
}
