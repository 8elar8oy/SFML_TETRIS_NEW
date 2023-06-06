#pragma once
#include "settings.h"
#include "SFML/Graphics.hpp"
#include "tetramino.h"
#include "TextObj.h"
using namespace sf;
class Game {
private:
	RenderWindow window;
	
	Tetramino tetramino;
	
	Texture background;
	Texture background1;
	Sprite background_sprite;

	TextObj score_text;
	
	Sprite gameover_sprite;
	Texture gameover_texture;
	
	Sprite start_sprite;
	Texture start_texture;

	bool gameIsOver = false;
	void checkEvents() {
		sf::Event event;
		while (window.pollEvent(event))
			if (event.type == Event::Closed) window.close();
	}
	void update() {
		tetramino.update();
		score_text.update(std::to_string(tetramino.getScore()));
		for (int i = 0; i < 10; i++)
		{
			if (field[2][i]) {
				gameIsOver = true;
			}
		}
		darkMode();
		
	}
	void draw() {
		window.clear();
		window.draw(background_sprite);
		window.draw(score_text.getText());
		tetramino.draw(window);
		window.display();
	}
	void gameover() {
		window.draw(gameover_sprite);
		window.display();

	}
	void start() {
		window.draw(start_sprite);
		window.display();

	}
	void darkMode() {
		if (tetramino.getScore() >= 1) {
			background_sprite.setTexture(background1);
			tetramino.changeTexture();
		}
	}
public:
	Game() :window(VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), WINDOW_TITLE), score_text(std::to_string(tetramino.getScore()), Vector2f{ 360,40 })
	{
		start_texture.loadFromFile("START.png");
		start_sprite.setTexture(start_texture);

		background.loadFromFile("WINDOW.png");
		background1.loadFromFile("WINDOW2.png");
		background_sprite.setTexture(background);

		gameover_texture.loadFromFile("GAMEOVER.png");
		gameover_sprite.setTexture(gameover_texture);

		window.setFramerateLimit(FPS);

	}

	void play() {
		while (window.isOpen())
		{
			while (!sf::Keyboard::isKeyPressed(Keyboard::Space)) {
				start();
			}
			checkEvents();
			while (!gameIsOver) {

				update();
				draw();
			}
			while (gameIsOver) {
				gameover();
				if (sf::Keyboard::isKeyPressed(Keyboard::Enter)) {
					break;
				}
			}
			if (gameIsOver) {
				break;
			}
		}
	}
};