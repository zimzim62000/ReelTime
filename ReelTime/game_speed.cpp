#pragma once

#include "game_speed.h"
#include <iostream>
#include "config.h"

game_speed::game_speed()
{
	this->gameSpeed = 1;
	this->gameSpeedMin = 0;
	this->gameSpeedMax = 5;
	this->gamePause = this->gameTick = false;
	this->tileWidth = 64;
	this->tileHeight = 64;

	this->deltaTime = this->deltaTimeCounter = this->deltaTimeSecond = this->deltaTimeSpeed = 0;

	this->texture = new sf::Texture();
	this->tileSetTexture = new sf::Image();

	this->font = new sf::Font();
	this->font->loadFromFile("Graphics/font.ttf");
}

void game_speed::setDeltaTime(float const dt)
{
	this->deltaTime = dt;
}

void game_speed::Initialize(sf::RenderWindow* window)
{
	this->texture->create(384, this->tileHeight);
	this->tileSetTexture->loadFromFile("Graphics/Tilesets/game_speed.png");

	this->ImgPauseActive.create(this->tileWidth, this->tileHeight);
	this->ImgPauseInactive.create(this->tileWidth, this->tileHeight);
	this->ImgPlayActive.create(this->tileWidth, this->tileHeight);
	this->ImgPlayInactive.create(this->tileWidth, this->tileHeight);

	this->ImgPauseInactive.copy(*this->tileSetTexture, 0, 0, sf::IntRect(0, 0, this->tileWidth, this->tileHeight), true);
	this->ImgPauseActive.copy(*this->tileSetTexture, 0, 0, sf::IntRect(this->tileWidth , 0, this->tileWidth, this->tileHeight), true);
	this->ImgPlayInactive.copy(*this->tileSetTexture, 0, 0, sf::IntRect(this->tileWidth * 2, 0, this->tileWidth, this->tileHeight), true);
	this->ImgPlayActive.copy(*this->tileSetTexture, 0, 0, sf::IntRect(this->tileWidth * 3, 0, this->tileWidth, this->tileHeight), true);
	
	this->speedText = new sf::Text("1000,000000000", *this->font, 28U);
	//this->speedText->setOrigin(this->speedText->getGlobalBounds().width / 2, this->speedText->getGlobalBounds().height / 2);
	this->speedText->setPosition(10, -this->speedText->getGlobalBounds().height / 2);
	this->speedText->setColor(sf::Color::Yellow);

	this->counterSecondText = new sf::Text("1000,00000000", *this->font, 28U);
	//this->counterSecondText->setOrigin(this->counterSecondText->getGlobalBounds().width / 2, this->counterSecondText->getGlobalBounds().height / 2);
	this->counterSecondText->setPosition(10, this->counterSecondText->getGlobalBounds().height / 2);
	this->counterSecondText->setColor(sf::Color::Green);

	this->fpsText = new sf::Text("1000", *this->font, 28U);
	//this->fpsText->setOrigin(this->fpsText->getGlobalBounds().width / 2, this->fpsText->getGlobalBounds().height / 2);
	this->fpsText->setPosition(10 , this->fpsText->getGlobalBounds().height / 2 + this->counterSecondText->getGlobalBounds().height);
	this->fpsText->setColor(sf::Color::Red);

	this->generateSprite();

	this->setPosition(window->getSize().x - 384, 0);
}

bool game_speed::Update(sf::RenderWindow* window)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) && !this->echapKey) {
		if (this->gamePause == false) {
			this->gameSpeed = 0;
			this->gamePause = true;
			this->generateSprite();
		}
		else {
			this->gameSpeed = 1;
			this->gamePause = false;
			this->generateSprite();
		}
	}else{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Subtract) && !this->subtractKey) {
			this->gameSpeed--;
			if (this->gameSpeed <= this->gameSpeedMin) {
				this->gameSpeed = this->gameSpeedMin;
				this->gamePause = true;
			}
			this->generateSprite();
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Add) && !this->addKey) {
			this->gameSpeed++;
			this->gamePause = false;
			if (this->gameSpeed > this->gameSpeedMax) {
				this->gameSpeed = this->gameSpeedMax;
			}
			this->generateSprite();
		}
	}

	if (this->gamePause == false) {
		this->gameTick = false;
		this->deltaTime = this->deltaTime;
		this->deltaTimeCounter += this->deltaTime;
		this->deltaTimeSecond += this->deltaTime;
		this->deltaTimeSpeed += this->getGameSpeedDeltaTime();
		if (this->deltaTimeSecond > 1) {
			this->gameTick = true;
			this->deltaTimeSecond = 0;
		}
		this->speedText->setString(std::to_string(this->deltaTimeSpeed));
		this->counterSecondText->setString(std::to_string(this->deltaTimeCounter));
		this->fpsText->setString(std::to_string(int(1/ this->deltaTime)));
	}

	this->echapKey = sf::Keyboard::isKeyPressed(sf::Keyboard::Escape);
	this->subtractKey = sf::Keyboard::isKeyPressed(sf::Keyboard::Subtract);
	this->addKey = sf::Keyboard::isKeyPressed(sf::Keyboard::Add);

	return true;
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

float game_speed::getGameSpeedDeltaTime()
{
	float tmp = (this->gameSpeed * this->deltaTime);
	return tmp;
}

float game_speed::getGameSpeedDeltaTimeWithFps()
{
	float tmp = (this->gameSpeed * this->deltaTime);
	return tmp;
}

float game_speed::getDeltaTime()
{
	return this->deltaTime;
}

bool game_speed::getGameTick()
{
	return this->gameTick;
}

void game_speed::generateSprite()
{
	if (this->gamePause) {
		this->texture->update(this->ImgPauseActive, 0, 0);
	}
	else {
		this->texture->update(this->ImgPauseInactive, 0, 0);
	}

	for (int i(1); i <= this->gameSpeedMax; i++) {
		if (i <= this->gameSpeed) {
			this->texture->update(this->ImgPlayActive, this->tileWidth * i , 0);
		}
		else {
			this->texture->update(this->ImgPlayInactive, this->tileWidth * i , 0);
		}
	}
	this->setTexture(*this->texture);
}