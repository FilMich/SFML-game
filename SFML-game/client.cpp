#include "client.h"

Client::Client(Data* data, Processor* processor) : processor(processor)
{
    this->socket = new sf::TcpSocket;
    this->selector = new sf::SocketSelector;
    //this->processor = processor;
}

Client::~Client()
{
}

void Client::connect()
{
    std::cout << "Connecting to the server...\n";
    if (socket->connect("192.168.0.239", 53000) != sf::Socket::Done) {
        std::cerr << "Failed to connect to the server" << std::endl;
    }
    else {
        std::cout << "Connected to the server\n";
        this->selector->add(*socket);

        startRecieve();
    }
    //receive();
}

void Client::send(const std::string& message)
{
    sf::Packet packet;
    packet << message;
    if (socket->send(packet) != sf::Socket::Done) {
        std::cerr << "Failed to send to the server" << std::endl;
    }
}

void Client::receive()
{
    if (selector->wait(sf::seconds(0.1)))
    {
        if (selector->isReady(*socket)) {
            sf::Packet packet;
            if (socket->receive(packet) == sf::Socket::Done) {
                std::string received = "";
                packet >> received;
                std::cout << "Received from the server: " << received << std::endl;
                processor->unpackData(received);
                packet.clear();
            }
        }
    }
}

void Client::startRecieve()
{
    receiveThread = std::thread(&Client::startRecieveLoop, this);
    receiveThread.detach();
}

void Client::startRecieveLoop()
{
    while (true)
    {
        receive();
    }
}