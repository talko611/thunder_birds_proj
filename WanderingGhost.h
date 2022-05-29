#pragma once
#include <cstdlib>
#include<ctime>
#include "Ghost.h"

class WanderingGhost : public Ghost
{

public:
	WanderingGhost(int x = -1, int y = -1, Direction dir = Direction::Right, char sign = '%') : Ghost(x, y, dir, sign) {}
	WanderingGhost(const Point& p, Direction dir = Direction::Right, char sign = '%') : Ghost(p, dir, sign) {}
	bool move(char bord[][width]) override;
	bool moveByDir(char Bord[][width], Direction dir) override;
	void changeDirection()override;
	void startSeed()const { srand(time(0)); }
	bool checkIfMoveAvailable(Point& saver, const char bord[][width])const;
};

