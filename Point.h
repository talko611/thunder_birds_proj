#pragma once
#include "Utils.h"


class Point {
    int x;
    int y;

public:
    Point(int x1 = 0, int y1 = 0 ) : x(x1), y(y1) {}
    Point(const Point& p) {
        x = p.x;
        y = p.y;
    }

    int getX() const {return x;}

    int getY() const {return y;}

    void set(int x1, int y1) {
        x = x1;
        y = y1;
    }

    bool operator ==(const Point& p) {
        return x == p.x && y == p.y;
    }

    void operator = (const Point& p) {
        this->x = p.x;
        this->y = p.y;
    }

    friend std::ostream& operator<<(std::ostream& out, const Point& p) {
        return out << '(' << p.x << ',' << p.y << ')';
    }
};


