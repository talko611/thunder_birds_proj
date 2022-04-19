#pragma once
#include <string>
#include "Utils.h"

class Bord
{
	char** bord;
	string name;
	int lives;
	int time;
	
public:
	Bord();
	Bord(const Bord& bord);
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

