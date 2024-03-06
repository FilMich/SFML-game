#include "processor.h"
#include <iostream>


Processor::Processor()
{
}

Processor::~Processor()
{
}

std::string Processor::colorToString(sf::Color color)
{
	std::string strColor;
	if (color == sf::Color().Blue)
	{
		strColor = "blue";
	}
	else if (color == sf::Color().Green)
	{
		strColor = "green";
	}
	else if (color == sf::Color().Magenta)
	{
		strColor = "magenta";
	}
	else if (color == sf::Color().Red)
	{
		strColor = "red";
	}
	else if (color == sf::Color().Black)
	{
		strColor = "black";
	}
	else if (color == sf::Color().Yellow)
	{
		strColor = "yellow";
	}
	return strColor;
}

sf::Color Processor::stringToColor(std::string strColor)
{
	sf::Color color;
	if (strColor == "blue")
	{
		color = sf::Color().Blue;
	}
	else if (strColor == "green")
	{
		color = sf::Color().Green;
	}
	else if (strColor == "magenta")
	{
		color = sf::Color().Magenta;
	}
	else if (strColor == "black")
	{
		color = sf::Color().Black;
	}
	else if (strColor == "yellow")
	{
		color = sf::Color().Yellow;
	}
	else if (strColor == "red")
	{
		color = sf::Color().Red;
	}
	return color;
}

void Processor::processData(std::string action, int intID, int intPosx, int intPosy, sf::Color color)
{
	/*int intID;
	int intPosx;
	int intPosy;
	sf::Color color;*/

	Data& data = data.getInstance();
	if (action == "add")
	{
		data.addPlayer(intID, sf::Vector2f(intPosx,intPosy), color);
	}
	else if (action == "update")
	{
		data.updatePlayer(intID, sf::Vector2f(intPosx, intPosy), color);
	}
	else if (action == "updatePos")
	{
		data.updatePlayerPos(intID, sf::Vector2f(intPosx, intPosy));
	}
	else if (action == "updateCol")
	{
		data.updatePlayerColor(intID, color);
	}
	else if (action == "yourID")
	{
		data.setMyID(intID);
	}
	else if (action == "isReadyToPlay")
	{
		data.setIsReadyToPlay(intID);
	}
	else if (action == "isNotReadyToPlay")
	{
		data.setIsNotReadyToPlay(intID);
	}
	else if (action == "bulletFlying")
	{
		data.setIsNotReadyToPlay(intID);
	}

}

void Processor::unpackData(std::string message)
{
	std::istringstream issCount(message);
	std::istringstream iss(message);
	std::string word;
	int wordCount = 0;

	std::string action, stringID, stringPosx, stringPosy, stringColor;
	//std::string stringID;
	//std::string stringPosx;
	//std::string stringPosy;
	//std::string stringColor;

	int intID;
	int intPosx = 0;
	int intPosy = 0;
	sf::Color color;

	while (std::getline(issCount, word, ',')) {
		wordCount++;
	}

	if (wordCount == 5)
	{
		std::getline(iss, action, ','); 
		std::getline(iss, stringID, ',');
		std::getline(iss, stringPosx, ',');
		std::getline(iss, stringPosy, ',');
		std::getline(iss, stringColor, ',');

		intID = std::stoi(stringID);
		intPosx = std::stof(stringPosx);
		intPosy = std::stof(stringPosy);

		color = stringToColor(stringColor);
	}
	else if (wordCount == 2)
	{
		std::getline(iss, action, ',');
		std::getline(iss, stringID, ',');

		intID = std::stoi(stringID);
	}
	else if (wordCount == 4)
	{
		std::getline(iss, action, ',');
		std::getline(iss, stringID, ',');
		std::getline(iss, stringPosx, ',');
		std::getline(iss, stringPosy, ',');

		intID = std::stoi(stringID);
		intPosx = std::stof(stringPosx);
		intPosy = std::stof(stringPosy);
	}
	//std::string action;
	//std::string ID;
	//std::string strColor;
	//std::string posx;
	//std::string posy;
	//sf::Color color;
	

	processData(action, intID, intPosx, intPosy, color);

}

std::string Processor::packData(std::string action, int paID, sf::Vector2f pos, sf::Color color)
{
	/*std::string id = "" + ID;
	std::string posx = "" + ID;
	std::string posy = "" + ID;

	std::string sColor = "";*/
	std::string ID, posx, posy, strColor;
	ID = std::to_string(paID);
	posx = std::to_string(pos.x);
	posy = std::to_string(pos.y);

	strColor = colorToString(color);

	return action + "," + ID + "," + posx + "," + posy + "," + strColor;
}

std::string Processor::packData(std::string action, int paID)
{
	std::string ID;
	ID = std::to_string(paID); 
	return action + "," + ID; 
}

std::string Processor::packData(std::string action, int paID, const sf::Vector2f& position)
{
	std::string ID, posx, posy;
	ID = std::to_string(paID);
	posx = std::to_string(position.x);
	posy = std::to_string(position.y);
	return action + "," + ID + "," + posx + "," + posy;
}
