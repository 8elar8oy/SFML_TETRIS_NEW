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
	Sprite background_sprite;
	Texture scorebg;
	Sprite score_sprite;
	TextObj score_text;
	TextObj gameover_text;
	FloatRect text_size = gameover_text.getText().getGlobalBounds();
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
			if (field[1][i]) {
				gameIsOver = true;
				//break;
				
				//window.close();
			}

		}
		
	}

	void draw() {
	
		window.clear(Color::White);
		window.draw(background_sprite);
		window.draw(score_sprite);
		window.draw(score_text.getText());
		tetramino.draw(window);
		window.display();
	}
	void gameover() {
		window.clear(Color::Black);
		window.draw(gameover_text.getText());
		window.display();
	}
public:
	Game() :window(VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), WINDOW_TITLE), score_text(std::to_string(tetramino.getScore())),gameover_text("GAME OVER")
	{
		gameover_text.getText().setPosition(Vector2f((WINDOW_WIDTH - text_size.width) / 2, (WINDOW_HEIGHT - text_size.height) / 2));
		score_text.getText().setPosition(Vector2f{ 360,40 });
		background.loadFromFile("WINDOW.png");
		background_sprite.setTexture(background);
		scorebg.loadFromFile("SCORE.png");
		score_sprite.setTexture(scorebg);
		score_sprite.setPosition(360, 0);
		window.setFramerateLimit(FPS);
		
	}

	void play() {
		while (window.isOpen() )
		{
			checkEvents();
			while (!gameIsOver) {
				
				update();
				draw();
			
			}
				
			
			gameover();
			
		}
	}
};