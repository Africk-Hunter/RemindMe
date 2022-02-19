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
	setFont(nFont);
	setSize(nSize);
	setPosition(nPos);
	currentPos = textbox.getGlobalBounds().left;
	maxChars = charLim;
	lineLimit = sizeX / charSize; // How many characters can fit on a line
	charCount = 0; // How many chars on the current line
	currentChars = 0;
	isSelected = false;

}

void Textbox::reverseSelectState() {
	isSelected = !isSelected;
}
bool Textbox::getSelectionState() {
	return isSelected;
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
	sizeX = nSize.x;
	sizeY = nSize.y;
}
void Textbox::setFont(sf::Font& font) {
	textbox.setFont(font);
}
void Textbox::setPosition(sf::Vector2f pos) {
	textbox.setPosition(pos);
}

void Textbox::drawTo(sf::RenderWindow& window) {
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
			std::cout << "Current length: " << currentPos<< std::endl;
			std::cout << "Max: " << textbox.getGlobalBounds().left + sizeX << std::endl;
			/*
			if (currentPos - textbox.getCharacterSize() < textbox.getGlobalBounds().left) {
				currentPos = textbox.getGlobalBounds().left + sizeX;
			}
			else {
				currentPos -= textbox.getCharacterSize();
			}
			*/
			currentChars--;
		}
	}
	textbox.setString(textString);

}

bool Textbox::wrapText(int typedChar) {

	//if (charCount >= lineLimit) { //If the amount of characters on a line has reached the limit
	//std::cout << "Current length: " << currentPos + textbox.getCharacterSize() << std::endl;
//	std::cout << "Max: " << textbox.getGlobalBounds().left + sizeX << std::endl;

	currentPos += textbox.getCharacterSize();

	if ( currentPos >= textbox.getGlobalBounds().left + sizeX || charCount > maxChars ){
		textString += '\n';
		charCount = 0;
		currentPos = textbox.getGlobalBounds().left;
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
		currentPos = textbox.getGlobalBounds().left + sizeX;
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
	
	/*
	
	
	std::string t = textStream.str();
	std::string newText = "";

	int i;
	for (i = 0; i < (t.length() - 1); i++) {
		newText += t[i];
	}
	textStream.str("");
	textStream << newText;
	textbox.setString(textStream.str());
	if (newText[i - 1] == '\n') {
		charCount = (lineLimit + 1);
	}
	else {
		charCount -= 1;
	}
	*/
}