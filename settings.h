#pragma once
#include "SFML/Graphics.hpp"
const size_t WINDOW_HEIGHT = 720;
const size_t WINDOW_WIDTH = 360;
const std::string WINDOW_TITLE = "SFML_TETRIS";
const size_t FPS = 15;
const int M = 20; // высота игрового поля
const int N = 10; // ширина игрового поля
int field[M][N] = { 0 }; // игровое поле
// Массив фигурок-тетрамино
int figures[7][4] =
{
	1,3,5,7, // I
	2,4,5,7, // S
	3,5,4,6, // Z
	3,5,4,7, // T
	2,3,5,7, // L
	3,5,7,6, // J
	2,3,4,5, // O
};