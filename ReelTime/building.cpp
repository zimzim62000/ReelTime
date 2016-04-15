#include "building.h"

Building::Building(EntityManager* entityManager, MapGame* mapGame, float x, float y) : Entity()
{
	this->name = "stock/stock_";
	this->setPosition(x, y);
	this->groupId = 2;
	this->entityManager = entityManager;
	this->mapGame = mapGame;

	//init building
	this->animationActive = 1;
	this->nbAnimation = 7;
	this->stock = 0;
	this->stockMax = 5;

	this->timer = 0;
	this->timerNextAnimated = 5;

	this->Load(this->name + std::to_string(this->animationActive) + ".png");

	this->font = new sf::Font();
	this->font->loadFromFile("Graphics/font.ttf");

	this->entrance = new sf::RectangleShape();
	this->entrance->setSize(sf::Vector2f(mapGame->tileWidth, mapGame->tileHeight));
	this->entrance->setFillColor(sf::Color::Blue);
	this->entrance->setPosition(x, y + this->getGlobalBounds().height);

	this->stockText = new sf::Text("000", *this->font, 24U);
	this->stockText->setPosition(x + this->getGlobalBounds().width - 20, y + this->getGlobalBounds().height / 8);
	this->stockText->setColor(sf::Color::Blue);
	this->stockText->setString(std::to_string(this->stock));
}

bool Building::Update(game_speed* gameSpeed, sf::RenderWindow* window)
{
	this->timer += gameSpeed->getGameSpeedDeltaTime();

	if(this->stock < this->stockMax){
		if (this->timer > this->timerNextAnimated) {

			if (this->timer > this->timerNextAnimated) {
				this->Load(this->name + std::to_string(this->animationActive) + ".png");
				this->timer = 0;
				this->animationActive++;
			}

			if (this->animationActive > this->nbAnimation) {
				this->animationActive = 1;
				this->stock++;
				this->stockText->setString(std::to_string(this->stock));
			}
		}
	}
	else {
		this->stockText->setColor(sf::Color::Red);
		this->stockText->setString("Full");
	}

	return true;
}

bool Building::Render(game_speed* gameSpeed, sf::RenderWindow* window)
{
	window->draw(*this->stockText);
	window->draw(*this->entrance);

	return true;
}

int Building::getStock() {
	return this->stock;
}

void Building::Collision(Entity* entity)
{
	switch (entity->getGroupID()) {
	case 1:
		if(this->stock > 0){
			if (this->stock == this->stockMax) {
				this->animationActive = 1;
			}
			this->stock = 0;
			this->stockText->setString(std::to_string(this->stock));
		}
		break;
	default:
		std::cout << "building collision : " << entity->getGroupID() << std::endl;
		break;
	}
}
