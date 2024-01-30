#ifndef MATH_H
#define MATH_H

#include <math.h>
#include <stdlib.h>
#include "Point2Dd.hpp"

namespace ShF {

class Math {
    private:

    public:
        static double* sinTable;
        static const double PI;
        static const double DEG_TO_RAD;
        static double degreesToRadians(double deg);
        static double fastSin(double x);
        static double fastCos(double x);
        static double fastSqrt(double x); //lol
        static double slope(Point2Dd A, Point2Dd B);
        static double origin(Point2Dd A, Point2Dd B);
        static double origin(Point2Dd A, double slope);
        static double lerp(double a, double b, float t);
        static Point2Dd slopeAndOrigin(Point2Dd A, Point2Dd B);
        static double intersection(double a, double b, double c, double d);
        static void initialize();
};

}

#endif //MATH_H