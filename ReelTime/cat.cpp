#include "cat.h"
#include <iostream>
#include "utility.h"

Cat::Cat(EntityManager* entityManager, MapGame* mapGame, float x, float y, const int speed) : Entity(speed)
{
	this->Load("doudou.png");
	this->setPosition(x, y);
	this->groupId = 1;
	this->entityManager = entityManager;
	this->mapGame = mapGame;
	this->pathFinding = new PathFinding();
	this->todoList = new TodoList();
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

	this->taskText = new sf::Text("---------", *this->font, 28U);
	this->taskText->setPosition(sf::Vector2f(this->getPosition().x+this->stockText->getGlobalBounds().width, this->getPosition().y));
	this->taskText->setColor(sf::Color::Green);

	this->targetView = new sf::CircleShape();
	this->targetView->setFillColor(sf::Color::Blue);
	this->targetView->setRadius(this->mapGame->tileWidth / 2);

	this->targetOneView = new sf::CircleShape();
	this->targetOneView->setFillColor(sf::Color::Magenta);
	this->targetOneView->setRadius(this->mapGame->tileWidth / 4);
	this->targetOneView->setOrigin(-this->mapGame->tileWidth / 4, -this->mapGame->tileHeight / 4);

	this->taskCount = 21;
	this->taskCountMax = 20;

}


bool Cat::Update(game_speed* gameSpeed, sf::RenderWindow* window)
{
	this->taskCount += gameSpeed->getGameSpeedDeltaTime();

	if (this->taskCount > this->taskCountMax) {
		this->taskCount = 0;
		if(this->todoList->countTodoList() == 0){
			this->createTask();
		}
	}

	if(this->listPoint.size() != 0){
		this->MoveOnTarget(gameSpeed);
		Entity::Update(gameSpeed, window);
		this->stockText->setPosition(this->getPosition());
		this->taskText->setPosition(sf::Vector2f(this->getPosition().x + this->stockText->getGlobalBounds().width, this->getPosition().y));
	}

	if (this->listPoint.size() == 0) {
		//std::cout << "end path" << std::endl;
		if (this->todoList->countTodoList() != 0) {
			this->todoList->deleteFirstTask();
		}
	}

	this->CheckCollision();

	return true;
}

bool Cat::Render(game_speed* gameSpeed, sf::RenderWindow* window)
{
	//sf::View defaultView = window->getDefaultView();
	//window->setView(defaultView);
	
	if (this->target.first == this->target.second && this->target.second == -1){

	
	}
	else {
		window->draw(*this->targetView);
		window->draw(*this->targetOneView);
		if (this->pathLine.size()  > 0) {
			window->draw(&this->pathLine.at(0), this->pathLine.size(), sf::LinesStrip);
		}
	}

	window->draw(*this->stockText);
	window->draw(*this->taskText);

	return Entity::Render(gameSpeed, window);
}

void Cat::AddTarget(const int x, const int y)
{
	this->listPoint.push(std::pair<int, int>(x, y));
}

void Cat::MoveOnTarget(game_speed* gameSpeed)
{
	if (this->listPoint.size() != 0) {
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


void Cat::createTask()
{
	std::cout << "New Task ! " << std::endl;

	int choice = utility::randInt(10, false);
	switch (choice)
	{
	case 1:
	case 2:
	case 3:
	case 4:
	case 5:
		this->taskGoToTarget();
		break;
	default:
		this->target.first = -1;
		this->target.second = -1;
		this->targetOne.first = -1;
		this->targetOne.second = -1;
		this->todoList->addTask(new Task(1, "Attend"));
		break;
	}
	this->taskText->setString(this->todoList->getFisrtTask()->name);
	
}

void Cat::taskGoToTarget()
{
	bool find = false;
	float x, y;
	int xx, yy;
	this->pathLine.empty();
	Entity* house = this->entityManager->Get("building");
	while (find == false) {
		if (false){//house->GetFull()) {
			this->target.first = house->getPosition().x / this->mapGame->tileWidth;
			this->target.second = house->getPosition().y / this->mapGame->tileHeight;
			find = true;
		}else{
			this->target = this->mapGame->getPositionAvailable();
			x = this->target.first * this->mapGame->tileWidth;
			y = this->target.second * this->mapGame->tileHeight;
			if (x != this->getPosition().x && y != this->getPosition().y) {
				this->targetView->setPosition(x, y);
				find = true;
			}
		}
	}

	delete this->pathFinding;
	this->pathFinding = new PathFinding();
	//this->pathFinding->resetPath();
	std::cout << "target x : " << this->target.first << " target y : " << this->target.second << std::endl;
	std::cout << "position x : " << int(this->getPosition().x / this->mapGame->tileWidth) << " position y : " << int(this->getPosition().y / this->mapGame->tileHeight) << std::endl;
	this->pathFinding->findRoad(this->mapGame, int(this->getPosition().x / this->mapGame->tileWidth), int(this->getPosition().y / this->mapGame->tileHeight), this->target.first, this->target.second);
	std::cout << "chemin size : " <<  std::endl;
	while (this->pathFinding->chemin.size() > 0) {
		point pt = this->pathFinding->chemin.front();
		xx = pt.x*this->mapGame->tileWidth;
		yy = pt.y*this->mapGame->tileHeight;
		this->pathLine.push_back(sf::Vertex(sf::Vector2f(xx + this->mapGame->tileWidth / 2, yy + this->mapGame->tileHeight / 2), sf::Color::Red));
		this->AddTarget(xx, yy);
		this->pathFinding->chemin.pop_front();
	}
	this->todoList->addTask(new Task(1, "Se prom�ne", sf::Vector2f(x, y)));
}