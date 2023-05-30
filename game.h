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
			}
		}
	}

	void draw() {
	
		window.clear();
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
	Game() :window(VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), WINDOW_TITLE), score_text(std::to_string(tetramino.getScore()),Vector2f{ 360,40 }), gameover_text("GAME OVER",Vector2f((WINDOW_WIDTH - gameover_text.getZize().width)/2, (WINDOW_HEIGHT - gameover_text.getZize().height)/2 ))
	{
		
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