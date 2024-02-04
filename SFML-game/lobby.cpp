#include "lobby.h"

Lobby::Lobby(sf::RenderWindow* window, Data* data, Processor* processor) :data(data), processor(processor)
{
    //this->players = data->getPlayers();
    this->window = window;
    this->readyRect = new sf::RectangleShape();
    this->playerReady = new sf::RectangleShape();
    this->font = new sf::Font();
    this->image = new sf::Texture();
    this->bg = new sf::Sprite();

    //sf::TcpSocket* client = new sf::TcpSocket;
    //players->push_back(new Player(client, 1, sf::Color().Green));
    ////sf::TcpSocket* client = new sf::TcpSocket;
    //players->push_back(new Player(client, 2, sf::Color().Yellow));
    ////sf::TcpSocket* client = new sf::TcpSocket;
    //players->push_back(new Player(client, 3, sf::Color().Blue));
    ////sf::TcpSocket* client = new sf::TcpSocket;
    //players->push_back(new Player(client, 4, sf::Color().Red));
    //float i = 100;
    //float j = 100;
    //for (Player* p : *this->players) { 
    //    i += 100;
    //    p->setPos({ i,j }); 
    //}

    set_values();
}

Lobby::~Lobby()
{
    delete window;
    delete readyRect;
    delete font;
    delete image;
    delete bg;
}

void Lobby::draw()
{
    window->clear();
    window->draw(*bg);
    window->draw(text);
    window->draw(*readyRect);
    //std::cout << this->data->getMyID() << std::endl;
    
    

    for (auto p : *this->data->getPlayers()) {
        //std::cout << "position " << p->getShape()->getPosition().x << "x " << p->getShape()->getPosition().y << "y " << std::endl;
        window->draw(*p->getShape());
        sf::RectangleShape* playerReady = new sf::RectangleShape();
        sf::Text* myIDNumber = new sf::Text;
        playerReady->setSize(sf::Vector2f(23, 26));
        playerReady->setPosition(p->getPos().x + 7, p->getPos().y - 35);

        myIDNumber->setFont(*font);
        myIDNumber->setString(std::to_string(p->getID()));
        myIDNumber->setPosition(p->getPos().x + 13, p->getPos().y + 10);
        myIDNumber->setCharacterSize(10);
        myIDNumber->setOutlineColor(sf::Color::Green);

        window->draw(*myIDNumber);

        /*if (p->isReadyToPlay())
        {
            playerReady->setFillColor(sf::Color::Green);
        }
        playerReady->setFillColor(sf::Color::Red);*/
        
        if (p->isReadyToPlay())
        {
            playerReady->setFillColor(sf::Color::Green);
        }
        else
        {
            playerReady->setFillColor(sf::Color::Red);
        }

        /*p->isReadyToPlay() ? playerReady->setFillColor(sf::Color::Green) : playerReady->setFillColor(sf::Color::Red);*/
    
        window->draw(*playerReady);
        //p->isReadyToPlay() ? playerReady->setFillColor(sf::Color::Green) : playerReady->setFillColor(sf::Color::Red);
    }
    window->display();
}

void Lobby::run_lobby()
{
    std::cout << "run lobby \n";
    while (window->isOpen()) {
        loop_events();
        draw();
    }
}

void Lobby::set_values()
{
    //pos = 0;
    pressed = theselect = false;
    font->loadFromFile("ethn.otf");
    image->loadFromFile("./lobby.png");
    bg->setTexture(*image);

    sf::Vector2u windowSize = window->getSize();

    // Get the size of the loaded texture
    sf::Vector2u textureSize = image->getSize();

    float scaleX = static_cast<float>(windowSize.x) / textureSize.x;
    float scaleY = static_cast<float>(windowSize.y) / textureSize.y;

    bg->setScale(scaleX, scaleY);
    pos_mouse = { 0,0 };
    mouse_coord = { 0, 0 };

    options = { "READY!" };

    
    text.setFont(*font);
    text.setString(options[0]);
    text.setCharacterSize(72);
    text.setOutlineColor(sf::Color::Black);
    text.setPosition({450,600});
    
    //readyRect->setSize(sf::Vector2f(23, 26));
    //readyRect->setPosition(600, 500);
    //readyRect->setFillColor(sf::Color::Red);
}

void Lobby::loop_events()
{
    pos_mouse = sf::Mouse::getPosition(*window);
    mouse_coord = window->mapPixelToCoords(pos_mouse);

    sf::Event event;
    while (window->pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window->close();
        }

        else if (event.type == sf::Event::MouseButtonPressed)
        {
            if (event.key.code == sf::Mouse::Left) {
                if (text.getGlobalBounds().contains(mouse_coord))
                {

                    //after clicking ready check will change color for all players

                    if (data->getIsReadyToPlay(data->getMyID()))
                    {
                        data->setIsNotReadyToPlay(data->getMyID());
                        if (data->amIClient())
                        {
                            Client& client = client.getInstance(data, processor);
                            client.send(processor->packData("isNotReadyToPlay", data->getMyID()));
                        }
                        else
                        {
                            Server& server = server.getInstance(data, processor);
                            server.broadcastMessage(data->getPlayers(), processor->packData("isNotReadyToPlay", data->getMyID()));
                        }
                    }
                    else
                    {
                        data->setIsReadyToPlay(data->getMyID());
                        if (data->amIClient())
                        {
                            Client& client = client.getInstance(data, processor);
                            client.send(processor->packData("isReadyToPlay", data->getMyID()));
                        }
                        else
                        {
                            Server& server = server.getInstance(data, processor);
                            server.broadcastMessage(data->getPlayers(), processor->packData("isReadyToPlay", data->getMyID()));
                        }
                    }

                    
                    //client.send()

                    /*if (readyRect->getFillColor() == sf::Color::Green)
                    {
                        readyRect->setFillColor(sf::Color::Red);
                    }
                    else
                    {
                        readyRect->setFillColor(sf::Color::Green);
                    }*/

                }
            }
        }

        //if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        //    //if (readyRect->getGlobalBounds().contains(mouse_coord)) {
        //    //    //std::cout << "Close the window!" << '\n';
        //    //    window->close();
        //    //}
        //    if (text.getGlobalBounds().contains(mouse_coord))
        //    {
        //        if (readyRect->getFillColor() == sf::Color::Green)
        //        {
        //            readyRect->setFillColor(sf::Color::Red);
        //        }
        //        else
        //        {
        //            readyRect->setFillColor(sf::Color::Green);
        //        }

        //    }
        //}
    }
}


