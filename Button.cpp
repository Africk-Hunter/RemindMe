#include "Button.hpp"

Button::Button() { }

Button::Button(sf::Vector2f pos, sf::Vector2f size) {


	sf::FloatRect textRect = text.getLocalBounds();
	text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
	text.setPosition(sf::Vector2f(pos));

	//Button Properties//
	button.setPosition(pos);
	button.setSize(size);
	setSizeX(size.x);
	setSizeX(size.y);

	//float xOrg = button.getLocalBounds().width / 2;
	//float yOrg = button.getLocalBounds().height / 2;

	//button.setOrigin(xOrg, yOrg);


}
void Button::setSizeX(int nSizeX) {
	xSize = nSizeX;
}
void Button::setSizeY(int nSizeY) {
	ySize = nSizeY;
}
int Button::getSizeX() {
	return xSize;
}
int Button::getSizeY() {
	return ySize;
}
void Button::setTexture(sf::Texture newText) {
	buttonTexture = newText;
	button.setTexture(&buttonTexture);
}
sf::Vector2f Button::getPosition() {
	return button.getPosition();
}
void Button::setPosition(sf::Vector2f pos) {

	xPos = pos.x;
	yPos = pos.y;
	button.setPosition(pos);


}
void Button::drawTo(sf::RenderWindow& window) {
	window.draw(button);
	window.draw(text);
}
bool Button::isHovered(sf::RenderWindow& window) {

	float mouseX = sf::Mouse::getPosition(window).x;
	float mouseY = sf::Mouse::getPosition(window).y;

	// Gets button's left & bottom edges
	xPos = button.getPosition().x;
	yPos = button.getPosition().y;

	// Gets button's right & top edges
	float buttonPosWidth = button.getPosition().x + button.getLocalBounds().width;
	float buttonPosHeight = button.getPosition().y + button.getLocalBounds().height;

	if (mouseX < buttonPosWidth && mouseX > xPos && mouseY < buttonPosHeight && mouseY > yPos) {
		return true;
	}
	else {
		return false;
	}


}