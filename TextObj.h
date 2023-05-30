#pragma once
#include "windows.h"
#include "settings.h"

class TextObj {
private:
	sf::Font font;
	sf::Text text;
	sf::FloatRect size = text.getGlobalBounds();
public:
	TextObj(std::string str,sf::Vector2f pos) {
		font.loadFromFile("Font.ttf");
		text.setString(str);
		text.setFont(font);
		text.setCharacterSize(40);
		text.setPosition(pos);

	}
	void update(std::string str) {
		text.setString(str);
	}

	sf::Text getText() { return text; }
	sf::FloatRect getZize() { return size; }

};