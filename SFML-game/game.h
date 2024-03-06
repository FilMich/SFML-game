#pragma once
#include "assetsManager.h"
#include "controls.h"
#include "map.h"
#include "data.h"
#include "bullet.h"
class Game
{
public:
	Game(int numOfMap, int width, int height, sf::RenderWindow* window);
	~Game();
	void run();
	void draw(sf::RenderWindow* window);
	void drawMinimapElements(sf::RenderWindow* window);
private:
	sf::RenderWindow* window;
	Map* map;
	Controls* controls;
	Player* player;
	sf::View* view;
	sf::View* miniMap;
	int height;
	int width;
	std::vector<Bullet*> bullets;
};