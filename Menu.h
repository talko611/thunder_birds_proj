#pragma once
#include "Game.h";

class Menu
{
	int userChoice;
	bool color = true;
	constexpr static int seperateLineLen = 40;
	enum validChoic { Exit = 57, Play = 49, changeColor = 55, showInstructions = 56};

	void printMenu() const;
	void printInstructions() const;
	void changeColorStatus();
public:
	void getUserChoice();
	
};
