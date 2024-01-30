#ifndef TEXTUREBOUNDINGRECT_H
#define TEXTUREBOUNDINGRECT_H

#include "Game/Math/Point2Di.hpp"

namespace ShF {

class TextureBoundingRect {
    public:
        int x, y;
        int width, height;

        TextureBoundingRect() {};
        TextureBoundingRect(int x, int y, int width, int height) : x(x), y(y), width(width), height(height) {};
        int positionFromFraction(double f);
        Point2Di getFloorPosition(double x, double y);
};

}

#endif