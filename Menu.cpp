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
	std::cout << "2 - Choose and play single bord" << std::endl;
	std::cout << "7 - Enable/Disable colors" << std::endl;
	std::cout << "8 - Present instructions and keys" << std::endl;
	std::cout << "9 - Exit game" << std::endl;
}

void Menu::printInstructions() const
{
	clrscr();
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

void Menu::changeColorStatus(Renderer& renderer) const{
	char choice = 0;
	clrscr();
	if (renderer.isColor()) {
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
				renderer.changeColorMode();
				clrscr();
				if (renderer.isColor()) {
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
	clrscr();
}

MenuChoice Menu::getUserChoice(Bord& bord, FileInputOutput& inOut, Renderer& renderer) {
	int choice = 0;
	try {
		printMenu();
		while (true) {
			if (_kbhit()) {
				choice = tolower(_getch());
				switch (choice)
				{
				case (int)MenuChoice::PlayNewGame:
					inOut.readScreen(bord, 0);
					return MenuChoice::PlayNewGame;
				case (int)MenuChoice::ChooseAndPlaySingle:
					if (this->playSingleScreen(bord, inOut, renderer)) {
						return MenuChoice::ChooseAndPlaySingle;
					}
					clrscr();
					this->printMenu();
					break;
				case (int)MenuChoice::changeColor:
					this->changeColorStatus(renderer);
					clrscr();
					this->printMenu();
					break;
				case (int)MenuChoice::showInstructions:
					this->printInstructions();
					clrscr();
					this->printMenu();
					break;
				case (int)MenuChoice::Exit:
					return MenuChoice::Exit;
				default:
					break;
				}
			}
		}
	}
	catch (ios_base::failure& e) {
		clrscr();
		cout << "Something went wrong , Cannot start game..." << endl;
		Sleep(2000);
		return MenuChoice::Exit;
	}
}

bool Menu::playSingleScreen(Bord& bord, FileInputOutput& inOut, Renderer& renderer) 
{
	char choice = 0;
	int screenNum = inOut.getCurrentFileNum();
	int selectedScreen = 0;
	bool isSelected = true;
		
	clrscr();
	inOut.readScreen(bord, screenNum);
	cout << bord;
	renderer.printBord(bord.getBord());
	cout << "Screen is selected" << endl;
	cout << "Press P to start game with the current selected screen , N for next screen or B to return to menu";

		while (choice != 'b') {
			if (_kbhit()) {
				choice = tolower(_getch());
				if (choice == 'n') {
					isSelected = false;
					clrscr();
					screenNum = (screenNum + 1) % 3;
					inOut.readScreen(bord, screenNum);
					cout << bord;
					renderer.printBord(bord.getBord());

					if (screenNum == selectedScreen) {
						isSelected = true;
						cout << "Screen is selected" << endl;
						cout << "Press P to Play ,Press N for next screen or B to return to menu";
					}
					else {
						cout << "Press P to start game with the current selected screen \nPress Y to select screen, Press N for next screen or B to return to menu " << endl;
					}
				}
				else if (choice == 'y' && !isSelected) {
					isSelected = true;
					selectedScreen = screenNum;
					inOut.setCurrentInputFileNum(screenNum);
					cout << "Screen is selected" << endl;
					cout << "Press P to start game ,press N for next screen or B to return to menu";
				}
				else if (choice == 'p') {
					inOut.readScreen(bord, selectedScreen);
					clrscr();
					return true;
				}
			}
		}
		return false;
}

