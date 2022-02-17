#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Textbox.h"


class Button {

public:

	Button();
	Button(sf::Vector2f, sf::Vector2f);

	void setTexture(sf::Texture);
	void setPosition(sf::Vector2f pos);
	sf::Vector2f getPosition();
	void setSizeX(int);
	void setSizeY(int);
	int getSizeX();
	int getSizeY();
	void drawTo(sf::RenderWindow& window);
	bool isHovered(sf::RenderWindow&);


private:

	sf::RectangleShape button;
	sf::Texture buttonTexture;
	sf::Text text;
	Textbox inputTextbox;
	int xPos, yPos, xSize, ySize;




};


/*

[ Characteristics of a Button ]

- Rectangle
- Has text (sometimes)

[ Behaviors of a Button ]
- Be Clickable
- Be Hoverable
- Be drawable to window


*/