#include "entity.h"

Entity::Entity(const int speed)
{
	this->id = -1;
	this->texture = new sf::Texture();
	this->active = 1;
	this->groupId = 0;
	this->speed = speed;
	this->IsAnimate = false;
	this->IsONScene = false;
	this->canMove = true;
	this->busy = false;
	this->full = false;

	this->CaseBase = 640;
}

Entity::Entity()
{
	this->id = -1;
	this->texture = new sf::Texture();
	this->active = 1;
	this->groupId = 0;
	this->speed = 1;
	this->IsAnimate = false;
	this->IsONScene = false;
	this->canMove = true;
	this->busy = false;

	this->CaseBase = 640;
}

int Entity::getStock()
{
	return 0;
}

void Entity::setOnScene(const bool enable)
{
	this->IsONScene = enable;
}

bool Entity::getOnScene() const
{
	return this->IsONScene;
}

void Entity::setName(const std::string name)
{
	this->name = name;
}

std::string Entity::getName() const
{
	return this->name;
}

void Entity::AnimateMe(game_speed* gameSpeed)
{
	if(this->IsAnimate){
		if (this->velocity.x > 0 && this->velocity.y == 0) {
			this->animateRightCount += gameSpeed->getDeltaTime();
			if (this->animateRightCount >= this->animateMax) {
				this->animateRightCount = 0;
				this->animateRightKey++;
				if (this->animateRightKey >= this->animatedRight.size()) {
					this->animateRightKey = 0;
				}
				this->Load(this->animatedRight.at(this->animateRightKey));
			}
		}else if (this->velocity.x < 0 && this->velocity.y == 0) {
			this->animateLeftCount += gameSpeed->getDeltaTime();
			if (this->animateLeftCount >= this->animateMax) {
				this->animateLeftCount = 0;
				this->animateLeftKey++;
				if (this->animateLeftKey >= this->animatedLeft.size()) {
					this->animateLeftKey = 0;
				}
				this->Load(this->animatedLeft.at(this->animateLeftKey));
			}
		}else {
			this->animateCount += gameSpeed->getDeltaTime();
			if (this->animateCount >= this->animateMax) {
				this->animateCount = 0;
				this->animateKey++;
				if (this->animateKey >= this->animated.size()) {
					this->animateKey = 0;
				}
				this->Load(this->animated.at(this->animateKey));
			}
		}
	}
}

void Entity::SetNewAnimation(std::string nameAnimation)
{
	this->animated.push_back(nameAnimation);
}

void Entity::SetNewRightAnimation(std::string nameAnimation)
{
	this->animatedRight.push_back(nameAnimation);
}

void Entity::SetNewLeftAnimation(std::string nameAnimation)
{
	this->animatedLeft.push_back(nameAnimation);
}

bool Entity::getBusy() const
{
	return this->busy;
}

void Entity::Load(std::string filename)
{
	this->texture->loadFromFile("Graphics/Images/" + filename);
	this->setTexture(*this->texture);
}

bool Entity::Update(game_speed* gameSpeed, sf::RenderWindow* window)
{
	this->move(this->velocity * ( this->speed * gameSpeed->getGameSpeedDeltaTime()));
	this->AnimateMe(gameSpeed);
	
	this->CaseX = this->getPosition().x / this->CaseBase;
	this->CaseY = this->getPosition().y / this->CaseBase;

	return true;
}

bool Entity::Render(game_speed* gameSpeed, sf::RenderWindow* window)
{
	return true;
}

void Entity::Collision(Entity* entity)
{
}

bool Entity::CheckCollision()
{
	return false;
}

bool Entity::CheckCollision(Entity* entity)
{
	return false;
}

int Entity::getGroupID()
{
	return this->groupId;
}

int Entity::Active()
{
	return this->active;
}

void Entity::Destroy()
{
	this->active = 0;
}

Entity::~Entity()
{
	delete this->texture;
	this->listPoint.empty();
}

std::pair<int, int> Entity::getTarget()
{
	return this->target;
}

std::pair<int, int> Entity::getTargetOne()
{
	return this->targetOne;
}


bool Entity::getOnMovement() {
	return this->onMove;
}

bool Entity::GetFull() {
	return this->full;
}

void Entity::setId(const int id)
{
	this->id = id;
}

int Entity::getId() const
{
	return this->id;
}