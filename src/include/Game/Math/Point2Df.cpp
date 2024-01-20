#include "Point2Df.hpp"
#include "Math.hpp"
#include <algorithm>

namespace ShF {

void Point2Df::rotateAround(Point2Df &b, float angle) {
    float relX = b.x - x, relY = b.y - y;
    x += relX, y += relY;
    float newX = relX*Math::fastCos(angle) - relY*Math::fastSin(angle);
    float newY = relY*Math::fastCos(angle) + relX*Math::fastSin(angle);
    //float newX = relX*cos(angle) - relY*sin(angle);
    //float newY = relY*cos(angle) + relX*sin(angle);

    x -= newX;
    y -= newY;
}

Point2Df Point2Df::getRotated(Point2Df &b, float angle) {
    Point2Df a = *this;
    a.rotateAround(b, angle);
    return a;
}

Point2Df Point2Df::sum(Point2Df b) {
    return Point2Df(x + b.x, y + b.y);
}

bool Point2Df::between(Point2Df a, Point2Df b) {
    return x > std::min(a.x, b.x) && y > std::min(a.y, b.y) && x < std::max(a.x, b.x) && y < std::max(a.y, b.y);
}

}