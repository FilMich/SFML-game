#include "tile.h"

Tile::Tile(sf::Vector2f position, TextureType type) : position(position), type(type) {

    AssetsManager& assetsManager = assetsManager.getInstance();
    this->sprite.setTexture(assetsManager.getTexture(type));
    this->sprite.setPosition(position);
    this->sprite.setScale({ 1,1 });
    /*texture.loadFromFile("./grassTile.png");
    this->sprite.setTexture(texture);
    this->sprite.setScale(sf::Vector2f(0.5, 0.5));
    this->sprite.setPosition(position);*/

    //Textures& textures = textures.getInstance();
    //sf::Texture t = textures.getTexture(type);
    //this->sprite.setTexture(t);
    ////sf::Texture texture;
    ////texture.loadFromFile("./grassTile.png");
    ////this->sprite.setTexture(texture);
    
    
    // Initialize sprite based on type
    // For example, assign different textures based on the tile type
}

void Tile::draw(sf::RenderWindow* window) {
    window->draw(this->sprite);
}

bool Tile::isPassable() const {
    return type != TextureType::Wall;
}