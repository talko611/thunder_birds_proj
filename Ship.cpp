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

void Ship::move(Direction dir) {
    int x, y;
    copyCurrentLocationToOldLocation();

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

void Ship::copyCurrentLocationToOldLocation() {
    if (!oldLocation.empty()) {
        oldLocation.clear();
    }
    oldLocation.insert(oldLocation.begin(), currentLocation.begin(), currentLocation.end());
}

std::ostream& operator<<(std::ostream& out, const Ship& ship) {
    std::cout << "Represented character: " << ship.shipCharacter << std::endl
        << "Location : " << std::endl;
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
    return out;
}
