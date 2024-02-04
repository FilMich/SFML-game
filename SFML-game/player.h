#pragma once
#include "SFML/Network.hpp"
#include "SFML/Graphics.hpp"
class Player
{
public:
	//Player() {};
	Player(int ID, sf::Vector2f position, sf::Color color);
	~Player();
	void setPos(sf::Vector2f position) { this->position = position; this->shape->setPosition(position); }
	sf::CircleShape* getShape() { return this->shape; }
	int getID() { return this->ID; }
	sf::Color getColor() { return this->color; }
	sf::Vector2f getPos() { return this->position; }
	void setColor(sf::Color color) { this->color = color; }
	bool isReadyToPlay() { return readyToPlay; }
	void setReadyToPlay() { this->readyToPlay = true; }
	void setNotReadyToPlay() { this->readyToPlay = false; }
private:
	
	int ID;
	sf::Color color;
	sf::CircleShape* shape;
	sf::Vector2f position = {0,0};
	bool readyToPlay = false;
	//int HP; 
	//bool alive; 
	//bool dmgTaken; 
	//int kills; 

};