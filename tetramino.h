#pragma once
#include "SFML/Graphics.hpp"
#include <time.h>
using namespace sf;
struct Point//структура точки
{
	int x, y;//переменные x,y
} pos[4], fpos[4];//массивы структуры
class Tetramino {//класс фигур тетриса
private://доступно только внутри класса
	sf::Sprite sprite;//спрайт
	sf::Texture texture;//текстура
	sf::Texture texture1;//темная текстура
	int color; //цвет фигуры
	int speed_x = 0; //скорость движения
	int n;//тип фигуры
	bool isRotate = 0; //логическая функция поврота фигуры
	Clock clock, clock2; //создание часов
	float timer, timer2; //создание таймеров для счета времени
	float delay = 0.5; //задержка падения фигуры
	int score = 0; //счет игрока
public://доступно везде
	Tetramino() {//конструктор фигуры тетриса
		srand(time(nullptr));//функция генерации случайных чисел
		texture.loadFromFile(TEXTURE_TETRAMINO);//загурзка текстуры из файла
		texture1.loadFromFile(TEXTURE_TETRAMINO2);//загрузка темной текстуры из файла
		sprite.setTexture(texture);//установка текстуры в спрайт
		setType();
		clock.restart(); //перезапуск первых часов
		clock2.restart();  //перезапуск вторых часов
	}
	void update() {//функция update

		timer = clock.getElapsedTime().asSeconds();//присваивание первому таймеру времени часов в секунадх 
		timer2 = clock2.getElapsedTime().asSeconds();//присваивание второму таймеру времени часов в секунадх 
		checkButtons();
		for (int i = 0; i < 4; i++) {
			fpos[i] = pos[i];//сохранение предыдущей позиции блока
			pos[i].x += speed_x;//движение по x
		}
		returnPos();
		rotate();

		if (timer > delay) {//задерка движения вниз

			for (int i = 0; i < 4; i++)
			{
				fpos[i] = pos[i];//сохранение предыдущей позиции блока
				pos[i].y += 1;//движение вниз

			}
			if (outOfBorders()) {//проверка выхода за границы
				for (int i = 0; i < 4; i++) {
					pos[i] = fpos[i];//сохранение предыдущей позиции блока
					field[pos[i].y][pos[i].x] = color;//присваивание цвета ячейке двумерного массива
				}
				setType();//установка позиции и цвета по форме фигуры
			}
			clock.restart();//перезапуск первых часов

		}
		if (score >= 10) {//провера счета
			sprite.setTexture(texture1);//ночной режим игры

		}
		deleteLine();//стирание линии
		speed_x = 0;//скорость равна нулю
		isRotate = 0;// поворот равен false
		delay = 0.5;//задержка падения начальная
	}
	void changeTexture() {
		texture = texture1;
	}
	void deleteLine() {
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
			if (count == N) score++;//если все закрашено, счет плюс 1
		}
	}
	void rotate() {
		if (isRotate) {//поворот фигуры
			if (timer2 > 0.2) {//задержка поворота 
				int center_x = pos[1].x;//центр фигуры по х
				int center_y = pos[1].y;//центр фигуры по у
				for (int i = 0; i < 4; i++)
				{
					int x = pos[i].y - center_y; // y - y0
					int y = pos[i].x - center_x; // x - x0
					//присваивание новых позиций после поворота каждому блоку
					pos[i].x = center_x - x;
					pos[i].y = center_y + y;
				}
				returnPos();
				clock2.restart();//презапуск вторых часов
			}

		}
	}
	void checkButtons() {
		//проверка нажатий клавиш
		if (Keyboard::isKeyPressed(Keyboard::Left)) {
			speed_x = -1;//движение влево
		}
		if (Keyboard::isKeyPressed(Keyboard::Right)) {
			speed_x = 1;//движение вправо
		}
		if (Keyboard::isKeyPressed(Keyboard::Up)) {
			isRotate = true;//выполняется поворот
		}
		if (Keyboard::isKeyPressed(Keyboard::Down)) {
			delay = 0.05;//ускорение падения
		}
	}
	void setType() {
		color = 1 + rand() % 7;//случайный цвет новой фигуры
		int n = rand() % 7;//случайный тип новой фигуры
		for (int i = 0; i < 4; i++) //цикл for 4 итерации(фигура из 4 блоков)
		{
			pos[i].x = figures[n][i] % 2; //установка позиции кубика фигуры из локальной в глобальную по x
			pos[i].y = figures[n][i] / 2; //установка позиции кубика фигуры из локальной в глобальную по y

		}

	}
	void returnPos() {
		if (outOfBorders()) {//проверка выхода за границы
			for (int i = 0; i < 4; i++)
			{
				pos[i] = fpos[i];//вернуть старую позицию
			}
		}
	}
	void draw(sf::RenderWindow& window) {//функция отрисовки
		for (int i = 0; i < M; i++)//проверка строк
			for (int j = 0; j < N; j++)//проверка кубиков строки
			{
				if (field[i][j] == 0) continue;//если куб пустой, пропуск итерации
				//иначе
				sprite.setTextureRect(IntRect(field[i][j] * 36, 0, 36, 36));//задание цвета 
				sprite.setPosition(j * 36, i * 36);//задание позиции
				window.draw(sprite);//отрисовка и фиксация упавшей фигуры
			}
		for (int i = 0; i < 4; i++)//отрисовка новой фигуры
		{
			sprite.setTextureRect(IntRect(color * 36, 0, 36, 36));//установка цвета
			sprite.setPosition(pos[i].x * 36, pos[i].y * 36);//установка позиции
			window.draw(sprite);//отрисовка
		}
	}
	bool outOfBorders()//логическая функция за пределами экрана
	{
		for (int i = 0; i < 4; i++) {//проверка каждого блока
			if (pos[i].x < 0 || pos[i].x >= N || pos[i].y >= M) return true;//если выбло за груницы вернуть true
			else if (field[pos[i].y][pos[i].x]) return true;//если элемент двумерного массива поля не равен нулю(пустой), тоже вернуть true
		}
		return false;//иначе false
	}
	int getScore() {//геттер счета
		return score;
	}
	Sprite getSprite() {// геттер спрайта
		return sprite;
	}
	Texture getTexture() {//геттер текстуры
		return texture1;

	}
};