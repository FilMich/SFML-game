#include "SFML/System.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/Network.hpp"
#include "SFML/Window.hpp"
#include "SFML/Audio.hpp"
#include <iostream>

int main() {

	sf::RenderWindow win(sf::VideoMode(), "game", sf::Style::Fullscreen);
	
	sf::SoundBuffer soundBuffer;

	if (!soundBuffer.loadFromFile("background.mp3"))
	{
		std::cout << "dfgh" << std::endl;
	}

	sf::Sound sound;
	sound.setBuffer(soundBuffer);
	sound.setVolume(50);
	sound.play();

	std::cout << "volume : " << sound.getVolume() << std::endl;

	

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
			else if (event.type == sf::Event::KeyPressed) {
				// Check if the Up or Down key is pressed
				if (event.key.code == sf::Keyboard::Up && sound.getVolume() < 110) {
					sound.setVolume(sound.getVolume() + 10);
					std::cout << "Volume + \n Current volume: " << sound.getVolume() << std::endl;
				}
				else if (event.key.code == sf::Keyboard::Down && sound.getVolume() > 10 ) {
					sound.setVolume(sound.getVolume() - 10);
					std::cout << "Volume - \n Current volume: " << sound.getVolume() << std::endl;
				}
			}
		}
		
		//if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		//{
		//	sound.setVolume(sound.getVolume() + 1);
		//}
		//else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		//{
		//	sound.setVolume(sound.getVolume() - 1);
		//}

		win.clear();
		win.draw(ball);
		win.display();

	}

	return 0;
}