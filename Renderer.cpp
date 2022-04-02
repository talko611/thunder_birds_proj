#include "Renderer.h"

void Renderer::gotoxy(int x, int y) const
{
	HANDLE hConsoleOutput;
	COORD dwCursorPosition;
	std::cout.flush();
	dwCursorPosition.X = x;
	dwCursorPosition.Y = y;
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hConsoleOutput, dwCursorPosition);
}

void Renderer::erase()const
{
	for (auto& point : pointsToErase) {
		gotoxy(point.getY(), point.getX());
		printCell(' ');
	}
}

void Renderer::renderShip(const Ship& ship) const{
	char shipCharacter = ship.getShipCharacter();
	std::vector <Point> shipLocation = ship.getCurrLoc();
	for (auto& point : shipLocation) {
		gotoxy(point.getY(), point.getX());
		printCell(shipCharacter);
	}
 }

void Renderer::renderBlocks(const Block blocks[], int size) const{
	for (int i = 0; i < size; i++) {
		std::vector <Point> blockLocation = blocks[i].getCurrentLocation();
		for (auto& point : blockLocation) {
			gotoxy(point.getY(), point.getX());
			printCell((char)objectChars::Block);
		}
	}
}

void Renderer::addPointsToErase(const std::vector<Point>& points) {
	pointsToErase.insert(pointsToErase.end(), points.begin(), points.end());
}

void Renderer::printBord(const char bord[][width], int hight, int width) const
{
	for (int i = 0; i < hight; i++) {
		for (int j = 0; j < width; j++) {
			if (bord[i][j] == (char)objectAsciiVal::Wall1 || bord[i][j] == (char) objectAsciiVal::Wall2) {
				printCell((char)objectChars::Wall);
			}
			else if (bord[i][j] == (char)objectAsciiVal::Block) {
				printCell((char)objectChars::Block);
			}
			else if (bord[i][j] == (char)objectAsciiVal::ExitPoint) {
				printCell(' ');
			}
			else
			{
				printCell(bord[i][j]);
			}
		}
		std::cout << std::endl;
	}
}

void Renderer::printLegend(int lives, int time, int activeShip) const
{
	std::string const legend = "|     Lives:                 Time:                    Active Ship:           |\n"
	
							"------------------------------------------------------------------------------\0";
	gotoxy(0, 23);
	std::cout << legend;
	printLives(lives);
	printTime(time);
	printShipTurn(activeShip);
	
}

void Renderer::printTime(int time) const {
	gotoxy(34, 23);
	std::cout << "   ";
	gotoxy(34, 23);
	std::cout << time << std::endl;
}

void Renderer::printLives(int lives) const{
	gotoxy(12, 23);
	std::cout << lives << std::endl;
}

void Renderer::printShipTurn(int activeShip) const {
	gotoxy(67, 23);
	if (activeShip == 0) {
		std::cout << "Small" << std::endl;
	}
	else
	{
		std::cout << "Big  " << std::endl;
	}
}

void Renderer::renderNextMove(const Ship& ship, const Block blocks[], int size ,int time, int activeShip , bool isFinish) 
{
	erase();
	renderBlocks(blocks, size);
	if(!isFinish)
		renderShip(ship);
	printTime(time);
	printShipTurn(activeShip);
	pointsToErase.clear();
}

void Renderer::clearRow()const {
	gotoxy(1, 23);
	for (int i = 0; i < width - 1; i++) {
		std::cout << ' ';
	}
}

void Renderer::printPauseMessage() const{
	clearRow();
	gotoxy(12, 23);
	std::cout << "Game paused, press ESC again to continue or 9 to Exit";
}

void Renderer::printLosingMessage(int lives) const{
	clearRow();
	
	if (lives == 1) {
		gotoxy(28, 23);
		std::cout << "GAME OVER - YOU LOST";
	}
	else {
		gotoxy(20, 23);
		std::cout << "Ship died - you have " << --lives << " lives left";
	}
}

void Renderer::printWinningMessage()const {
	clearRow();
	gotoxy(20, 23);
	std::cout << "CONGRATULATIONS - YOU WON!";
}

void Renderer::printCell(char cellChar) const {
	if (this->color) {
		switch (cellChar)
		{
		case (char) objectAsciiVal::Wall1:
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), gray);
			std::cout << (char)objectChars::Wall;
			break;
		case (char)objectAsciiVal::Wall2:
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), gray);
			std::cout << (char)objectChars::Wall;
			break;
		case (char) objectAsciiVal::Block:
			system("color 02");
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), yellow);
			break;
		case (char) objectAsciiVal::BigShip:
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), red);
			std::cout << cellChar;
			break;
		case (char)objectAsciiVal::SmallShip:
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), dark_blue);
			std::cout << cellChar;
			break;
		default:
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), white);
			std::cout << cellChar;
			break;
		}
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), white);
	}
	else
	{
		std::cout << cellChar;
	}
}
