#include "SFML/System.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/Network.hpp"
#include "SFML/Window.hpp"
#include "SFML/Audio.hpp"
#include <iostream>
#include "lobby.h"
#include "client.h"
#include "data.h"
#include "server.h"
#include "menu.h"
#include "mainMenu.h"
#include "map.h"
#include "controls.h"
#include "assetsManager.h"
#include "game.h"

int main() {
	int c = 0;
	sf::RenderWindow* win = new sf::RenderWindow(sf::VideoMode(1280, 720), "game", sf::Style::Default);
	Menu menu(win);
	MainMenu mainMenu(win); 
	
	//lobby.run_lobby();

	if (menu.getRun())
	{
		menu.run_menu();
	}
	if(menu.getNext() == 1)
	{
		mainMenu.run_menu();
	}
	if (mainMenu.getNext() == 1)
	{
		win->setTitle("Client");
		Data& data = data.getInstance();
		data.setIsClient();
		//Processor& processor = processor.getInstance();
		Lobby lobby(win);

		Client& client = client.getInstance();
		client.connect();
		
		lobby.run_lobby();

		Game game(1, 100, 100, win);
		game.run();
	}
	else if(mainMenu.getNext() == 2)
	{
		win->setTitle("Server");
		Data& data = data.getInstance(); 
		data.setIsNotClient(); 
		//Processor* processor = new Processor(data);
		Lobby lobby(win);

		Server& server = server.getInstance();

		server.start();

		
		lobby.run_lobby();
		Game game(1, 100, 100, win);
		game.run();
		//AssetsManager& assetsManager = assetsManager.getInstance();
		//assetsManager.loadTextures();
		//Map map(100,100);
		//Controls controls(map);
		///*sf::Texture text;
		//text.loadFromFile("./grassTile.png");*/
		//sf::Sprite sprit;
		//
		//sf::Texture t = assetsManager.getTexture(TextureType::Grass);
		//sprit.setTexture(t);
		//while (win->isOpen()) {
		//	// Process events
		//	sf::Event event;
		//	while (win->pollEvent(event)) {
		//		if (event.type == sf::Event::Closed)
		//			win->close();
		//	}

		//	// Handle player input
		//	Player* player;
		//	player = data.findPlayerWithID(data.getMyID());
		//	controls.handleInput(*player, *win);
		//	
		//	
		//	//sprit.setTexture(text);
		//	
		//	//sprit.setScale(sf::Vector2f(0.1, 0.1));
		//	sprit.setPosition(sf::Vector2f(10, 10));
		//	// Render update
		//	win->clear();
		//	//win->draw(sprit);
		//	map.draw(win);
		//	win->draw(*player->getShape()); // Assuming you have a draw method for the player
		//	win->display();
		//}
	}
	return 0;
}


