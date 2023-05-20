#pragma once
#include "settings.h"
#include "SFML/Graphics.hpp"
#include "tetramino.h"
using namespace sf;
class Game {
private:
	RenderWindow window;
	Tetramino tetramino;
	void checkEvents() {
		sf::Event event;
		while (window.pollEvent(event))
			if (event.type == Event::Closed) window.close();
	}
	void update() {
		tetramino.update();
	}
	
	void draw() {
		window.clear(Color::White);
		tetramino.draw(window);
		window.display();
	}
public:
	Game() :window(VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), WINDOW_TITLE)
	{

		window.setFramerateLimit(FPS);
	}

	void play() {
		while (window.isOpen())
		{
			checkEvents();
			update();
			
			draw();
		}
	}
};