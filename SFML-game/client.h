#pragma once
#include "SFML/Network.hpp"
#include <iostream>
#include "processor.h"
class Client
{
public:
	Client(Data* data, Processor* processor);
	~Client();

	void connect();
	void send(const std::string& message);
	void receive();
private:
	Processor* processor;
	sf::TcpSocket* socket;
	sf::SocketSelector* selector;
};