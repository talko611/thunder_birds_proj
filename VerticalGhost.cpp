#include "VerticalGhost.h"


bool VerticalGhost::move(char bord[][width]) {
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

void VerticalGhost::changeDirection() {
	if (this->getDirection() == Direction::Up) {
		this->setDirection(Direction::Down);
	}
	else {
		this->setDirection(Direction::Up);
	}
}

