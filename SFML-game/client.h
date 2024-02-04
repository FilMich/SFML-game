#pragma once
#include "SFML/Network.hpp"
#include <iostream>
#include "processor.h"
#include <thread>
class Client
{
public:
	static Client& getInstance(Data* data, Processor* processor) {
		static Client instance(data, processor);
		return instance;
	}
	~Client();

	void connect();
	void send(const std::string& message);
	void receive();
	void startRecieve();
	void startRecieveLoop();
	
private:
	Client(Data* data, Processor* processor);

	std::thread receiveThread;
	Processor* processor;
	sf::TcpSocket* socket;
	sf::SocketSelector* selector;
};