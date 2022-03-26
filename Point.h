#pragma once
#include "Utils.h"


class Point {
    int x;
    int y;

public:
    Point(int x1 = 1, int y1 = 1) : x(x1), y(y1) {}
    Point(const Point& p) {
        x = p.x;
        y = p.y;
    }

    int getX() const {
        return x;
    }

    int getY() const {
        return y;
    }

    void set(int x1, int y1) {
        x = x1;
        y = y1;
    }

    friend std::ostream& operator<<(std::ostream& out, const Point& p) {
        return out << '(' << p.x << ',' << p.y << ')';
    }

};


