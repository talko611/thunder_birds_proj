#pragma once
#include "Ghost.h"

class VerticalGhost : public Ghost
{

public:
	VerticalGhost(int x = -1, int y = -1, Direction dir = Direction::Down, char sign = '!') : Ghost(x, y, dir, sign) {}
	VerticalGhost(const Point& p, Direction dir = Direction::Right, char sign = '!') : Ghost(p, dir, sign) {}
	bool move(char bord[][width]) override;
	void changeDirection()override;
};

