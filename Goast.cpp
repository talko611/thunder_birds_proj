#include "Goast.h"
Goast::Goast(const Point& p)
{
	this->position = p;
}

Goast::Goast(int x, int y) : position(Point(x,y)){}

Goast::Goast(const Goast& goast) {
	this->position = goast.position;
	this->direction = goast.direction;
}

void Goast::move(Direction dir, char bord[][width]) {
	int x = this->position.getX();
	int y = this->position.getY();
	bord[x][y] = ' ';
	switch (dir)
	{
	case Direction::Up:
		this->position.set(--x, y);
		break;
	case Direction::Down:
		this->position.set(++x, y);
		break;
	case Direction::Right:
		this->position.set(x, ++y);
		break;
	case Direction::Left:
		this->position.set(x, --y);
		break;
	case Direction::Stop:
		break;
	default:
		break;
	}
	bord[x][y] = (char)objectAsciiVal::Goast;
}

Direction Goast::getDirection() const { return this->direction; }

Point Goast::getLocation() const {return this->position;}

void Goast::changeDirection() {
	if (this->direction == Direction::Up) {
		this->direction = Direction::Down;
	}
	else {
		this->direction = Direction::Up;
	}
}

void Goast::setLocation(int x, int y) { this->position.set(x, y); }

void Goast::operator=(const Goast& goast) { 
	this->position = goast.position;
	this->direction = goast.direction;
}

bool Goast::operator ==(const Goast& goast) { 
	return this->position == goast.position && this->direction == goast.direction; 
}

ostream& operator <<(ostream& out, const Goast& goast) {
	return out << "Goast position: " << goast.position << endl;
}
