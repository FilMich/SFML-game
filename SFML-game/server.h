#pragma once
#include "SFML/Network.hpp"
#include <vector>
#include "player.h"
#include "data.h"
#include <iostream>

class Server
{
public:
	Server(Data* data);
	~Server();
	void run();
	void handleNewConnection();
	void handleClientActivity();
	int assignUniqueId();
	sf::Color assignUniqueColor();
	void sendPlayerInfoToAll(sf::TcpSocket* newClient, std::vector<sf::TcpSocket*>* clients);
	void broadcast(std::vector<Player*>* players, std::vector<sf::TcpSocket*>* clients);
	void processPacket(sf::TcpSocket* client,sf::Packet);
private:
	sf::TcpListener* listener;
	sf::SocketSelector* selector;
	std::vector<Player*>* players;
	std::vector<sf::TcpSocket*>* clients;
};