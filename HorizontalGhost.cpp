#include "HorizontalGhost.h"


bool HorizontalGhost::move(char bord[][width]) {
	Point saver = this->getLocation();
	saver = changePointByDirection(saver, this->getDirection());
	int x = saver.getX();
	int y = saver.getY();
	bool res = false;

	if (bord[x][y] == (char)objectAsciiVal::Wall1 || bord[x][y] == (char)objectAsciiVal::Wall2
		|| (bord[x][y] >= (char)objectAsciiVal::BlockLowestVal && bord[x][y] <= (char)objectAsciiVal::BlockHighestVal)
		|| bord[x][y] == (char)objectAsciiVal::HorizontalGhost || bord[x][y] == (char)objectAsciiVal::verticalGhost
		|| bord[x][y] == (char)objectAsciiVal::WandringGhost) {
		this->changeDirection();
	}
	else {
		this->setLocation(saver);
		res = true;
	}

	return res;
}

void HorizontalGhost::changeDirection() {
	if (this->getDirection() == Direction::Right) {
		this->setDirection(Direction::Left);
	}
	else {
		this->setDirection(Direction::Right);
	}
}

