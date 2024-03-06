#include "bullet.h"

Bullet::Bullet(sf::Vector2f startPos, sf::Vector2f direction)
{
	this->flying = true;
	this->shape = new sf::CircleShape(5.f);
	this->shape->setPosition(startPos);
	this->shape->setFillColor(sf::Color::Black);
	this->speed = 10.0f;
	this->direction = direction;
}

void Bullet::fly(float deltaTime) //delta Time
{
	if (flying) {
		sf::Vector2f movement = direction * speed;
		shape->move(movement);
	}
}

void Bullet::draw(sf::RenderWindow* window)
{
	if (flying)
	{
		window->draw(*shape);
	}
}
