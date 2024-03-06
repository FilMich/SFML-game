#include "SFML/Graphics.hpp"
#include "assetsManager.h"


class Tile {
public:
    Tile(sf::Vector2f position, TextureType type);
    void draw(sf::RenderWindow* window);
    bool isPassable() const;

private:
    sf::Vector2f position;
    TextureType type;
    sf::Sprite sprite; // Assuming you have a texture manager to assign textures
    sf::Texture texture;
};
