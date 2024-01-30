#include "TextureBoundingRect.hpp"
#include <math.h>
#include "Game/Math/Point2Di.hpp"

namespace ShF {

int TextureBoundingRect::positionFromFraction(double f) {
    if (f < 0) return x + (width - (int)abs(width*f)%width);
    else return x + (int)(width*f)%width;
}

Point2Di TextureBoundingRect::getFloorPosition(double x, double y) {
    return Point2Di(this->x + (int)(width + x)%width, this->y + (int)(height + y)%height);
}

}