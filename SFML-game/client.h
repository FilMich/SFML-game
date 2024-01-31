#pragma once
#include "SFML/Network.hpp"
#include <iostream>
#include "processor.h"
#include <thread>
class Client
{
public:
	Client(Data* data, Processor* processor);
	~Client();

	void connect();
	void send(const std::string& message);
	void receive();
	void startRecieve() {
		std::thread serverThread(&Client::receive, this);
		serverThread.detach(); // Detach the thread to allow it to run independently
	}
private:
	Processor* processor;
	sf::TcpSocket* socket;
	sf::SocketSelector* selector;
};