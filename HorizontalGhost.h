#pragma once
#include "Ghost.h"

class HorizontalGhost : public Ghost
{
	
public:
	HorizontalGhost(int x = -1, int y = -1, Direction dir = Direction::Right, char sign = '$') : Ghost(x, y, dir, sign) {}
	HorizontalGhost(const Point& p, Direction dir = Direction::Right, char sign = '$') : Ghost(p, dir, sign) {}
	bool move(char bord[][width]) override;
	bool moveByDir(char bord[][width], Direction dir) override { return move(bord); }
	void changeDirection()override;
};

