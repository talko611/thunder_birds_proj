#include "Ship.h"


Ship::Ship(const Point& p, ShipSize size, char shipCh , int weight) : size(size), shipCharacter(shipCh), weightCanMove(weight) {
    int x = p.getX();
    int y = p.getY();

    if (size == ShipSize::Big) {
        currentLocation.insert(currentLocation.begin(), { {x, y++}, {x++, y--}, {x, y++}, {x, y} });
    }
    else {
        currentLocation.insert(currentLocation.begin(), { {x, y++}, {x, y} });
    }
}

Ship::Ship(ShipSize size, char shipCh, int weight) : size(size), shipCharacter(shipCh), weightCanMove(weight){}

void Ship::move(Direction dir) {
    int x, y;

    switch (dir) {
    case Direction::Down:
        for (auto& point : currentLocation) {
            x = point.getX();
            y = point.getY();
            point.set(++x, y);
        }
        break;
    case Direction::Up:
        for (auto& point : currentLocation) {
            x = point.getX();
            y = point.getY();
            point.set(--x, y);
        }
        break;
    case Direction::Left:
        for (auto& point : currentLocation) {
            x = point.getX();
            y = point.getY();
            point.set(x, --y);
        }
        break;
    case Direction::Right:
        for (auto& point : currentLocation) {
            x = point.getX();
            y = point.getY();
            point.set(x, ++y);
        }
        break;
    case Direction::Stop:
        break;
    }
}

std::ostream& operator<<(std::ostream& out, const Ship& ship) {
    std::cout << "Represented character: " << ship.shipCharacter << std::endl
        << "Location : ";
    for (auto& point : ship.currentLocation) {
        std::cout << point << " ";
    }
    std::cout << std::endl;
    if (ship.size == ShipSize::Big) {
        std::cout << "Size : Big";
    }
    else {
        std::cout << "Size : Small";
    }
    cout << endl;
    return out;
}

vector<Point>& Ship::getCurrLoc()  {return currentLocation;}

char Ship::getShipCharacter() const {return shipCharacter;}

int Ship::getWeightCanMove()const { return weightCanMove; }

void Ship::setLocation(vector<Point>& location){this->currentLocation = location;}

void Ship::setSize(ShipSize size) { this->size = size; }

void Ship::setWeightCanMove(int weight) { this->weightCanMove = weight;}

void Ship::setShipCharacter(char ch) { this->shipCharacter = ch; }

void Ship::setPointOfLocation(Point p) {
    this->currentLocation.push_back(p);
}