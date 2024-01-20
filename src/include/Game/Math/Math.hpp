#ifndef MATH_H
#define MATH_H

#include <math.h>
#include <stdlib.h>
#include "Point2Df.hpp"

namespace ShF {

class Math {
    private:

    public:
        static float* sinTable;
        static const float PI;
        static float degreesToRadians(float deg);
        static float fastSin(float x);
        static float fastCos(float x);
        static float fastSqrt(float x); //lol
        static float slope(Point2Df A, Point2Df B);
        static float origin(Point2Df A, Point2Df B);
        static float origin(Point2Df A, float slope);
        static Point2Df slopeAndOrigin(Point2Df A, Point2Df B);
        static float intersection(float a, float b, float c, float d);
        static void initialize();
};

}

#endif //MATH_H