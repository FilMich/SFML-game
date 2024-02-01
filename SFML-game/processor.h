#pragma once
#include <iostream>
#include <sstream>
#include "data.h"
#include "SFML/Graphics.hpp"

class Processor
{
public:
	Processor(Data* data);
	~Processor();
	std::string colorToString(sf::Color color);
	sf::Color stringToColor(std::string color);
	void processData(std::string action);
	void unpackData(std::string message);
	std::string packData(std::string action, int paID, sf::Vector2f pos, sf::Color color);

private:
	Data* data;
	std::string action;
	std::string ID;
	std::string strColor;
	std::string posx;
	std::string posy;
	sf::Color color;
	int intID;
	float intPosx;
	float intPosy;
};