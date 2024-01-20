#include <iostream>
#include "Math.hpp"
#include "Point2Df.hpp"

namespace ShF {

const float Math::PI = 3.14159265;

float* Math::sinTable = new float[(int)(Math::PI * 1000)];

float Math::degreesToRadians(float deg) {
    return deg * PI / 180.0;
}

float Math::fastSin(float x) {
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

float Math::fastCos(float x) {
    return cos(x);
    //return sin(x + (PI / 2.0));
}

float Math::fastSqrt(float x) {
    return sqrtf(x);
}

void Math::initialize() {
    delete sinTable;
    sinTable = new float[(int)(PI * 1000.0)];

    for (int i = 0; i < PI * 1000; i++) {
        sinTable[i] = sin(i / 1000.0);
    }
}

float Math::slope(Point2Df A, Point2Df B) {
    return (B.y - A.y) / (B.x - A.x);
}

float Math::origin(Point2Df A, Point2Df B) {
    return A.y - A.x * slope(A, B);
}

float Math::origin(Point2Df A, float slope) {
    return A.y - A.x * slope;
}

Point2Df Math::slopeAndOrigin(Point2Df A, Point2Df B) {
    float slope = Math::slope(A, B);
    //std::cout << slope << std::endl;
    return Point2Df(slope, origin(A, slope));
}

float Math::intersection(float a, float b, float c, float d) {
    return (d - b) / (a - c);
}

}