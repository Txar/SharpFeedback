#include "TextureBoundingRect.hpp"

namespace ShF {

int TextureBoundingRect::positionFromFraction(double f) {
    return x + (int)(width*f)%width;
}

}