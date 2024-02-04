#include "processor.h"
#include <iostream>


Processor::Processor(Data* data)
{
	this->data = data;
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

void Processor::processData(std::string action)
{
	if (action == "add")
	{
		this->data->addPlayer(intID, { intPosx,intPosy}, color); 
	}
	else if (action == "update")
	{
		this->data->updatePlayer(intID, { intPosx,intPosy }, color);
	}
	else if (action == "updatePos")
	{
		this->data->updatePlayerPos(intID, { intPosx,intPosy });
	}
	else if (action == "updateCol")
	{
		this->data->updatePlayerColor(intID, color);
	}
	else if (action == "yourID")
	{
		this->data->setMyID(intID);
	}
	else if (action == "isReadyToPlay")
	{
		this->data->setIsReadyToPlay(intID);
	}
	else if (action == "isNotReadyToPlay")
	{
		this->data->setIsNotReadyToPlay(intID);
	}

}

void Processor::unpackData(std::string message)
{
	std::istringstream issCount(message);
	std::istringstream iss(message);
	std::string word;
	int wordCount = 0;

	while (std::getline(issCount, word, ',')) {
		wordCount++;
	}

	if (wordCount == 5)
	{
		std::getline(iss, action, ','); 
		std::getline(iss, ID, ','); 
		std::getline(iss, posx, ','); 
		std::getline(iss, posy, ','); 
		std::getline(iss, strColor, ','); 

		intID = std::stoi(ID); 
		intPosx = std::stof(posx); 
		intPosy = std::stof(posy); 

		color = stringToColor(strColor);
	}
	else if (wordCount == 2)
	{
		std::getline(iss, action, ','); 
		std::getline(iss, ID, ',');

		intID = std::stoi(ID); 
	}
	//std::string action;
	//std::string ID;
	//std::string strColor;
	//std::string posx;
	//std::string posy;
	//sf::Color color;
	

	processData(action);

}

std::string Processor::packData(std::string action, int paID, sf::Vector2f pos, sf::Color color)
{
	/*std::string id = "" + ID;
	std::string posx = "" + ID;
	std::string posy = "" + ID;

	std::string sColor = "";*/
	ID = std::to_string(paID);
	posx = std::to_string(pos.x);
	posy = std::to_string(pos.y);

	strColor = colorToString(color);

	return action + "," + ID + "," + posx + "," + posy + "," + strColor;
}

std::string Processor::packData(std::string action, int paID)
{
	ID = std::to_string(paID); 
	return action + "," + ID; 
}
