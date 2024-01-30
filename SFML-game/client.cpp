#include "client.h"

Client::Client()
{
    this->socket = new sf::TcpSocket;
}

Client::~Client()
{
}

void Client::connect()
{
    std::cout << "Connecting to the server...\n";
    if (socket->connect("192.168.154.187", 53000) != sf::Socket::Done) {
        std::cerr << "Failed to connect to the server" << std::endl;
    }
    else {
        std::cout << "Connected to the server\n";
    }

}

void Client::sendMessage(const std::string& message)
{
    sf::Packet packet;
    packet << message;
    if (socket->send(packet) != sf::Socket::Done) {
        std::cerr << "Failed to send message to the server" << std::endl;
    }
}

void Client::receiveMessage()
{
    if (selector->isReady(*socket)) {
        sf::Packet packet;
        if (socket->receive(packet) == sf::Socket::Done) {
            std::string receivedMessage;
            packet >> receivedMessage;
            std::cout << "Received message from the server: " << receivedMessage << std::endl;
        }
    }
}
