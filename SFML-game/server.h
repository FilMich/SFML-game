#pragma once
#include "SFML/Network.hpp"
#include <vector>
#include "player.h"
#include "data.h"
#include <iostream>
#include "processor.h"
#include <thread>
#include <fstream>

class Server
{
public:
	static Server& getInstance(Data* data, Processor* processor) {
		static Server instance(data, processor);
		return instance;
	}

	~Server();
	void run();

	void createFileWithData();

	void handleNewConnection();
	void handleClientActivity();
	int assignUniqueId(sf::TcpSocket* client);
	sf::Vector2f assignUniquePos();
	sf::Color assignUniqueColor();
	void sendPlayerInfoToAll(sf::TcpSocket* newClient, std::vector<sf::TcpSocket*>* clients);
	void broadcastPlayers(std::vector<Player*>* players);
	void broadcastMessage(std::vector<Player*>* players, std::string message);
	//void processPacket(sf::TcpSocket* client,sf::Packet);
	void start() {
		std::thread serverThread(&Server::run, this);
		serverThread.detach(); // Detach the thread to allow it to run independently
	}
private:
	Server(Data* data, Processor* processor);
	Processor* processor;
	Data* data;
	sf::TcpListener* listener;
	sf::SocketSelector* selector;
	//std::vector<Player*>* players;
	std::vector<sf::TcpSocket*>* clients;
	float x = 100.00;
};