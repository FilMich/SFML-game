#include "game.h"

Game::Game(int numOfMap, int width, int height, sf::RenderWindow* window)
{
	this->width = width;
	this->height = height;
	AssetsManager& assetsManager = assetsManager.getInstance();
	assetsManager.loadTextures();
	map = new Map(width, height);
	controls = new Controls(*map);
	this->window = window;
	Data& data = data.getInstance();
	player = data.findPlayerWithID(data.getMyID());
	view = new sf::View(sf::FloatRect(0, 0, 1280, 720));
	miniMap = new sf::View(sf::FloatRect(0, 0, width, height));
	view->setCenter(player->getPos());
	miniMap->setSize(sf::Vector2f(width, height));
	miniMap->setViewport(sf::FloatRect(0.75f, 0.75f, 0.25f, 0.25f));
}

Game::~Game()
{
	delete map;
	delete controls;
}

void Game::run()
{
	sf::Clock clock;
	sf::Vector2i mousePos;
	sf::Vector2f mouseCoord;
	
	while (window->isOpen()) {
		sf::Event event;
		while (window->pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window->close();

			else if (event.type == sf::Event::MouseButtonPressed)
			{
				controls->shoot(*player, window);
				clock.restart();
			}
		}
		sf::Time elapsed = clock.getElapsedTime();
		if (elapsed.asSeconds() >= 2) {
			player->addToMagazine();
			clock.restart();
		}
		controls->handleInput(*player, window);
		this->draw(window);
	}
}

void Game::draw(sf::RenderWindow* window)
{
	view->setCenter(player->getPos());
	window->setView(*view);

	window->clear();

	Data& data = data.getInstance();
	window->clear();
	map->draw(window);
	for (auto p : *data.getPlayers()) {
		window->draw(*p->getShape());
	}
	player->bulletFly();
	for (auto b : player->getBullets()) {
		b->draw(window);
	}
	for (int i = 0; i < player->getMagazine(); i++)
	{
		sf::RectangleShape bullet;
		bullet.setFillColor(sf::Color::Black);
		bullet.setPosition(player->getPos().x + (i * 10), player->getPos().y + 100);
		bullet.setSize(sf::Vector2f(5,10));
		window->draw(bullet);
	}
	//window->setView(*miniMap);
	//drawMinimapElements(window);
	//window->draw(*player->getShape());
	window->display();
}

void Game::drawMinimapElements(sf::RenderWindow* window) {
	float scaleFactor = 0.2f;

	for (int x = 0; x < this->width; x++) {
		for (int y = 0; y < this->height; y++) {
			sf::RectangleShape tileShape(sf::Vector2f(20 * scaleFactor, 20 * scaleFactor));
			tileShape.setPosition(x * 20 * scaleFactor, y * 20 * scaleFactor);
			tileShape.setFillColor(sf::Color::Green);
			window->draw(tileShape);
		}
	}

	
	Data& data = Data::getInstance();
	for (auto p : *data.getPlayers()) {
		sf::CircleShape playerShape(5.0f * scaleFactor);
		playerShape.setPosition(p->getPos().x * scaleFactor, p->getPos().y * scaleFactor);
		playerShape.setFillColor(p->getColor());
		miniMap->setCenter(playerShape.getPosition());
		window->draw(playerShape);
	}
}