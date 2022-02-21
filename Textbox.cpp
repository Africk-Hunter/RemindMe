#include "Textbox.hpp"
#include <sstream>



Textbox::Textbox() { 

	textbox.setCharacterSize(40);
	textbox.setFillColor(sf::Color::Black);
	textString = "";
	maxChars = 0;
	lineLimit = 0;
	charCount = 0;
	sizeY = 0;
	sizeX = 0;
	currentChars = 0;
	isSelected = false;

}

Textbox::Textbox(int charSize, int charLim, sf::Vector2f nSize, sf::Vector2f nPos, sf::Color textBoxColor, sf::Font& nFont) {

	textString = "";
	textbox.setCharacterSize(charSize);
	textbox.setFillColor(textBoxColor);
	boundsBox.setFillColor(sf::Color::Transparent);
	setFont(nFont);
	setSize(nSize);
	setPosition(nPos);
	currentPos = 0;
	maxChars = charLim;
	lineLimit = sizeX / charSize; // How many characters can fit on a line
	charCount = 0; // How many chars on the current line
	currentChars = 0;
	isSelected = false;
	
}

void Textbox::reverseSelectState() {
	isSelected = !isSelected;
}
void Textbox::turnOffSelection() {
	isSelected = false;
}
bool Textbox::getSelectionState() {
	return isSelected;
}
sf::Text Textbox::getTextbox() {
	return textbox;
}
float Textbox::getSizeX() {
	return sizeX;
}
float Textbox::getsizeY() {
	return sizeY;
}
int Textbox::getMaxChars() {
	return maxChars;
}
void Textbox::setCharSize(int nSize) {
	textbox.setCharacterSize(nSize);
}
void Textbox::setMaxChars(int size) {
	maxChars = size;
}
void Textbox::setSize(sf::Vector2f nSize) {
	boundsBox.setSize(nSize);
	sizeX = nSize.x;
	sizeY = nSize.y;
}
void Textbox::setFont(sf::Font& font) {
	textbox.setFont(font);
}
void Textbox::setPosition(sf::Vector2f pos) {
	boundsBox.setPosition(pos);
	textbox.setPosition(pos);
}

void Textbox::drawTo(sf::RenderWindow& window) {
	window.draw(boundsBox);
	window.draw(textbox);
}
void Textbox::verifyValidInput(sf::Event input) { //Function to verify is input is valid

	int charTyped = input.text.unicode;
	if (charTyped < 128) {
		if (textString.length() <= maxChars) {
			stringEdit(charTyped);
		}
		else if (textString.length() > 0 && charTyped == DELETE_KEY) {
			deleteChar();
		}
	}
}
void Textbox::stringEdit(int typedChar) {

	if (typedChar != DELETE_KEY && typedChar != ENTER_KEY && typedChar != ESCAPE_KEY) {

		if (wrapText(typedChar)) {
			if (!(typedChar == ' ')) {
				textString += typedChar;
				currentChars++;
				charCount++;
			}
		}
		else {
			textString += typedChar;
			currentChars++;
			charCount++;
		}
	}
	else if (typedChar == DELETE_KEY) {
		if (textString.length() > 0) {
			deleteChar();
			currentChars--;
		}
	}
	textbox.setString(textString);

}

bool Textbox::wrapText(int typedChar) {	

	currentPos += textbox.getCharacterSize();
	//currentPos = textbox.findCharacterPos(currentChars).x;
	std::cout << "Current length: " << currentPos << std::endl;
	std::cout << "Max: " << boundsBox.getPosition().x + boundsBox.getSize().x << std::endl;

	if ( currentPos > boundsBox.getPosition().x + boundsBox.getSize().x - (4 * textbox.getCharacterSize()) ){
		textString += '\n';
		charCount = 0;
		currentPos = 0;
		//std::cout << "after length: " << currentPos << std::endl;
		return true;
	}
	else {
		return false;
	}

}

void Textbox::deleteChar() {
	
	std::string newString = "";
	int i = 0;

	std::cout << '\n' << textString[textString.length() - 1] << std::endl;

	if (textString[textString.length() - 2] == '\n') {
		for (i; i < textString.length() - 2; i++) {	
			newString += textString[i];
		}
		currentPos = boundsBox.getPosition().x + boundsBox.getSize().x - (4 * textbox.getCharacterSize());
	}
	else {
		std::cout << "b4: " << currentPos << std::endl;
		for (i; i < textString.length() - 1; i++) {
			
			
			newString += textString[i];
		}
		currentPos -= textbox.getCharacterSize();
		std::cout << "after: " << currentPos << std::endl;
	}
	textString = newString;

}