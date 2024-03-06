#pragma once
#include "map.h"
#include "player.h"
#include "server.h"
#include "client.h"
#include "data.h"
#include "processor.h"  
#include "bullet.h"
class Controls {
public:
    Controls(Map& map);
    void handleInput(Player& player, sf::RenderWindow* window);
    void shoot(Player& player, sf::RenderWindow* window);
private:
    Map& map;

    bool checkCollision(Player& player, const sf::Vector2f& direction) const;
    sf::Vector2f calculateNextPosition(Player& player, const sf::Vector2f& direction) const;
    void sendPosition(const sf::Vector2f& position);
};