//class TileMap : public sf::Drawable, public sf::Transformable
//{
//public:
//
//	bool load(const std::string& tileset, sf::Vector2u tileSize, const int* tiles, unsigned int width, unsigned int height)
//	{
//		// load the tileset texture
//		if (!m_tileset.loadFromFile(tileset))
//			return false;
//
//		// resize the vertex array to fit the level size
//		m_vertices.setPrimitiveType(sf::Triangles);
//		m_vertices.resize(width * height * 6);
//
//		// populate the vertex array, with two triangles per tile
//		for (unsigned int i = 0; i < width; ++i)
//			for (unsigned int j = 0; j < height; ++j)
//			{
//				// get the current tile number
//				int tileNumber = tiles[i + j * width];
//
//				// find its position in the tileset texture
//				int tu = tileNumber % (m_tileset.getSize().x / tileSize.x);
//				int tv = tileNumber / (m_tileset.getSize().x / tileSize.x);
//
//				// get a pointer to the triangles' vertices of the current tile
//				sf::Vertex* triangles = &m_vertices[(i + j * width) * 6];
//
//				// define the 6 corners of the two triangles
//				triangles[0].position = sf::Vector2f(i * tileSize.x, j * tileSize.y);
//				triangles[1].position = sf::Vector2f((i + 1) * tileSize.x, j * tileSize.y);
//				triangles[2].position = sf::Vector2f(i * tileSize.x, (j + 1) * tileSize.y);
//				triangles[3].position = sf::Vector2f(i * tileSize.x, (j + 1) * tileSize.y);
//				triangles[4].position = sf::Vector2f((i + 1) * tileSize.x, j * tileSize.y);
//				triangles[5].position = sf::Vector2f((i + 1) * tileSize.x, (j + 1) * tileSize.y);
//
//				// define the 6 matching texture coordinates
//				triangles[0].texCoords = sf::Vector2f(tu * tileSize.x, tv * tileSize.y);
//				triangles[1].texCoords = sf::Vector2f((tu + 1) * tileSize.x, tv * tileSize.y);
//				triangles[2].texCoords = sf::Vector2f(tu * tileSize.x, (tv + 1) * tileSize.y);
//				triangles[3].texCoords = sf::Vector2f(tu * tileSize.x, (tv + 1) * tileSize.y);
//				triangles[4].texCoords = sf::Vector2f((tu + 1) * tileSize.x, tv * tileSize.y);
//				triangles[5].texCoords = sf::Vector2f((tu + 1) * tileSize.x, (tv + 1) * tileSize.y);
//			}
//
//		return true;
//	}
//
//private:
//
//	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
//	{
//		// apply the transform
//		states.transform *= getTransform();
//
//		// apply the tileset texture
//		states.texture = &m_tileset;
//
//		// draw the vertex array
//		target.draw(m_vertices, states);
//	}
//
//	sf::VertexArray m_vertices;
//	sf::Texture m_tileset;
//};
//
//int main()
//{
//	// create the window
//	sf::RenderWindow window(sf::VideoMode(512, 512), "Tilemap");
//
//	// define the level with an array of tile indices
//	const int level[] =
//	{
//		0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
//		0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0,
//		1, 1, 0, 0, 0, 0, 0, 0, 3, 3, 3, 3, 3, 3, 3, 3,
//		0, 1, 0, 0, 2, 0, 3, 3, 3, 0, 1, 1, 1, 0, 0, 0,
//		0, 1, 1, 0, 3, 3, 3, 0, 0, 0, 1, 1, 1, 2, 0, 0,
//		0, 0, 1, 0, 3, 0, 2, 2, 0, 0, 1, 1, 1, 1, 2, 0,
//		2, 0, 1, 0, 3, 0, 2, 2, 2, 0, 1, 1, 1, 1, 1, 1,
//		0, 0, 1, 0, 3, 2, 2, 2, 0, 0, 0, 0, 1, 1, 1, 1,
//		0, 0, 1, 0, 3, 2, 2, 2, 0, 0, 0, 0, 1, 1, 1, 1,
//		0, 0, 1, 0, 3, 2, 2, 2, 0, 0, 0, 0, 1, 1, 1, 1,
//		0, 0, 1, 0, 3, 2, 2, 2, 0, 0, 0, 0, 1, 1, 1, 1,
//		0, 0, 1, 0, 3, 2, 2, 2, 0, 0, 0, 0, 1, 1, 1, 1,
//		0, 0, 1, 0, 3, 2, 2, 2, 0, 0, 0, 0, 1, 1, 1, 1,
//		0, 0, 1, 0, 3, 2, 2, 2, 0, 0, 0, 0, 1, 1, 1, 1,
//		0, 0, 1, 0, 3, 2, 2, 2, 0, 0, 0, 0, 1, 1, 1, 1,
//	};
//
//	// create the tilemap from the level definition
//	TileMap map;
//	if (!map.load("tileset.png", sf::Vector2u(32, 32), level, 16, 15))
//		return -1;
//
//	// run the main loop
//	while (window.isOpen())
//	{
//		// handle events
//		sf::Event event;
//		while (window.pollEvent(event))
//		{
//			if (event.type == sf::Event::Closed)
//				window.close();
//		}
//
//		// draw the map
//		window.clear();
//		window.draw(map);
//		window.display();
//	}
//
//	return 0;
//}



