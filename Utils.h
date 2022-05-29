#pragma once

#include <windows.h>
#include <process.h>
#include <iostream>


using namespace std;
class Point;

enum class ShipSize { Big = 4, Small = 2 };
enum class Direction { Up = 119, Down = 120, Right = 100, Left = 97, Stop = -1 };
enum class objectAsciiVal { 
	Wall1 = 45, 
	Wall2 = 124,
	HorizontalGhost = 36,
	verticalGhost = 33,
	WandringGhost = 37,
	ExitPoint = 47,
	LegendPoint = 38,
	BigShip = 35,
	SmallShip = 64,
	BlockLowestVal = 49 ,
	BlockHighestVal = 57};
enum class GameMode {regular = 0, record = 1,  loadRun = 2, loadSilence = 3};
enum class MenuChoice { Exit = 57, PlayNewGame = 49, ChooseAndPlaySingle = 50, changeColor = 55, showInstructions = 56, Failure = -1 };
enum class ValidKeys { Up = 119, Down = 120, Right = 100, Left = 97, SwitchToSmall = 115, SwitchToBig = 98, ESC = 27, EXIT = 57, Null = -1 };
constexpr static int hight = 25, width = 80;



void clrscr();
void hideCursor();
void gotoxy(int x, int y);
Point changePointByDirection(const Point& p,Direction dir);
