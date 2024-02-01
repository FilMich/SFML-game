#include "player.h"

Player::Player(int ID, sf::Vector2f position, sf::Color color)
{
	this->position = position;
	this->shape = new sf::CircleShape(20);
	this->shape->setFillColor(color);
	this->shape->setPosition(this->position);
	this->ID = ID;
	this->color = color;
	readyToPlay = false;
}

Player::~Player()
{
	//delete this->newPlayer;
}
