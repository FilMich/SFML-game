#pragma once
#include "SFML/Network.hpp"
#include "SFML/Graphics.hpp"
#include "bullet.h"
class Player
{
public:
	//Player() {};
	Player(int ID, sf::Vector2f position, sf::Color color);
	~Player();
	void setPos(sf::Vector2f position) { this->position = position; this->shape->setPosition(position); }
	sf::CircleShape* getShape() { return this->shape; }
	int getID() { return this->ID; }
	int getMagazine() { return this->magazine; }
	sf::Color getColor() { return this->color; }
	sf::Vector2f getPos() { return this->position; }
	void setColor(sf::Color color) { this->color = color; }
	bool isReadyToPlay() { return readyToPlay; }
	void setReadyToPlay() { this->readyToPlay = true; }
	void setNotReadyToPlay() { this->readyToPlay = false; }
	std::vector<Bullet*> getBullets() { return this->bullets; }
	void shootBullet(sf::Vector2f direction);
	void bulletFly();
	void addToMagazine();
	bool isFull();
	void resizeMagazine(int i) { this->maxMagazineSize += i; }
private:
	
	int ID;
	sf::Color color;
	sf::CircleShape* shape;
	sf::Vector2f position = {0,0};
	bool readyToPlay = false;
	std::vector<Bullet*> bullets;
	int magazine = 5;
	int maxMagazineSize = 5;
	int HP; 
	bool alive; 
	//bool dmgTaken; 
	//int kills;

};