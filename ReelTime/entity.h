#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include <queue>
#include "game_speed.h"
#include "utility.h"


class Entity : public sf::Sprite
{
public:
	sf::Vector2f velocity;

	Entity();

	Entity(const int speed);

	void Load(std::string filename);

	virtual bool Update(game_speed* gameSpeed, sf::RenderWindow* window);

	bool CheckCollision(Entity* entity);

	virtual void Collision(Entity* entity);

	int GroupID();

	int Active();

	void Destroy();

	~Entity();

	bool getBusy() const;

	bool getOnMovement();
	void setName(std::string name);
	std::string getName() const;
	void setId(const int id);
	int getId() const;
	void setOnScene(const bool enable);
	bool getOnScene() const;
	std::pair<int, int> getTarget();

protected:
	void AnimateMe(game_speed* gameSpeed);
	void SetNewAnimation(std::string nameAnimation);
	void SetNewRightAnimation(std::string nameAnimation);
	void SetNewLeftAnimation(std::string nameAnimation);

	int active, groupId, id, speed;
	bool busy, onMove, IsAnimate, IsONScene, canMove;
	std::string name;

	std::pair<int, int> target;

	float animateMax;
	/* Animated none */
	float animateCount;
	int animateKey;
	std::vector<std::string> animated;
	/* Animated Right */
	float animateRightCount;
	int animateRightKey;
	std::vector<std::string> animatedRight;
	/* Animated Left */
	float animateLeftCount;
	int animateLeftKey;
	std::vector<std::string> animatedLeft;

	std::queue < std::pair<int, int>> listPoint;

private:
	sf::Texture* texture;
};
