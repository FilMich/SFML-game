#pragma once
#include <iostream>
#include <vector>
#include "player.h"
class Data
{
public:

	static Data& getInstance() {
		static Data instance;
		return instance;
	}

	//Data();
	~Data();

	void addPlayer(int ID, sf::Vector2f pos,sf::Color color);
	void updatePlayer(int ID, sf::Vector2f pos,sf::Color color);
	void updatePlayerColor(int ID,sf::Color color);
	void updatePlayerPos(int ID, sf::Vector2f pos);
	void setMyID(int myID) { this->myID = myID; }
	int getMyID() { return this->myID; }
	void setIsClient() { isClient = true; }
	void setIsNotClient() { isClient = false; }
	void setIsReadyToPlay(int ID);
	void setIsNotReadyToPlay(int ID);
	bool getIsReadyToPlay(int ID);
	bool amIClient() { return this->isClient; }
	Player* findPlayerWithID(int ID);
	bool arePlayersReady();
	//bool existsPlayerWithID(int ID);
	std::vector<Player*>* getPlayers();

private:
	Data();
	// MOZNO musim pridat mutex a zamknut data ktore idem menit/gettovat
	std::vector<Player*>* players;
	int myID;
	bool isClient;
};
