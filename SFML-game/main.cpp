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
		Data* data = new Data();
		data->setIsClient();
		Processor* processor = new Processor(data);
		Lobby lobby(win, data, processor);

		Client& client = client.getInstance(data, processor);
		client.connect();
		
		lobby.run_lobby();

	}
	else if(mainMenu.getNext() == 2)
	{
		win->setTitle("Server");
		Data* data = new Data();
		data->setIsNotClient();
		Processor* processor = new Processor(data);
		Lobby lobby(win, data, processor);

		Server& server = server.getInstance(data, processor);
		//data->addPlayer(11, { 200,200 }, sf::Color::Black);
		server.start();

		
		lobby.run_lobby();
	}
	return 0;
}


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