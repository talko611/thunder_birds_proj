#pragma once
#include <iostream>
#include<filesystem>
#include <fstream>
#include <vector>
#include <string>
#include "bord.h"
#include "Block.h"
#include "Ghost.h"



namespace fs = std::filesystem;
using namespace std;

class FileInputOutput
{
	string directoryPath;
	vector<string> inputFilesNames;
	vector<string> stepsFilesNames;
	vector<string> resultFilesNames;
	string lastRecordedFileName;
	int currentFileNum;
	fstream inOut1, inOut2;


	
	
	void readFilesNamesByMode(GameMode mode);// Read file names to the correcr array and throw an exceptioin if it faild
	string getStringByKey(char key) const;
public:
	FileInputOutput( GameMode mode = GameMode::regular,int fileNum = 0, string path = fs::current_path().string()) : currentFileNum(fileNum), directoryPath(path){
		this->readFilesNamesByMode(mode);
	}
	bool isNeedFilesExists(GameMode mode) const;
	void setCurrentInputFileNum(int num) { this->currentFileNum = num; }
	int getCurrentFileNum() const { return this->currentFileNum; }
	void setCurrentFileNum(int fileNum) { this->currentFileNum = fileNum; }
	int getMaxStages()const { return this->inputFilesNames.size(); }
	void readScreen(Bord& bord, int screenNum);
	void writeWandringGhostMove(const Ghost& g);
	void writeCurrentKey(char key);
	bool setFilesByMode(GameMode mode);
	void closeAll();
	void writeResult(int result);
	void writeTime(int time);
	int getEndRoundTime();
	char getNextKeyInput();
	int readResult();
	MenuChoice getLastGameMode();
	bool writeGameMode(MenuChoice choice);
	Direction readGhostNextDir();
};

