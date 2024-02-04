#include "data.h"

Data::Data()
{
	this->players = new std::vector<Player*>();
	//this->players->push_back(new Player(1, { 0,0 }, sf::Color::Green));
}

Data::~Data()
{
}

void Data::addPlayer(int ID, sf::Vector2f pos, sf::Color color)
{
	if (findPlayerWithID(ID) == nullptr)
	{
		Player* player = new Player(ID, pos, color);
		this->players->push_back(player);
	}
	else
	{
		updatePlayer(ID, pos, color);
	}
}

void Data::updatePlayer(int ID, sf::Vector2f pos, sf::Color color)
{
	Player* player = findPlayerWithID(ID);
	if (player != nullptr)
	{
		player->setPos(pos);
		player->setColor(color);
	}
	else
	{
		addPlayer(ID, pos, color);
	}
	/*bool found = false;
	for (Player* p : *this->players) {
		if (p->getID() == ID)
		{
			p->setPos(pos);
			p->setColor(color);
			break;
			found == true;
		}
	}
	if (!found)
	{
		addPlayer(ID, pos, color);
	}*/
}

void Data::updatePlayerColor(int ID, sf::Color color)
{
	Player* player = findPlayerWithID(ID);
	player->setColor(color);
}

void Data::updatePlayerPos(int ID, sf::Vector2f pos)
{
	Player* player = findPlayerWithID(ID);
	player->setPos(pos);
}

void Data::setIsReadyToPlay(int ID)
{
	Player* player = findPlayerWithID(ID);
	player->setReadyToPlay();
}

void Data::setIsNotReadyToPlay(int ID)
{
	Player* player = findPlayerWithID(ID);
	player->setNotReadyToPlay();
}

bool Data::getIsReadyToPlay(int ID)
{
	Player* player = findPlayerWithID(ID);
	return player->isReadyToPlay();
}

Player* Data::findPlayerWithID(int ID)
{
	for (Player* player : *players) {
		if (player->getID() == ID)
		{
			return player;
		}
	}
	return nullptr;
}

std::vector<Player*>* Data::getPlayers()
{
	return this->players;
}
