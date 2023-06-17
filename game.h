#pragma once
#include "settings.h"
#include "SFML/Graphics.hpp"
#include "tetramino.h"
#include "TextObj.h"
using namespace sf;// ������������� �������� sf ���������� sfml
class Game {//����� ����
private://�������� ������ ������ ������
	RenderWindow window;//���� ����

	Tetramino tetramino;//������ �������

	Texture background;//�������� ����(���������)
	Texture background2;//�������� ����(������)
	Sprite background_sprite;//������ ����

	TextObj score_text;//����� �����

	Sprite gameover_sprite;//������ ���� ���������
	Texture gameover_texture;//�������� ���� ���������

	Sprite start_sprite;//������ ���� ������ ����
	Texture start_texture;//�������� ���� ������ ����
	int colorScore = 1;//������� ������� ���������� �����
	bool gameIsOver = false;//���������� ������� ���������
	void checkEvents() {//������� �������� �������
		sf::Event event;
		while (window.pollEvent(event))
			if (event.type == Event::Closed) window.close();//���� ����� �������, ���� �������������
	}
	void update() {//������� ����������
		tetramino.update();//����� ������� update � tetramino
		score_text.update(std::to_string(tetramino.getScore()));//����� ������� update � �����
		for (int i = 0; i < 10; i++)//�������� ������� ����� � ������� �����
		{
			if (field[3][i]) {//���� ������ ������, ���� ���������
				gameIsOver = true;
			}
		}
		deleteLine();//������� �������� ����� ������
	}
	void draw() {//������� ���������
		window.clear();//������ ����
		window.draw(background_sprite);//��������� ������� ����
		window.draw(score_text.getText());//��������� �����
		tetramino.draw(window);//��������� ������ �������
		window.display();//����������� �� ������
	}
	void gameover() {//������� ���� ���������
		window.draw(gameover_sprite);//��������� ���� ���������
		window.display();//����������� ���� ���������
	}
	void start() {//������� ���� ������ ����
		window.draw(start_sprite);//��������� ���� ������
		window.display();//����������� ���� ������
	}
	void darkMode() {//������� ������� ������

		if (tetramino.getScore() % 4 == 0) {//���� ���� ������ 4 
			colorScore++;//������� ������� 4 ����� �������������
			if (colorScore % 2 != 0) {//���� ������� ������� ���������� ����� �� ������ 2  
				background_sprite.setTexture(background);//��������� ������ �������� ����
				tetramino.oldTexture();//��������� ������ �������� ������� �������
			}
			else if (colorScore % 2 == 0) {//���� ������ 2
				background_sprite.setTexture(background2);//����������� ����� �������� ����
				tetramino.changeTexture();//����������� ����� �������� ������� �������
			}
		}
	}
	void deleteLine() {//������� �������� �����
		//�������� �����
		int k = M - 1;//���������� k = ��������� ������
		for (int i = M - 1; i > 0; i--)//�������� � ����� ����
		{
			int count = 0;//���� ����������� �����
			for (int j = 0; j < N; j++)//�������� ������� ����� � ������
			{
				if (field[i][j]) count++;//���� ������� ������� �� 0
				field[k][j] = field[i][j];//������������ ����������� ������ ������� ������
			}
			if (count < N) k--;//���� �� ��� ����� ���������, ���������� = �������� ������
			if (count == N) {

				tetramino.incScore();//���� ��� ���������, ���� ���� 1
				darkMode();//������� ������� ������
			}
		}
	}
public://�������� �����
	Game() :window(VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), WINDOW_TITLE), score_text(std::to_string(tetramino.getScore()), Vector2f{ 360,40 })//����������� ������ game
	{
		start_texture.loadFromFile(TEXTURE_START);//�������� �������� �������� ���� �� �����
		start_sprite.setTexture(start_texture);//���������� ������� �������� ���� ��������

		background.loadFromFile(TEXTURE_WINDOW);//�������� �������� ���������� ���� �� �����
		background2.loadFromFile(TEXTURE_WINDOW2);//�������� �������� ������� ���� ���� �� �����
		background_sprite.setTexture(background);//���������� ������� ���� ���� ��������

		gameover_texture.loadFromFile(TEXTURE_GAMEOVER);//�������� �������� ���� ��������� �� �����
		gameover_sprite.setTexture(gameover_texture);//���������� ������� ���� ��������� ��������

		window.setFramerateLimit(FPS);//��������� ����������� ������ 

	}

	void play() {//������� play
		while (window.isOpen())//���� ������� ����
		{
			while (!sf::Keyboard::isKeyPressed(Keyboard::Space)) {//���� �� ����� ������
				start();//���� ������
			}
			checkEvents();//�������� �������
			while (!gameIsOver) {//���� �� ��������� ����

				update();//����������
				draw();//���������
			}
			while (gameIsOver) {//���� ���� ���������
				gameover();//���� ���������
				if (sf::Keyboard::isKeyPressed(Keyboard::Enter)) {//���� ����� enter
					break;//��������
				}
			}
			if (gameIsOver) {//���� ���� ��������� 
				break;//�������� �������� ����
			}
		}
	}
};