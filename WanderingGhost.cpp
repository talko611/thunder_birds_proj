#include "WanderingGhost.h"

bool WanderingGhost::move(char bord[][width]) {
	Point saver = this->getLocation();
	this->changeDirection();
	saver = changePointByDirection(saver, this->getDirection());
	int x = saver.getX();
	int y = saver.getY();
	bool res = false;

	if (bord[x][y] == (char)objectAsciiVal::Wall1 || bord[x][y] == (char)objectAsciiVal::Wall2
		|| (bord[x][y] >= (char)objectAsciiVal::BlockLowestVal && bord[x][y] <= (char)objectAsciiVal::BlockHighestVal)
		|| bord[x][y] == (char)objectAsciiVal::HorizontalGhost || bord[x][y] == (char)objectAsciiVal::verticalGhost
		|| bord[x][y] == (char)objectAsciiVal::WandringGhost) {
	}
	else {
		this->setLocation(saver);
		res = true;
	}

	return res;

}

void WanderingGhost::changeDirection() {
	static int counter = 0;
	if (!counter) {
		this->startSeed();
		++counter;
	}
	int num = 1 + rand() % 4;
	switch (num)
	{
	case 1:
		this->setDirection(Direction::Up);
		break;
	case 2:
		this->setDirection(Direction::Down);
		break;
	case 3:
		this->setDirection(Direction::Left);
		break;
	case 4:
		this->setDirection(Direction::Right);
		break;
	default:
		break;
	}
}
