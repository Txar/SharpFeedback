#ifndef FACE_H
#define FACE_H

#include "Game/Math/Line2Dd.hpp"
#include "TextureBoundingRect.hpp"

namespace ShF {

class Face {
    public:
        TextureBoundingRect *texture;
        Line2Dd line;
        sf::Color color;
        bool noTexture;
};

}

#endif