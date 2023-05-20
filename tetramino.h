#pragma once
#include "SFML/Graphics.hpp"
using namespace sf;

class Tetramino {
private:
	sf::Sprite sprite;
	sf::Texture texture;
	int pos_x[4];
	int pos_y[4];
	int color;
	int speed_x = 0;
	int n = 3;
	bool rotate = 0;
	Clock clock;
	float timer = 0, delay = 0.5;
	float time1;
public:
	
	Tetramino() {
		srand(time(nullptr));
		

		
		texture.loadFromFile("TETRISSFML.png");
		sprite.setTexture(texture);
		color = rand() % 7;
		 // задаем тип тетрамино
		for (int i = 0; i < 4; i++)
		{
			pos_x[i] = figures[n][i] % 2;
			pos_y[i] = figures[n][i] / 2;
			
		}
		
	}


	void update() {
		float time1 = clock.getElapsedTime().asSeconds();
		clock.restart();
		timer += time1;
		if (Keyboard::isKeyPressed(Keyboard::Left)) {
			speed_x = -1;
		}
		if (Keyboard::isKeyPressed(Keyboard::Right)) {
			speed_x = 1;
		}
		if (Keyboard::isKeyPressed(Keyboard::Up)) {
			rotate = true;
		}
		for (int i = 0; i < 4; i++) pos_x[i] += speed_x;
		if (rotate) {
			int center_x = pos_x[1];
			int center_y = pos_y[1];
			for (int i = 0; i < 4; i++)
			{
				int x = pos_y[i] - center_y; // y - y0
				int y = pos_x[i] - center_x; // x - x0
				pos_x[i] = center_x - x;
				pos_y[i] = center_y + y;
			}
		
		}
		if (timer > delay ) {
			for (int i = 0; i < 4; i++)
			{
				pos_y[i] += 1;

			}
			timer = 0;
		}
		speed_x = 0;
		rotate = 0;
	}
	

	void draw(sf::RenderWindow& window) {
		for (int i = 0; i < 4; i++)
		{
			sprite.setPosition(pos_x[i] * 36, pos_y[i] * 36);
			sprite.setTextureRect(IntRect(0+36*color, 0, 36, 36));
			window.draw(sprite);
		}
	}


};