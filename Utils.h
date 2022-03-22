#pragma once

#include <windows.h>
#include <process.h>
#include <iostream>


enum class Direction { Up = 119, Down = 120, Right = 100, Left = 97, Stop = -1 };
enum class ShipSize { Big = 4, Small = 2 };
enum class SwitchKeys {SwitchToSmall = 115, SwitchToBig = 98};


void gotoxy(int x, int y);
void clrscr();
void hideCursor();