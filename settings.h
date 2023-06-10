#pragma once
#include "SFML/Graphics.hpp"
const size_t WINDOW_HEIGHT = 720;
const size_t WINDOW_WIDTH = 468;
const std::string WINDOW_TITLE = "SFML_TETRIS";
std::string TEXTURE_TETRAMINO = "TETRISSFML.png";
std::string TEXTURE_TETRAMINO2 = "TETRISSFML2.png";
std::string TEXTURE_START = "START.png";
std::string TEXTURE_WINDOW = "WINDOW.png";
std::string TEXTURE_WINDOW2 = "WINDOW2.png";
std::string TEXTURE_GAMEOVER = "GAMEOVER.png";

const size_t FPS = 15;
const int M = 20;
const int N = 10;
int field[M][N] = { 0 };
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
