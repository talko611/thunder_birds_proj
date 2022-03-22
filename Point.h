//
// Created by Tal Koren on 21/03/2022.
//

#pragma once
#include "Utils.h"


class Point {
    int x;
    int y;

public:
    Point(int x1 = 1, int y1 = 1) : x(x1), y(y1) {}
    Point(const Point& p) {
        this->x = p.x;
        this->y = p.y;
    }

    int getX() const {
        return x;
    }

    int getY() const {
        return y;
    }

    void setPoint(int x1, int y1) {
        this->x = x1;
        this->y = y1;
    }

    void movePoint(Direction dir);

    friend std::ostream& operator<<(std::ostream& out, const Point& p) {
        return out << '(' << p.x << ',' << p.y << ')';
    }

};


