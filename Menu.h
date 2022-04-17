#pragma once
#include "Game.h"
#include "Bord.h"
#include "ScreenReader.h"
#include "Renderer.h"

class Menu
{
	constexpr static int seperateLineLen = 40;
	int userChoice;
	Bord bord;
	Renderer renderer;
	ScreenReader screenReader;
	enum validChoic { Exit = 57, Play = 49,ChangeScreen = 50, changeColor = 55, showInstructions = 56};

	void printMenu() const;
	void printInstructions() const;
	void changeColorStatus();
	void chooseScreen();
public:
	Menu() : renderer(Renderer(true)) {};
	void getUserChoice();
	
};
