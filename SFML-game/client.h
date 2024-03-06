#pragma once
#include "SFML/Network.hpp"
#include <iostream>
#include "processor.h"
#include <thread>
class Client
{
public:
	static Client& getInstance() {
		static Client instance;
		return instance;
	}
	~Client();

	void connect();
	void send(const std::string& message);
	void receive();
	void startRecieve();
	void startRecieveLoop();
	
private:
	Client();

	std::thread receiveThread;
	sf::TcpSocket* socket;
	sf::SocketSelector* selector;
};