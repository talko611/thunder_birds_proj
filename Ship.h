//
// Created by Tal Koren on 21/03/2022.
//

#pragma once
#include <vector>
#include "Point.h"
#include "Utils.h"


class Ship {
    std::vector<Point> currLoc, oldLoc;
    ShipSize size;
    char shipCh; // represented character

    void copyCurrToOld();

public:
    Ship(const Point& p, ShipSize size, char shipCh);
    std::vector<Point> getCurrLoc() const {
        return currLoc;
    }
    std::vector<Point> getOldLoc() const {
        return oldLoc;
    }
    char getShipCh() const {
        return shipCh;
    }
    void moveShip(Direction dir);
};


