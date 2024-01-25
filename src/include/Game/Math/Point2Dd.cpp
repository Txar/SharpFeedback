#include "Point2Dd.hpp"
#include "Math.hpp"
#include <algorithm>
#include "iostream"

namespace ShF {

void Point2Dd::rotateAround(Point2Dd &b, double angle) {
    double relX = b.x - x, relY = b.y - y;
    x += relX, y += relY;
    double newX = relX*Math::fastCos(angle) - relY*Math::fastSin(angle);
    double newY = relY*Math::fastCos(angle) + relX*Math::fastSin(angle);
    //double newX = relX*cos(angle) - relY*sin(angle);
    //double newY = relY*cos(angle) + relX*sin(angle);

    x -= newX;
    y -= newY;
}

Point2Dd Point2Dd::getRotated(Point2Dd &b, double angle) {
    Point2Dd a = *this;
    a.rotateAround(b, angle);
    return a;
}

Point2Dd Point2Dd::sum(Point2Dd b) {
    return Point2Dd(x + b.x, y + b.y);
}

Point2Dd Point2Dd::sub(Point2Dd b) {
    return Point2Dd(x - b.x, y - b.y);
}

bool Point2Dd::between(Point2Dd a, Point2Dd b) {
    //printf("%i %i %i %i\n", x > std::min(a.x, b.x), y > std::min(a.y, b.y), x < std::max(a.x, b.x), y < std::max(a.y, b.y));
    return x >= std::min(a.x, b.x) && y >= std::min(a.y, b.y) && x <= std::max(a.x, b.x) && y <= std::max(a.y, b.y);
}

}