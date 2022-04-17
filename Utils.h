#pragma once

#include <windows.h>
#include <process.h>
#include <iostream>

using namespace std;

enum class ShipSize { Big = 4, Small = 2 };
enum class Direction { Up = 119, Down = 120, Right = 100, Left = 97, Stop = -1 };
enum class objectAsciiVal { Wall1 = 45, Wall2 = 124 , Goast = 36, ExitPoint = 33,LegendPoint = 38,  BigShip = 35, SmallShip = 64};
constexpr static int hight = 25, width = 80;


void clrscr();
void hideCursor();
void gotoxy(int x, int y);
