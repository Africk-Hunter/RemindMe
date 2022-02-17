#include "Textbox.h"
#include <sstream>

Textbox::Textbox() { 

	limit = 0;
	lineLimit = 0;
	charCount = 0;
	sizeY = 0;
	sizeX = 0;
	isLimitReached = false;

}

Textbox::Textbox(int charSize, int charLim, sf::Vector2f nSize, bool limReached, sf::Color textBoxColor) {

	textbox.setCharacterSize(charSize);
	textbox.setFillColor(textBoxColor);
	isLimitReached = limReached;
	limit = charLim;
	setSize(nSize);
	lineLimit = sizeX / charSize;
	charCount = 0;

}

int Textbox::getSizeX() {
	return sizeX;
}
int Textbox::getsizeY() {
	return sizeY;
}
bool Textbox::getIsLimitReached() {
	return isLimitReached;
}
int Textbox::getLimit() {
	return limit;
}
void Textbox::setCharSize(int nSize) {
	textbox.setCharacterSize(nSize);
}
void Textbox::setIsLimitReached(bool limReached) {
	isLimitReached = limReached;
}
void Textbox::setLimit(int size) {
	limit = size;
}
void Textbox::setSize(sf::Vector2f nSize) {
	sizeX = nSize.x;
	sizeY = nSize.y;
}
void Textbox::setFont(sf::Font& font) {
	textbox.setFont(font);
}
void Textbox::drawTo(sf::RenderWindow& window) {
	window.draw(textbox);
}
void Textbox::typedOn(sf::Event input) {

	int charTyped = input.text.unicode;
	if (charTyped < 128) {
		if (textStream.str().length() <= limit) {
			keyboardInput(charTyped);
		}
		else if (textStream.str().length() > limit && charTyped == DELETE_KEY) {
			deleteChar();
		}
	}
}
void Textbox::keyboardInput(int typedChar) {
	if (typedChar != DELETE_KEY && typedChar != ENTER_KEY && typedChar != ESCAPE_KEY) {

		if (!wrapText(typedChar)) {
			textStream << static_cast<char>(typedChar);
		}
		charCount++;
	}
	else if (typedChar == DELETE_KEY) {
		if (textStream.str().length() > 0) {
			deleteChar();
		}
	}
	textbox.setString(textStream.str() + "_");
}

void Textbox::setPosition(sf::Vector2f pos) {
	textbox.setPosition(pos);
}

bool Textbox::wrapText(int typedChar) {

	int stringLen = textStream.str().length();
	std::string temp = "";
	std::string t = textStream.str();
	std::string lastWord = "";
	std::string finalString = "";
	bool spaceOrNot = false;
	int wordLenTracker = 0;

	if ((charCount >= lineLimit)) {
		if (t[stringLen] != 32) {
			spaceOrNot = true;
			for (int i = stringLen; t[i] != 32; i--) {
				temp += t[i];
				wordLenTracker++;
			}
			for (int j = wordLenTracker; j > 0; j--) {
				if (temp[j] != '\0') {
					lastWord += temp[j];
				}

			}
			for (int i = 0; i < (t.length()) - wordLenTracker; i++) {
				finalString += t[i];
			}
			for (int i = 0; i < wordLenTracker; i++) {
				finalString += " ";
			}
		}
		textStream.str("");
		textStream << finalString;
		textStream << "\n";
		textStream << lastWord;
		charCount = wordLenTracker;
	}
	return spaceOrNot;
}


void Textbox::deleteChar() {
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

}