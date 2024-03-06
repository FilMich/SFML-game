#pragma once
#include "SFML/Graphics.hpp"


class Bullet
{
public:
	Bullet(sf::Vector2f startPos, sf::Vector2f direction);
	~Bullet();
	void fly(float deltaTime);
	void draw(sf::RenderWindow* window);
	void collided() { this->flying = false; }
private:
	sf::CircleShape* shape;
	sf::Vector2f direction;
	float speed;
	bool flying;
};
