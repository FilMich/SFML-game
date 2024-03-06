#pragma once
#include <iostream>
#include <sstream>
#include "data.h"
#include "SFML/Graphics.hpp"

class Processor
{
public:

	static Processor& getInstance() {
		static Processor instance;
		return instance;
	}

	
	~Processor();
	std::string colorToString(sf::Color color);
	sf::Color stringToColor(std::string color);
	void processData(std::string action, int intID, int intPosx, int intPosy, sf::Color color);
	void unpackData(std::string message);
	std::string packData(std::string action, int paID, sf::Vector2f pos, sf::Color color);
	std::string packData(std::string action, int paID);
	std::string packData(std::string action, int paID, const sf::Vector2f& position);

private:
	Processor();
	/*std::string action;
	std::string ID;
	std::string strColor;
	std::string posx;
	std::string posy;
	sf::Color color;
	int intID;
	float intPosx;
	float intPosy;*/
};