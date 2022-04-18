#pragma once
#include <vector>
#include <string>
#include "Utils.h"
#include "Ship.h"
#include "Block.h"
#include "Utils.h"


class Renderer
{
	
	vector<Point> pointsToErase;
	vector<Point> blockToPrint;
	vector<Point> goastsToPrint;
	bool color;
	Point legendPosition;
	enum class objectChars { Wall = 176, Block = 178 };
	enum lenFromStartLegend{Lives = 11, Time = 33, ActiveShip= 65 };
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
	void addPointsToErase(const vector<Point>& points);
	void addPointToErase(const Point& point);
	void addPointsOfBlock(const vector<Point>& points);
	void addPointsOfGoast(const Point& point);
	void printBord(char** bord) const;
	void Renderer::printBord(char bord[][width]) const;
	void printLegend(int lives, int time, int activeShip) const;
	void renderNextMove(const Ship& ship, const Block blocks[], int size , int time, int activeShip, bool isFinish);
	void printPauseMessage() const;
	void printWinningMessage()const;
	void printLosingMessage(int lives) const;
	void clearRow() const;
	void setLegendPosition(int x, int y);
	void changeColorMode();
	bool isColor() const;
	
};

