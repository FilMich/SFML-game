#include "SFML/System.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/Network.hpp"
#include "SFML/Window.hpp"
#include "SFML/Audio.hpp"
#include <iostream>

int main() {

	sf::RenderWindow win(sf::VideoMode(800, 600), "game", sf::Style::Default);
	
	sf::SoundBuffer soundBuffer;

	if (!soundBuffer.loadFromFile("background.mp3"))
	{
		std::cout << "dfgh" << std::endl;
	}

	sf::Sound sound;
	sound.setBuffer(soundBuffer);
	sound.play();

	std::cout << sound.getVolume();

	

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
		}
		
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			sound.setVolume(sound.getVolume() + 10);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			sound.setVolume(sound.getVolume() - 10);
		}

		win.clear();
		win.draw(ball);
		win.display();

	}

	return 0;
}