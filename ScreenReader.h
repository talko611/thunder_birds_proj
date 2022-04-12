#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <filesystem>
#include <fstream>
#include "Utils.h"
#include "Bord.h"


namespace fs = std::filesystem;

class ScreenReader
{
	vector<string> screenFileNames;
	string directoryPath;

	void readScreenFileNames();
	
public:

	ScreenReader(string path = fs::current_path().string()) : directoryPath(path)
	{
		readScreenFileNames();
	}

	vector<string>& getScreenFileNames();
	void readScreen(Bord& bord, int screenNum) const;
};

