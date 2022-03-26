#pragma once
#include <vector>
#include "Point.h"
#include "Utils.h"


class Ship {
    std::vector<Point> currentLocation, oldLocation;
    ShipSize size;
    char shipCharacter; // represented character

    void copyCurrentLocationToOldLocation();

public:
    Ship(const Point& p, ShipSize size, char shipCh);
    std::vector<Point> getCurrLoc() const {
        return currentLocation;
    }
    std::vector<Point> getOldLoc() const {
        return oldLocation;
    }
    char getShipCharacter() const {
        return shipCharacter;
    }
    void move(Direction dir);

    friend std::ostream& operator << (std::ostream& out, const Ship& ship);
};


