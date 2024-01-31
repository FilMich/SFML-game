#include "player.h"

Player::Player(int ID, sf::Vector2f position, sf::Color color)
{
	this->position = sf::Vector2f(100, 100);
	this->shape = new sf::CircleShape(20);
	this->shape->setFillColor(color);
	this->shape->setPosition(this->position);
	this->ID = ID;
	this->color = color;
}

Player::~Player()
{
	//delete this->newPlayer;
}
