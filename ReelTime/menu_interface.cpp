#include "menu_interface.h"

MenuInterface::MenuInterface()
{
	this->texture = new sf::Texture();
	this->texture->loadFromFile("Graphics/Images/interface.png");
	this->setTexture(*this->texture);
}