//class Tile {
//public:
//	sf::Sprite sprite; // Image of the tile
//	sf::Vector2f position; // Position of the tile
//
//	// Constructor to initialize tile properties
//	Tile(sf::Texture& texture, const sf::Vector2f& position) : position(position) {
//		sprite.setTexture(texture);
//		sprite.setPosition(position);
//	}
//
//	// Method to draw the tile on the screen
//	void draw(sf::RenderWindow& window) {
//		window.draw(sprite);
//	}
//};
//
//// Define Playground class
//class Playground {
//public:
//	// Constructor to initialize playground size and tiles
//	Playground(int rows, int cols) : rows(rows), cols(cols) {
//		// Initialize the matrix of tiles
//		texture.loadFromFile("./grassTile.png");
//		tiles.resize(rows, std::vector<Tile>(cols, Tile(texture, sf::Vector2f())));
//	}
//
//	// Method to draw the playground on the screen
//	void draw(sf::RenderWindow& window) {
//		// Draw all tiles in the matrix
//		for (int i = 0; i < rows; ++i) {
//			for (int j = 0; j < cols; ++j) {
//				tiles[i][j].draw(window);
//			}
//		}
//	}
//
//private:
//	int rows; // Number of rows in the playground
//	int cols; // Number of columns in the playground
//	sf::Texture texture; // Texture for tiles
//	std::vector<std::vector<Tile>> tiles; // Matrix of tiles
//};
//
//int main() {
//	sf::RenderWindow window(sf::VideoMode(800, 600), "Playground");
//
//	// Create playground object
//	Playground playground(10, 10); // Example: 10x10 grid
//
//	// Main loop
//	while (window.isOpen()) {
//		sf::Event event;
//		while (window.pollEvent(event)) {
//			if (event.type == sf::Event::Closed) {
//				window.close();
//			}
//		}
//
//		window.clear();
//
//		// Draw the playground
//		playground.draw(window);
//
//		window.display();
//	}
//
//	return 0;
//}




/*sf::RenderWindow wind(sf::VideoMode(800, 600), "server");
	while (c == 0)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
			c = 1;
			wind.close();
		}

		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::C)) {
			c = 2;
			wind.close();
		}
	}
	Data data;
	sf::RenderWindow* win = new sf::RenderWindow(sf::VideoMode(1280, 720), "game", sf::Style::Default);
	if (c == 1)
	{

		Server server(data);
		server.run();

		Lobby lobby(win);
		lobby.run_lobby();
	}
	else if (c == 2)
	{
		Client client;
		client.connect();

		Lobby lobby(win);
		lobby.run_lobby();
	}*/
	/*sf::RenderWindow win(sf::VideoMode(800, 600), "game", sf::Style::Default);

	sf::CircleShape ball;
	ball.setFillColor(sf::Color::Green);
	ball.setPosition(100, 100);
	ball.setRadius(30);

	while (win.isOpen())
	{
		sf::Event event;
		while (win.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				win.close();
			}
			else if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Up) {
					ball.setPosition(ball.getPosition().x, ball.getPosition().y - 5);
				}
				else if (event.key.code == sf::Keyboard::Down) {
					ball.setPosition(ball.getPosition().x, ball.getPosition().y + 5);
				}
				else if (event.key.code == sf::Keyboard::Left) {
					ball.setPosition(ball.getPosition().x - 5, ball.getPosition().y);
				}
				else if (event.key.code == sf::Keyboard::Right) {
					ball.setPosition(ball.getPosition().x + 5, ball.getPosition().y);
				}
			}
		}

		win.clear();
		win.draw(ball);
		win.display();

	}*/

//int main() {
//
//	sf::RenderWindow win(sf::VideoMode(800, 600), "game", sf::Style::Default);
//	
//	sf::SoundBuffer soundBuffer;
//
//	if (!soundBuffer.loadFromFile("background.mp3"))
//	{
//		std::cout << "dfgh" << std::endl;
//	}
//
//	sf::Sound sound;
//	sound.setBuffer(soundBuffer);
//	sound.setVolume(50);
//	sound.play();
//
//	std::cout << "volume : " << sound.getVolume() << std::endl;
//
//	
//
//	sf::CircleShape ball;
//	ball.setFillColor(sf::Color::Green);
//	ball.setPosition(100, 100);
//	ball.setRadius(30);
//
//	while (win.isOpen())
//	{
//		sf::Event event;
//		while (win.pollEvent(event))
//		{
//			if (event.type == sf::Event::Closed)
//			{
//				win.close();
//			}
//			else if (event.type == sf::Event::KeyPressed) {
//				if (event.key.code == sf::Keyboard::Up && sound.getVolume() < 110) {
//					sound.setVolume(sound.getVolume() + 10);
//					std::cout << "Volume + \n Current volume: " << sound.getVolume() << std::endl;
//				}
//				else if (event.key.code == sf::Keyboard::Down && sound.getVolume() > 10 ) {
//					sound.setVolume(sound.getVolume() - 10);
//					std::cout << "Volume - \n Current volume: " << sound.getVolume() << std::endl;
//				}
//			}
//		}
//
//		win.clear();
//		win.draw(ball);
//		win.display();
//
//	}
//
//	return 0;
//}