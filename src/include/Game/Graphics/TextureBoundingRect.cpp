#include "TextureBoundingRect.hpp"

namespace ShF {

int TextureBoundingRect::positionFromFraction(float f) {
    return x + (int)(width*f)%width;
}

}