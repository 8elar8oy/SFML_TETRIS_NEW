#pragma once
#include "SFML/Graphics.hpp"
#include <time.h>
using namespace sf;
struct Point
{
	int x, y;
} pos[4], fpos[4];
class Tetramino {
private:
	sf::Sprite sprite;
	sf::Texture texture;
	sf::Texture texture1;

	int color; // ���� �������
	int speed_x = 0; // �������� ����������� ������� �� X
	int n;// ��� �������
	bool rotate = 0; // ������� ��������
	Clock clock, clock2; // �������� ��������
	float timer, timer2; // �������� ��������� ��������
	float delay = 0.5; // ���������� ������� �������
	int score = 0; // ���� ������
	
	
public:

	Tetramino() {
		srand(time(nullptr));
		texture.loadFromFile("TETRISSFML.png");
		texture1.loadFromFile("TETRISSFML2.png");
		sprite.setTexture(texture);
		color = 1 + rand() % 7;
		n = rand() % 7;
		// ������ ��� ���������
		if (pos[0].x == 0) { //���� ������ ��������(��������� ������� ������� ������)
			for (int i = 0; i < 4; i++) //��������� ������ ������� ������
			{
				pos[i].x = figures[n][i] % 2; //������������� ������� ������� ������� ������� �� ���� �� x
				pos[i].y = figures[n][i] / 2; //������������� ������� ������� ������� ������� �� ���� �� x

			}
			clock.restart(); // ������������� ������ ���������� �� ���������� ������� �������
			clock2.restart();  // ������������� ������ ���������� �� ���������� ������� ��������
		}

	}


	void update() {

		timer = clock.getElapsedTime().asSeconds();
		timer2 = clock2.getElapsedTime().asSeconds();
		if (Keyboard::isKeyPressed(Keyboard::Left)) {
			speed_x = -1;
		}
		if (Keyboard::isKeyPressed(Keyboard::Right)) {
			speed_x = 1;
		}
		if (Keyboard::isKeyPressed(Keyboard::Up)) {
			rotate = true;
		}
		if (Keyboard::isKeyPressed(Keyboard::Down)) {
			delay = 0.05;
		}
		for (int i = 0; i < 4; i++) {
			fpos[i] = pos[i];
			pos[i].x += speed_x;
		}
		if (outOfBorders()) {
			for (int i = 0; i < 4; i++)
			{
				pos[i] = fpos[i];

			}
		}
		if (rotate) {
			if (timer2 > 0.2) {
				int center_x = pos[1].x;
				int center_y = pos[1].y;
				for (int i = 0; i < 4; i++)
				{
					int x = pos[i].y - center_y; // y - y0
					int y = pos[i].x - center_x; // x - x0
					pos[i].x = center_x - x;
					pos[i].y = center_y + y;
				}
				if (outOfBorders()) {
					for (int i = 0; i < 4; i++)
					{
						pos[i] = fpos[i];
					}
				}
				clock2.restart();
			}

		}
		if (timer > delay) {

			for (int i = 0; i < 4; i++)
			{
				fpos[i] = pos[i];

				pos[i].y += 1;

			}
			if (outOfBorders()) {
				for (int i = 0; i < 4; i++) {
					pos[i] = fpos[i];
					field[pos[i].y][pos[i].x] = color;
				}
				color = 1 + rand() % 7;
				int n = rand() % 7;
				for (int i = 0; i < 4; i++)
				{
					pos[i].x = figures[n][i] % 2;
					pos[i].y = figures[n][i] / 2;
				}

			}
			clock.restart();

		}	
		if (score == 1) {
			sprite.setTexture(texture1);
			
		}
		
		
		int k = M - 1;
		for (int i = M - 1; i > 0; i--)
		{
			int count = 0;
			for (int j = 0; j < N; j++)
			{
				if (field[i][j]) count++;
				field[k][j] = field[i][j];
			}
			if (count < N) k--;
			if (count == N) score++;
		}
		speed_x = 0;
		rotate = 0;
		delay = 0.5;
	}


	void draw(sf::RenderWindow& window) {
		for (int i = 0; i < M; i++)
			for (int j = 0; j < N; j++)
			{
				if (field[i][j] == 0) continue;
				sprite.setTextureRect(IntRect(field[i][j] * 36, 0, 36, 36));
				sprite.setPosition(j * 36, i * 36);
				window.draw(sprite);
			}
		for (int i = 0; i < 4; i++)
		{
			// ������������� ���������
			sprite.setTextureRect(IntRect(color * 36, 0, 36, 36));
			// ������������� ������� ������� ������� ���������
			sprite.setPosition(pos[i].x * 36, pos[i].y * 36);
			// ��������� �������
			window.draw(sprite);
		}
	}
	bool outOfBorders()
	{
		for (int i = 0; i < 4; i++) {
			if (pos[i].x < 0 || pos[i].x >= N || pos[i].y >= M) return true;
			else if (field[pos[i].y][pos[i].x]) return true;
		}
		return false;
	}
	
	int getScore() {
		return score;
	}
	Sprite getSprite() {
		return sprite;
	}
	Texture getTexture() {
		return texture1;
	
	}
	

};