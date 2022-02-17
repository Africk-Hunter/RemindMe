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
	Textbox(int, int, sf::Vector2f, bool, sf::Color);

	int getSizeX();
	int getsizeY();
	bool getIsLimitReached();
	int getLimit();

	void setCharSize(int);
	void setSize(sf::Vector2f);
	void setIsLimitReached(bool);
	void setLimit(int);
	void setFont(sf::Font&);

	void drawTo(sf::RenderWindow&);
	void typedOn(sf::Event);
	void setPosition(sf::Vector2f);



private:
	sf::Text textbox;
	std::ostringstream textStream;
	bool isLimitReached = false;
	int limit, lineLimit;
	float sizeX, sizeY;
	int charCount = 0;

	void keyboardInput(int);
	void deleteChar();
	bool wrapText(int);

};