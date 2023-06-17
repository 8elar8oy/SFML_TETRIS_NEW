#pragma once
#include "settings.h"
#include "SFML/Graphics.hpp"
#include "tetramino.h"
#include "TextObj.h"
using namespace sf;// использование префикса sf библиотеки sfml
class Game {//класс ИГРА
private://доступно только внутри класса
	RenderWindow window;//окно игры

	Tetramino tetramino;//фигура тетриса

	Texture background;//текстура фона(начальная)
	Texture background2;//текстура фона(темная)
	Sprite background_sprite;//спрайт фона

	TextObj score_text;//текст счета

	Sprite gameover_sprite;//спрайт окна проигрыша
	Texture gameover_texture;//текстура окна проигрыша

	Sprite start_sprite;//спрайт окна начала игры
	Texture start_texture;//текстура окна начала игры
	int colorScore = 1;//счетчик каждого четвертого счета
	bool gameIsOver = false;//логическая функция проигрыша
	void checkEvents() {//функция проверки событий
		sf::Event event;
		while (window.pollEvent(event))
			if (event.type == Event::Closed) window.close();//если нажат крестик, окно сворачивается
	}
	void update() {//функция обновления
		tetramino.update();//вызов функции update у tetramino
		score_text.update(std::to_string(tetramino.getScore()));//вызов функции update у счета
		for (int i = 0; i < 10; i++)//проверка каждого блока в верхней линии
		{
			if (field[3][i]) {//если клетка занята, игра проиграна
				gameIsOver = true;
			}
		}
		deleteLine();//функция удаления линии клеток
	}
	void draw() {//функция отрисовки
		window.clear();//чистка окна
		window.draw(background_sprite);//отрисовка заднего фона
		window.draw(score_text.getText());//отрисовка счета
		tetramino.draw(window);//отрисовка фигуры тетриса
		window.display();//отображение на экране
	}
	void gameover() {//функция окна проигрыша
		window.draw(gameover_sprite);//отрисовка окна проигрыша
		window.display();//отображение окна проигрыша
	}
	void start() {//функция окна начала игры
		window.draw(start_sprite);//отрисовка окна начала
		window.display();//отображение окна начала
	}
	void darkMode() {//функция темного режима

		if (tetramino.getScore() % 4 == 0) {//если счет кратен 4 
			colorScore++;//счетчик каждого 4 счета увеличивается
			if (colorScore % 2 != 0) {//если счетчик каждого четвертого счета не кратен 2  
				background_sprite.setTexture(background);//оставляем старую текстуру фона
				tetramino.oldTexture();//оставляем старую текстуру фигруки тетриса
			}
			else if (colorScore % 2 == 0) {//если кратен 2
				background_sprite.setTexture(background2);//присваиваем новую текстуру фона
				tetramino.changeTexture();//присваиваем новую текстуру фигурки тетриса
			}
		}
	}
	void deleteLine() {//функция удаления линии
		//стирание линии
		int k = M - 1;//коэффицент k = последняя строка
		for (int i = M - 1; i > 0; i--)//проверка с конца поля
		{
			int count = 0;//счет закрашенных кубов
			for (int j = 0; j < N; j++)//проверка каждого блока в строке
			{
				if (field[i][j]) count++;//если элемент массива не 0
				field[k][j] = field[i][j];//присваивание проверяемой строке текущей строки
			}
			if (count < N) k--;//если не вся линия закрашена, коэффицент = следущей строке
			if (count == N) {

				tetramino.incScore();//если все закрашено, счет плюс 1
				darkMode();//функция темного режима
			}
		}
	}
public://доступно везде
	Game() :window(VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), WINDOW_TITLE), score_text(std::to_string(tetramino.getScore()), Vector2f{ 360,40 })//конструктор класса game
	{
		start_texture.loadFromFile(TEXTURE_START);//загрузка текстуры стартого окна из файла
		start_sprite.setTexture(start_texture);//присвоение спрайту стартого окна текстуры

		background.loadFromFile(TEXTURE_WINDOW);//загрузка текстуры начального фона из файла
		background2.loadFromFile(TEXTURE_WINDOW2);//загрузка текстуры темного фона игры из файла
		background_sprite.setTexture(background);//присвоение спрайту фона игры текстуры

		gameover_texture.loadFromFile(TEXTURE_GAMEOVER);//загрузка текстуры окна проигрыша из файла
		gameover_sprite.setTexture(gameover_texture);//присвоение спрайту окна проигрыша текстуры

		window.setFramerateLimit(FPS);//установка ограничения кадров 

	}

	void play() {//функция play
		while (window.isOpen())//пока открыто окно
		{
			while (!sf::Keyboard::isKeyPressed(Keyboard::Space)) {//пока не нажат пробел
				start();//окно старта
			}
			checkEvents();//проверка событий
			while (!gameIsOver) {//пока не проиграна игра

				update();//обновление
				draw();//отрисовка
			}
			while (gameIsOver) {//пока игра проиграна
				gameover();//окно проигрыша
				if (sf::Keyboard::isKeyPressed(Keyboard::Enter)) {//если нажат enter
					break;//прервать
				}
			}
			if (gameIsOver) {//если игра проиграна 
				break;//преравть основной цикл
			}
		}
	}
};