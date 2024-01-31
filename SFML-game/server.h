#pragma once
#include "SFML/Network.hpp"
#include <vector>
#include "player.h"
#include "data.h"
#include <iostream>
#include "processor.h"
#include <thread>

class Server
{
public:
	Server(Data* data, Processor* processor);
	~Server();
	void run();
	void handleNewConnection();
	void handleClientActivity();
	int assignUniqueId();
	sf::Color assignUniqueColor();
	void sendPlayerInfoToAll(sf::TcpSocket* newClient, std::vector<sf::TcpSocket*>* clients);
	void broadcastPlayers(std::vector<Player*>* players, std::vector<sf::TcpSocket*>* clients);
	void broadcastMessage(std::vector<Player*>* players, std::vector<sf::TcpSocket*>* clients, std::string message);
	//void processPacket(sf::TcpSocket* client,sf::Packet);
	void start() {
		std::thread serverThread(&Server::run, this);
		serverThread.detach(); // Detach the thread to allow it to run independently
	}
private:
	Processor* processor;
	Data* data;
	sf::TcpListener* listener;
	sf::SocketSelector* selector;
	//std::vector<Player*>* players;
	std::vector<sf::TcpSocket*>* clients;
	float x = 100.00;
};