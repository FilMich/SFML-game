#pragma once
#include "SFML/Graphics.hpp"
#include <iostream>
#include "data.h"
class Lobby
{
public:
	Lobby(sf::RenderWindow* window, Data* data);
	~Lobby();

	void run_lobby();

private:
	Data* data;
	//std::vector<Player*>* players;
	int pos;
	bool pressed, theselect;
	sf::RenderWindow* window;
	sf::RectangleShape* readyRect;
	sf::RectangleShape* playerReady;
	sf::Font* font;
	sf::Texture* image;
	sf::Sprite* bg;
	sf::Vector2i pos_mouse;
	sf::Vector2f mouse_coord;

	std::vector<const char*> options;
	std::vector<sf::Vector2f> coords;
	sf::Text text;
	std::vector<sf::Text> texts;
	std::vector<std::size_t> sizes;

	void set_values();
	void loop_events();
	void draw();
};