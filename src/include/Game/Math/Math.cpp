#include <iostream>
#include "Math.hpp"
#include "Point2Dd.hpp"
#include "Line2Dd.hpp"

namespace ShF {

const double Math::PI = 3.14159265;

double* Math::sinTable = new double[(int)(Math::PI * 1000)];

double Math::degreesToRadians(double deg) {
    return deg * PI / 180.0;
}

double Math::fastSin(double x) {
    return sin(x); //turns out this is faster... nice -_-
    if (x == 0) return 0.0;

    if (x < 0) x = abs(x) + PI;
    
    while (x >= 2*PI) {
        x -= 2*PI;
    }

    if (x == 0) return 0.0;

    if (x > PI) {
        x = abs(x - PI);
        int index = (int)(x * 1000.0) % (int)(PI * 1000.0);
        return -sinTable[index];
    }
    else {
        int index = (int)(x * 1000.0) % (int)(PI * 1000.0);
        return sinTable[index];
    }
}

double Math::fastCos(double x) {
    return cos(x);
    //return sin(x + (PI / 2.0));
}

double Math::fastSqrt(double x) {
    return sqrtf(x);
}

void Math::initialize() {
    delete sinTable;
    sinTable = new double[(int)(PI * 1000.0)];

    for (int i = 0; i < PI * 1000; i++) {
        sinTable[i] = sin(i / 1000.0);
    }
}

double Math::slope(Point2Dd A, Point2Dd B) {
    return (B.y - A.y) / (B.x - A.x);
}

double Math::origin(Point2Dd A, Point2Dd B) {
    return A.y - A.x * slope(A, B);
}

double Math::origin(Point2Dd A, double slope) {
    return A.y - A.x * slope;
}

Point2Dd Math::slopeAndOrigin(Point2Dd A, Point2Dd B) {
    double slope = Math::slope(A, B);
    //std::cout << slope << std::endl;
    return Point2Dd(slope, origin(A, slope));
}

double Math::intersection(double a, double b, double c, double d) {
    return (d - b) / (a - c);
}

}