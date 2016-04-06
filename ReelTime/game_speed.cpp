#pragma once

#include "game_speed.h"

game_speed::game_speed()
{
	this->gameSpeed = 1;
	this->gameSpeedMin = 0;
	this->gameSpeedMax = 5;
	this->gamePause = false;
}

void game_speed::Initialize(sf::RenderWindow* window)
{
	/*
	this->font = new sf::Font();
	this->font->loadFromFile("Graphics/font.ttf");
	
	this->counter = new sf::Text("0", *this->font, 200U);
	this->counter->setOrigin(this->counter->getGlobalBounds().width / 2, this->counter->getGlobalBounds().height / 2);
	this->counter->setPosition(this->counter->getGlobalBounds().width, this->counter->getGlobalBounds().height);

	this->speedText = new sf::Text("0", *this->font, 100);
	this->speedText->setOrigin(this->speedText->getGlobalBounds().width / 2, this->speedText->getGlobalBounds().height / 2);
	this->speedText->setPosition(window->getSize().x - this->speedText->getGlobalBounds().width, this->speedText->getGlobalBounds().height / 2);

	this->pauseText = new sf::Text("Game Pause", *this->font, 200);
	this->pauseText->setOrigin(this->pauseText->getGlobalBounds().width / 2, this->pauseText->getGlobalBounds().height / 2);
	this->pauseText->setPosition(window->getSize().x /2, window->getSize().y / 2);
	*/

	this->texture->create(this->gameSpeedMax*this->tileWidth, this->tileHeight);
	this->tileSetTexture->loadFromFile("Graphics/Tilesets/game_speed.png");

	this->ImgPauseActive.create(this->tileWidth, this->tileHeight);
	this->ImgPauseInactive.create(this->tileWidth, this->tileHeight);
	this->ImgPlayActive.create(this->tileWidth, this->tileHeight);
	this->ImgPlayInactive.create(this->tileWidth, this->tileHeight);

	this->ImgPauseInactive.copy(*this->tileSetTexture, 0, 0, sf::IntRect(0, 0, this->tileWidth, this->tileHeight), true);
	this->ImgPauseActive.copy(*this->tileSetTexture, 0, 0, sf::IntRect(0, 0, this->tileWidth*2, this->tileHeight), true);
	this->ImgPlayInactive.copy(*this->tileSetTexture, 0, 0, sf::IntRect(0, 0, this->tileWidth * 3, this->tileHeight), true);
	this->ImgPlayActive.copy(*this->tileSetTexture, 0, 0, sf::IntRect(0, 0, this->tileWidth * 4, this->tileHeight), true);
	
	this->generateSprite();
}

bool game_speed::Update(float const dt, sf::RenderWindow* window)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Subtract) && !this->subtractKey) {
		this->gameSpeed--;
		if (this->gameSpeed <= this->gameSpeedMin) {
			this->gameSpeed = this->gameSpeedMin;
			this->gamePause = true;
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Add) && !this->addKey) {
		this->gameSpeed++;
		this->gamePause = false;
		if (this->gameSpeed > this->gameSpeedMax) {
			this->gameSpeed = this->gameSpeedMax;
		}
	}

	this->generateSprite();

	this->subtractKey = sf::Keyboard::isKeyPressed(sf::Keyboard::Subtract);
	this->addKey = sf::Keyboard::isKeyPressed(sf::Keyboard::Add);

	return true;
}

void game_speed::Render(float const dt, sf::RenderWindow* window)
{
	/*
	if (this->gamePause) {
		window->draw(*this->pauseText);
	}
	else {
		this->speedText->setString(std::to_string(this->gameSpeed));
		window->draw(*this->speedText);
	}
	*/
}


void game_speed::Destroy(sf::RenderWindow* window)
{
	delete this->font;
	delete this->counter;
	delete this->speedText;
}

bool game_speed::Paused()
{
	return this->gamePause;
}

int game_speed::getGameSpeed()
{
	return this->gameSpeed;
}

void game_speed::generateSprite()
{
	if (this->gamePause) {
		this->texture->update(ImgPauseActive, this->tileWidth, this->tileHeight);
	}
	else {
		this->texture->update(ImgPauseInactive, this->tileWidth, this->tileHeight);
	}

	for (int i(0); i < this->gameSpeedMax; i++) {
		if (i <= this->gameSpeed) {
			this->texture->update(ImgPlayActive, this->tileWidth * i, this->tileHeight);
		}
		else {
			this->texture->update(ImgPlayInactive, this->tileWidth * i, this->tileHeight);
		}
	}
}