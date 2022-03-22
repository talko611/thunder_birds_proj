//
// Created by Tal Koren on 21/03/2022.
//
#include "Point.h"


void Point::movePoint(Direction dir) {
    switch (dir) {
    case Direction::Up:
        x -= 1;
        break;
    case Direction::Down:
        x += 1;
        break;
    case Direction::Left:
        y -= 1;
        break;
    case Direction::Right:
        y += 1;
        break;
    case Direction::Stop:
        break;
    }
}
