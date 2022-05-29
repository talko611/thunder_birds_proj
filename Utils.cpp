#include "Utils.h"
#include "Point.h"


void clrscr()
{
	system("cls");
}

void hideCursor()
{
	HANDLE myconsole = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO CURSOR;
	CURSOR.dwSize = 1;
	CURSOR.bVisible = FALSE;
	SetConsoleCursorInfo(myconsole, &CURSOR);
}

void gotoxy(int x, int y) 
{
	HANDLE hConsoleOutput;
	COORD dwCursorPosition;
	std::cout.flush();
	dwCursorPosition.X = x;
	dwCursorPosition.Y = y;
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hConsoleOutput, dwCursorPosition);
}

Point changePointByDirection(const Point& p, Direction dir) {
	int x = p.getX();
	int y = p.getY();

	switch (dir) {
	case Direction::Down:
		return Point(++x, y);
	case Direction::Up:
		return Point(--x, y);
	case Direction::Left:
		return Point(x, --y);
	case Direction::Right:
		return Point(x, ++y);
	default:
		return Point();
	}
}
