#pragma once
#include <iostream>
#include <vector>
#include "player.h"
class Data
{
public:
	Data();
	~Data();

	void addPlayer(sf::TcpSocket* newPlayer, int ID, sf::Color color);
	std::vector<Player*>* getPlayers();

private:
	std::vector<Player*>* players;
};
