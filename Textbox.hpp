#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <sstream>

#define DELETE_KEY 8
#define ENTER_KEY 13
#define ESCAPE_KEY 27

class Textbox {

public:
	Textbox();
	Textbox(int, int, sf::Vector2f, sf::Vector2f, sf::Color, sf::Font&);

	float getSizeX();
	float getsizeY();
	int getMaxChars();
	bool getSelectionState();
	sf::Text getTextbox();
	void turnOffSelection();

	void reverseSelectState();
	void setCharSize(int);
	void setSize(sf::Vector2f);
	void setMaxChars(int);
	void setFont(sf::Font&);
	void setPosition(sf::Vector2f);
	void setString(std::string);

	void drawTo(sf::RenderWindow&);
	void verifyValidInput(sf::Event);
	void stringEdit(int);

	
	

private:

	sf::Text textbox;
	sf::RectangleShape boundsBox;
	std::string textString;
	bool isSelected;
	int maxChars, lineLimit, currentChars;
	float sizeX, sizeY, currentPos;
	int charCount = 0;
	sf::Font simplePixels;
	
	void deleteChar();
	bool wrapText(int);

};