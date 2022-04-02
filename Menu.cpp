#include "Menu.h"

void Menu::printMenu() const{
	for (int i = 0; i < seperateLineLen; i++) {
		std::cout << '-';
	}
	std::cout << std::endl;
	std::cout << "WLECOME TO THUNDERBIRDS GAME !" << std::endl;
	for (int i = 0; i < seperateLineLen; i++) {
		std::cout << '-';
	}
	std::cout << std::endl;
	std::cout << "Please enter your choice" << std::endl;
	std::cout << "1 - Start new game" << std::endl;
	std::cout << "7 - Enable/Disable colors" << std::endl;
	std::cout << "8 - Present instructions and keys" << std::endl;
	std::cout << "9 - Exit game" << std::endl;
}

void Menu::printInstructions() const
{
	
	for (int i = 0; i < seperateLineLen; i++) {
		std::cout << '-';
	}
	std::cout << std::endl;
	std::cout << "INSTRUCTIONS" << std::endl;
	for (int i = 0; i < seperateLineLen; i++) {
		std::cout << '-';
	}
	std::cout << std::endl;
	std::cout << "The perpose of the game is to get to the exit point with both ships\nbefore the time is over." << std::endl;
	for (int i = 0; i < seperateLineLen; i++) {
		std::cout << '-';
	}
	std::cout << std::endl << "KEYS" << std::endl;
	for (int i = 0; i < seperateLineLen; i++) {
		std::cout << '-';
	}
	std::cout << std::endl;
	std::cout << "LEFT - A" << std::endl;
	std::cout << "RIGHT - D" << std::endl;
	std::cout << "UP - W" << std::endl;
	std::cout << "DOWN - X" << std::endl;
	std::cout << "SWITCH TO BIG SHIP - B" << std::endl;
	std::cout << "SWITCH TO SMALL SHIP - S" << std::endl;
	std::cout << std::endl << "Press B to return to menu" << std::endl;
	
	char choice = 0;
	while (choice != 'b') {
		if (_kbhit()) {
			choice = tolower(_getch());
			if (choice == 'b')
				break;
		}
	}
	clrscr();
}

void Menu::changeColorStatus() {
	char choice = 0;
	if (this->color) {
		std::cout << "Colors are enable" << std::endl;
	}
	else
	{
		std::cout << "Colors are disable" << std::endl;
	}
	std::cout << "Press Y to change state" << std::endl << "Press B to return to menu" << std::endl;

	while (choice != 'b') {
		
		if (_kbhit()) {
			choice = tolower(_getch());
			if (choice == 'y') {
				this->color = !this->color;
				clrscr();
				if (this->color) {
					std::cout << "Colors are enable" << std::endl;
				}
				else
				{
					std::cout << "Colors are disable" << std::endl;
				}
				std::cout << "Press Y to change state" << std::endl << "Press B to return to menu" << std::endl;
			}
		}
	}
}

void Menu::getUserChoice() {
	int choice = 0;
	printMenu();
	while (choice != validChoic::Exit) {
		if (_kbhit()) {
			choice = _getch();
			if (choice == validChoic::Play) {
				clrscr();
				Game newGame(this->color);
				newGame.startGame();
				clrscr();
				printMenu();
			}
			else if (choice == validChoic::changeColor) {
				clrscr();
				changeColorStatus();
				clrscr();
				printMenu();
			}
			else if (choice == validChoic::showInstructions) {
				clrscr();
				printInstructions();
				clrscr();
				printMenu();
			}
		}
	}
	clrscr();
	std::cout << "Thanks for playing !" << std::endl << "GOODBYE:)";
}