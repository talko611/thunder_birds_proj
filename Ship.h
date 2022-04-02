#pragma once
#include <vector>
#include "Point.h"
#include "Utils.h"


class Ship {
    std::vector<Point> currentLocation, oldLocation;
    ShipSize size;
    char shipCharacter; // represented character
    int weightCanMove;

    void copyCurrentLocationToOldLocation();

public:
    Ship() {};
    Ship(const Point& p, ShipSize size, char shipCh , int weight);

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

    int getWeightCanMove()const { return weightCanMove; };

    friend std::ostream& operator << (std::ostream& out, const Ship& ship);
};


