//
// Created by Tal Koren on 21/03/2022.
//

#include "Ship.h"


Ship::Ship(const Point& p, ShipSize size, char shipCh) : size(size), shipCh(shipCh) {
    int x = p.getX();
    int y = p.getY();

    if (size == ShipSize::Big) {
        currLoc.insert(currLoc.begin(), { {x, y++},{x++, y--}, {x, y++}, {x, y} });
    }
    else {
        currLoc.insert(currLoc.begin(), { {x,y++}, {x, y} });
    }
}

void Ship::moveShip(Direction dir) {
    copyCurrToOld();
    switch (dir) {
    case Direction::Down:
        for (auto& i : currLoc) {
            i.movePoint(Direction::Down);
        }
        break;
    case Direction::Up:
        for (auto& i : currLoc) {
            i.movePoint(Direction::Up);
        }
        break;
    case Direction::Left:
        for (auto& i : currLoc) {
            i.movePoint(Direction::Left);
        }
        break;
    case Direction::Right:
        for (auto& i : currLoc) {
            i.movePoint(Direction::Right);
        }
        break;
    case Direction::Stop:
        break;
    }
}

void Ship::copyCurrToOld() {
    if (!oldLoc.empty()) {
        oldLoc.clear();
    }
    oldLoc.insert(oldLoc.begin(), currLoc.begin(), currLoc.end());
}
