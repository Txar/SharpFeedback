#ifndef DRAWOBJECT_H
#define DRAWOBJECT_H

#include "Face.hpp"
#include <vector>

namespace ShF {

class DrawObject {
    public:
        DrawObject();
        std::vector<Face> walls;
        double height;
        double z;
};

}

#endif