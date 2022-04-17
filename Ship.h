#pragma once
#include <vector>
#include "Point.h"
#include "Utils.h"


class Ship {
    vector<Point> currentLocation, oldLocation;
    ShipSize size;
    char shipCharacter; // represented character
    int weightCanMove;

    void copyCurrentLocationToOldLocation();

public:
    Ship() {};
    Ship(ShipSize size, char shipCh, int weight);
    Ship(const Point& p, ShipSize size, char shipCh , int weight);
    std::vector<Point> getCurrLoc() const;
    std::vector<Point> getOldLoc() const;
    char getShipCharacter() const;
    void move(Direction dir);
    int getWeightCanMove()const;
    void setLocation(vector<Point>& location);
    void setSize(ShipSize size);
    void setWeightCanMove(int weight);
    void setShipCharacter(char ch);
    friend std::ostream& operator << (std::ostream& out, const Ship& ship);
};


