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
	this->alive = true;
	this->HP = 100;
}

Player::~Player()
{
	//delete this->newPlayer;
}

void Player::shootBullet(sf::Vector2f direction)
{
	if (magazine != 0)
	{
		bullets.push_back(new Bullet(this->position, direction));
		--magazine;
	}
}

void Player::bulletFly()
{
	for (auto b : bullets) {
		b->fly(0);
	}
}

void Player::addToMagazine()
{
	if (!isFull())
	{
		++magazine;
	}
}

bool Player::isFull()
{
	return magazine == maxMagazineSize;
}
