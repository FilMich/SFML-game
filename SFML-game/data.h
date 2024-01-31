#pragma once
#include <iostream>
#include <vector>
#include "player.h"
class Data
{
public:
	Data();
	~Data();

	void addPlayer(int ID, sf::Vector2f pos,sf::Color color);
	void updatePlayer(int ID, sf::Vector2f pos,sf::Color color);
	void updatePlayerColor(int ID,sf::Color color);
	void updatePlayerPos(int ID, sf::Vector2f pos);
	Player* findPlayerWithID(int ID);
	//bool existsPlayerWithID(int ID);
	std::vector<Player*>* getPlayers();

private:
	std::vector<Player*>* players;
};
