#include "data.h"

Data::Data()
{
	this->players = new std::vector<Player*>();
}

Data::~Data()
{
}

void Data::addPlayer(sf::TcpSocket* newPlayer, int ID, sf::Color color)
{
	players->push_back(new Player(newPlayer, ID, color));
}

std::vector<Player*>* Data::getPlayers()
{
	return this->players;
}
