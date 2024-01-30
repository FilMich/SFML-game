#pragma once
#include "SFML/Network.hpp"
#include <iostream>
class Client
{
public:
	Client();
	~Client();

	void connect();
	void sendMessage(const std::string& message);
	void receiveMessage();
private:
	sf::TcpSocket* socket;
	sf::SocketSelector* selector;
};