#pragma once

#include <SFML/Graphics.hpp>
#include "game_speed.h"

class tiny_state
{
public:

	virtual void Initialize(sf::RenderWindow* window)
	{
	}

	virtual void Update(game_speed* game_speed, sf::RenderWindow* window)
	{
	}

	virtual void Render(game_speed* game_speed, sf::RenderWindow* window)
	{
	}

	virtual void Destroy(sf::RenderWindow* window)
	{
	}
};

class game_state
{
public:
	game_state()
	{
		this->state = NULL;
	}

	void SetWindow(sf::RenderWindow* window)
	{
		this->window = window;
	}

	void SetGameSpeed(game_speed* gameSpeed)
	{
		this->gameSpeed = gameSpeed;
	}

	void SetState(tiny_state* state)
	{
		if (this->state != NULL)
		{
			this->state->Destroy(this->window);
		}
		this->state = state;
		if (this->state != NULL)
		{
			this->state->Initialize(this->window);
		}
	}

	void Update(float const dt)
	{
		if (this->state != NULL)
		{
			this->gameSpeed->setDeltaTime(dt);
			this->state->Update(this->gameSpeed, this->window);
		}
	}
	void Render(float const dt)
	{
		if (this->state != NULL)
		{
			this->state->Render(this->gameSpeed, this->window);
		}
	}

	~game_state()
	{
		if (this->state != NULL)
		{
			this->state->Destroy(this->window);
		}
	}
private:
	sf::RenderWindow* window;
	tiny_state* state;
	game_speed* gameSpeed;
	float deltaT;
};

extern game_state coreState;
extern bool quitGame;
