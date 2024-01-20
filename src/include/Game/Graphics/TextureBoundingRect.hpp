#ifndef TEXTUREBOUNDINGRECT_H
#define TEXTUREBOUNDINGRECT_H

namespace ShF {

class TextureBoundingRect {
    public:
        int x, y;
        int width, height;

        int positionFromFraction(float f);
};

}

#endif