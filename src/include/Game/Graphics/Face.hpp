#ifndef FACE_H
#define FACE_H

#include "Game/Math/Line2Df.hpp"
#include "TextureBoundingRect.hpp"

namespace ShF {

class Face {
    public:
        TextureBoundingRect *texture;
        Line2Df line;
};

}

#endif