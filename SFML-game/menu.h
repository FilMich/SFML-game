#pragma once
#include "SFML/Graphics.hpp"
#include <iostream>
class Menu
{
public:
	Menu(sf::RenderWindow* window);
	~Menu();

	void run_menu();
	int getNext();
	bool getRun();

private:
	int pos;
	bool pressed, theselect;
	bool run = true;
	int next;
	sf::RenderWindow* window;
	sf::RectangleShape* winClose;
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