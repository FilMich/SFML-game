#pragma once
#include "Tile.h"
#include <vector>

class Map {
public:
    Map(int width, int height); // Width and height in terms of number of tiles
    void loadMap(const std::vector<std::vector<TextureType>>& layout); // Load map layout
    void draw(sf::RenderWindow* window);
    bool collisionCheck(const sf::Vector2f& nextPosition) const;

private:
    std::vector<std::vector<Tile>> tiles;
    int width, height;
};