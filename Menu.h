#pragma once
#include "Bord.h"
#include "FileInputOutput.h"
#include "Renderer.h"
#include "Utils.h"
#include <conio.h>

class Menu
{
	constexpr static int seperateLineLen = 40;
	
	void printMenu() const;
	void printInstructions() const;
	void changeColorStatus(Renderer& renderer) const;
	bool playSingleScreen(Bord& bord, FileInputOutput& inOut, Renderer& renderer);
public:
	Menu(){}
	MenuChoice getUserChoice(Bord& bord, FileInputOutput& inOut, Renderer& renderer);
};
