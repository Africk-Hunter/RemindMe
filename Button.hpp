#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>


class Button {

public:

	Button();
	Button(sf::Vector2f, sf::Vector2f);

	void setTexture(sf::Texture);
	void setPosition(sf::Vector2f pos);
	sf::Vector2f getPosition();
	void setSize(sf::Vector2f);

	sf::Vector2f getSize();
	sf::Texture getTexture();
	float getSizeX();
	float getSizeY();
	void drawTo(sf::RenderWindow& window);
	bool isHovered(sf::RenderWindow&);

private:

	sf::RectangleShape button;
	sf::Texture buttonTexture;
	sf::Text text;
	
	float xPos, yPos, xSize, ySize;




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