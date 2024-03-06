#pragma once
#include "SFML/Graphics.hpp"
#include <unordered_map>
#include "textureType.h"

class AssetsManager
{
public:
	static AssetsManager& getInstance() {
		static AssetsManager instance;
		return instance;
	}

	void loadTextures() {
		sf::Texture texture;
		texture.loadFromFile("./groundTile.png");
		textures[TextureType::Ground] = std::move(texture);
		texture.loadFromFile("./grassTile.png");
		textures[TextureType::Grass] = std::move(texture);
		texture.loadFromFile("./stoneTile.png");
		textures[TextureType::Wall] = std::move(texture);

	}

	sf::Texture& getTexture(TextureType type) {
		return textures[type];
	}

private:
	std::unordered_map<TextureType, sf::Texture> textures;
};