#pragma once
#include <string>
#include "Utils.h"

class Bord
{
	char** bord = nullptr;
	string name ="";
	int lives = 0;
	int time = 0;
	
public:
	Bord();
	Bord(const Bord& bord) = delete;
	void operator=(const Bord& bord) = delete;
	~Bord();
	char** getBord();
	int getLives() const;
	int getTime() const;
	string getName() const;
	void setName(string name);
	void setLives(int lives);
	void setTime(int time);

	friend ostream& operator<<(ostream& out, const Bord& bord);
};

