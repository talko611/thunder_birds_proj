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

void Renderer::printBord(char** bord) const
{
	for (int i = 0; i < hight; i++) {
		for (int j = 0; j < width; j++) {
			if (bord[i][j] >= '1' && bord[i][j] <= '9') {
				printCell((char)objectChars::Block);
			}
			else if (bord[i][j] == (char)objectAsciiVal::ExitPoint || bord[i][j] == (char)objectAsciiVal::LegendPoint) {
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

void Renderer::printBord(char bord[][width]) const
{
	for (int i = 0; i < hight; i++) {
		for (int j = 0; j < width; j++) {
			if (bord[i][j] >= '1' && bord[i][j] <= '9') {
				printCell((char)objectChars::Block);
			}
			else if (bord[i][j] == (char)objectAsciiVal::ExitPoint || bord[i][j] == (char) objectAsciiVal::LegendPoint) {
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
	std::string const legend = "     Lives:                 Time:                    Active Ship:           \0";
	gotoxy(this->legendPosition.getY(), this->legendPosition.getX());
	std::cout << legend;
	printLives(lives);
	printTime(time);
	printShipTurn(activeShip);
	
}

void Renderer::printTime(int time) const {
	int x = this->legendPosition.getX();
	int y = this->legendPosition.getY() + lenFromStartLegend::Time;
	gotoxy(y, x);
	std::cout << "   ";
	gotoxy(y, x);
	std::cout << time << std::endl;
}

void Renderer::printLives(int lives) const{
	int x = this->legendPosition.getX();
	int y = this->legendPosition.getY() + lenFromStartLegend::Lives;
	gotoxy(y, x);
	std::cout << lives << std::endl;
}

void Renderer::printShipTurn(int activeShip) const {
	int x = this->legendPosition.getX();
	int y = this->legendPosition.getY() + lenFromStartLegend::ActiveShip;
	gotoxy(y, x);
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
			cout << (char)objectChars::Wall;
			break;
		case (char)objectAsciiVal::Wall2:
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), gray);
			cout << (char)objectChars::Wall;
			break;
		case (char) objectChars::Block:
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), yellow);
			cout << cellChar;
			break;
		case (char) objectAsciiVal::BigShip:
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), red);
			cout << cellChar;
			break;
		case (char)objectAsciiVal::SmallShip:
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), dark_blue);
			cout << cellChar;
			break;
		case(char) objectAsciiVal::Goast:
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), magenta);
			cout << cellChar;
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

void Renderer::setLegendPosition(int x, int y) { this->legendPosition.set(x, y);}

void Renderer::changeColorMode() { this->color = !this->color; }

bool Renderer::isColor() const { return this->color; }
