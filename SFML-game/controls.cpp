#include "Controls.h"

Controls::Controls(Map& map) : map(map) {}

void Controls::handleInput(Player& player, sf::RenderWindow* window) {
    bool playerMoved = false;
    sf::Vector2f direction(0.f, 0.f);
    float moveSpeed = 20.0;
    Data& data = data.getInstance();
    sf::Vector2i mousePos;
    sf::Vector2f mouseCoord;
    
    if (!data.amIClient()) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            direction.y -= moveSpeed;
            playerMoved = true;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            direction.y += moveSpeed;
            playerMoved = true;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            direction.x -= moveSpeed;
            playerMoved = true;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            direction.x += moveSpeed;
            playerMoved = true;
        }
    }
    else
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::I)) {
            direction.y -= moveSpeed;
            playerMoved = true;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::K)) {
            direction.y += moveSpeed;
            playerMoved = true;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::J)) {
            direction.x -= moveSpeed;
            playerMoved = true;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::L)) {
            direction.x += moveSpeed;
            playerMoved = true;
        }
    }

    
    sf::Vector2f nextPosition = calculateNextPosition(player, direction);

    
    if (!checkCollision(player, direction) && playerMoved) {
        
        player.setPos(nextPosition);
        sendPosition(nextPosition);
    }
}

void Controls::shoot(Player& player, sf::RenderWindow* window)
{
    sf::Vector2i mousePos;
    sf::Vector2f mouseCoord;

    
    mousePos = sf::Mouse::getPosition(*window);
    mouseCoord = window->mapPixelToCoords(mousePos);
    sf::Vector2f direction = mouseCoord - player.getPos();
    float magnitude = std::sqrt(direction.x * direction.x + direction.y * direction.y);
    direction /= magnitude;

    player.shootBullet(direction);
    
}

bool Controls::checkCollision(Player& player, const sf::Vector2f& direction) const {
    
    sf::Vector2f nextPosition = calculateNextPosition(player, direction);
    return map.collisionCheck(nextPosition);
}

sf::Vector2f Controls::calculateNextPosition(Player& player, const sf::Vector2f& direction) const {
    return player.getPos() + direction;
}

void Controls::sendPosition(const sf::Vector2f& position)
{
    Data& data = data.getInstance();
    Processor& processor = processor.getInstance();
    if (data.amIClient())
    {
        Client& client = client.getInstance();
        client.send(processor.packData("updatePos", data.getMyID(), position));
    }
    else
    {
        Server& server = server.getInstance();
        server.broadcastMessage(data.getPlayers(), processor.packData("updatePos", data.getMyID(), position));
    }
}
