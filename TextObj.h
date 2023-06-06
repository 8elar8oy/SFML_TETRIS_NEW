#pragma once
#include "windows.h"
#include "settings.h"

class TextObj {//класс текста
private://доступно только внутри класса
	//свойства класса
	sf::Font font;//шрифт
	sf::Text text;//текст
public://доступно из всех частей программы
	TextObj(std::string str, sf::Vector2f pos) {//конструктор класса
		font.loadFromFile("Font.ttf");//загрузка шрифта из файла
		text.setString(str);//загрузка из строки в текст
		text.setFont(font);//установка шрифта
		text.setCharacterSize(50);//размер текста
		text.setPosition(pos);//позиция текста

	}
	void update(std::string str) {//метод класса(функция обновление текста)
		text.setString(str);
	}

	sf::Text getText() { return text; }//геттер текста(получить из private)

};