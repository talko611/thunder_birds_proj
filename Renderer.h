#pragma once
#include <vector>
#include <string>
#include "Ship.h"
#include "Block.h"
#include "Utils.h"


class Renderer
{
	std::vector<Point> pointsToErase;
	enum class objectChars{Wall = 176, Block = 178};
	bool color;
	enum concol
	{
		black = 0,
		dark_blue = 1,
		dark_green = 2,
		dark_aqua, dark_cyan = 3,
		dark_red = 4,
		dark_purple = 5, 
		dark_pink = 5, 
		dark_magenta = 5,
		dark_yellow = 6,
		dark_white = 7,
		gray = 8,
		blue = 9,
		green = 10,
		aqua = 11, 
		red = 12,
		purple = 13, 
		pink = 13, 
		magenta = 13,
		yellow = 14,
		white = 15
	};

	void printTime(int time) const;
	void printLives(int lives) const;
	void printShipTurn(int activeShip) const;
	void printCell(char cellChar) const;
	void erase()const;
	void renderShip(const Ship& ship) const;
	void renderBlocks(const Block blocks[], int size) const;
	

public:
	Renderer(bool _color): color(_color){}
	void gotoxy(int x, int y) const;
	void addPointsToErase(const std::vector<Point>& points);
	void printBord(const char bord[][80], int hight, int width) const;
	void printLegend(int lives, int time, int activeShip) const;
	void renderNextMove(const Ship& ship, const Block blocks[], int size , int time, int activeShip, bool isFinish);
	void printPauseMessage() const;
	void printWinningMessage()const;
	void printLosingMessage(int lives) const;
	void clearRow() const;
};
