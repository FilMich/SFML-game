#include "server.h"

Server::Server(Data* data, Processor* processor) :data(data), processor(processor)
{
    //data = data;
    //processor = processor;
    this->listener = new sf::TcpListener;
    this->selector = new sf::SocketSelector;
    //this->players = data->getPlayers();
    this->clients = new std::vector<sf::TcpSocket*>();
}

Server::~Server()
{
    delete this->listener;
    delete this->selector;
    delete this->clients;
    //delete this->players;
}

/*void Server::run()
{
    if (this->listener->listen(53000) != sf::Socket::Done) {
        std::cerr << "Error: Failed to bind the listener to port " << 53000 << std::endl;
    }
    std::cout << "listening \n";
    this->selector->add(*listener);
    while (true) {
        std::cout << "selector added\n";
        if (this->selector->wait()) {
            std::cout << "waiting \n";
            if (this->selector->isReady(*this->listener)) {
                std::cout << "is ready \n";
                handleNewConnection();
            }
            else {
                handleClientActivity();
            }
        }
    }
}*/

void Server::run()
{
    //std::cout << this->data->getPlayers()->size();
    sf::IpAddress ip = sf::IpAddress::getLocalAddress();
    std::cout << ip;
    this->data->addPlayer(0, {100,100}, sf::Color::Red);
    this->data->setMyID(0);
    if (this->listener->listen(53000) != sf::Socket::Done) {
        std::cerr << "Error: Failed to bind the listener to port " << 53000 << std::endl;
        return;
    }
    std::cout << "Listening on port " << 53000 << std::endl;
    this->selector->add(*listener);

    while (true) {
        std::cout << "Waiting for activity...\n";
        if (this->selector->wait()) {
            if (this->selector->isReady(*this->listener)) {
                std::cout << "New connection detected.\n";
                handleNewConnection();
            }
            else {
                std::cout << "Client activity detected.\n";
                handleClientActivity();
            }
        }
    }
}


void Server::handleNewConnection()
{
    //this->data->addPlayer(11, { 300,300 }, sf::Color::Red);
    std::cout << "handle \n";
    sf::TcpSocket* newClient = new sf::TcpSocket;
    newClient->setBlocking(false);
    if (this->listener->accept(*newClient) == sf::Socket::Done) {
        std::cout << "new player";
        int newClientId = assignUniqueId(newClient);
        sf::Color newClientColor = assignUniqueColor();
        sf::Vector2f pos = assignUniquePos();
        this->data->addPlayer(newClientId, pos, newClientColor);
        //this->players->push_back(new Player(newClientId, {100,100 }, newClientColor));
        this->selector->add(*newClient);
        this->clients->push_back(newClient);

        /*sf::Packet packetttt;
        std::string s = "sdfghj";
        packetttt << s;
        newClient->send(packetttt);*/

        broadcastPlayers(this->data->getPlayers(), this->clients);

        

        //sendPlayerInfoToAll(newClient, this->clients);
        
    }
    else
    {
        delete newClient;
    }
}

void Server::handleClientActivity()
{
    for (sf::TcpSocket* client : *this->clients) {
        if (this->selector->isReady(*client))
        {
            sf::Packet packet;
            if (client->receive(packet) == sf::Socket::Done)
            {
                std::string message;
                packet >> message;
                processor->unpackData(message);
                broadcastMessage(this->data->getPlayers(), this->clients, message);
                //processPacket(client, packet);
            }
        }
    }
}

int Server::assignUniqueId(sf::TcpSocket* client)
{
    int id = static_cast<int>(this->clients->size()) + 1;
    sf::Packet packet;
    packet << ("yourID," + std::to_string(id));
    client->send(packet);
    return id;
}

sf::Vector2f Server::assignUniquePos()
{
    x = x + 100.00;
    return sf::Vector2f(x + 100.00, 100.00);
    std::cout << x <<std::endl;
}

sf::Color Server::assignUniqueColor()
{
    int i = 0;
    switch (i)
    {
    case 0:
        return sf::Color().Blue;
        i++;
        break;
    case 1:
        i++;
        return sf::Color().Green;
        break;
    case 2:
        i++;
        return sf::Color().Magenta;
        break;
    case 3:
        i++;
        return sf::Color().Red;
        break;
    case 4:
        i++;
        return sf::Color().Yellow;
        break;
    default:
        return sf::Color().Black;
        i = 0;
    }
}

void Server::sendPlayerInfoToAll(sf::TcpSocket* newClient, std::vector<sf::TcpSocket*>* clients)
{
    for (sf::TcpSocket* client : *clients) {
            sf::Packet packet;
            packet << ("addNewPlayer");
            client->send(packet);
    }
}

void Server::broadcastPlayers(std::vector<Player*>* players, std::vector<sf::TcpSocket*>* clients)
{

    for (sf::TcpSocket* client : *clients) {
        sf::Packet packet;
        for (Player* player : *players) {
            std::string s = processor->packData("add", player->getID(), player->getPos(), player->getColor());
            packet << (s);
            client->send(packet);
            packet.clear();
        }
    }

    /*for (sf::TcpSocket* client : *clients) {
        for (Player* player : *players) {
            sf::Packet packet;
            sf::Color color = player->getColor();
            std::string sColor = "";

            if (color == sf::Color().Blue)
            {
                sColor = "Blue";
            }
            else if (color == sf::Color().Green)
            {
                sColor = "Green";
            }
            else if (color == sf::Color().Magenta)
            {
                sColor = "Magenta";
            }
            else if (color == sf::Color().Red)
            {
                sColor = "Red";
            }
            else if (color == sf::Color().Black)
            {
                sColor = "Black";
            }
            else if (color == sf::Color().Yellow)
            {
                sColor = "Yellow";
            }

            packet << ("addNewPlayer," + std::to_string(player->getPos().x) + "," + std::to_string(player->getPos().y) + "," + sColor);
            client->send(packet);
        }
        
    }*/
}

void Server::broadcastMessage(std::vector<Player*>* players, std::vector<sf::TcpSocket*>* clients, std::string message)
{
    sf::Packet packet;
    for (sf::TcpSocket* client : *clients) {
        for (Player* player : *players) {
            packet << message;
            client->send(packet);
        }
    }
}

//void Server::processPacket(sf::TcpSocket* client,sf::Packet packet)
//{
//
//    std::string s;
//    packet >> s;
//    if (s == "addNewPlayer")
//    {
//        players->push_back(new Player({100,100}, 1, sf::Color().Yellow));
//    }
//}
