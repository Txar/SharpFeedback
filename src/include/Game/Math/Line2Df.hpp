#ifndef LINE2DF_H
#define LINE2DF_H

#include "Point2Df.hpp"

namespace ShF {

class Line2Df {
    public:
        float x, y, x2, y2;

        Line2Df(float x, float y, float x2, float y2) : x(x), y(y), x2(x2), y2(y2) {};
        Line2Df(Point2Df a, Point2Df b) : x(a.x), y(a.y), x2(b.x), y2(b.y) {};
        Line2Df(Point2Df a, Point2Df b, bool absolute);
        Line2Df() {};

        void rotate(float angle);
        Line2Df getRotated(float angle);
        Point2Df A();
        Point2Df B();
        void setA(Point2Df p);
        void setB(Point2Df p);
        float length();
        Point2Df intersect(Line2Df &b);
        Point2Df intersectNonSegment(Line2Df &b);
};

}

#endif //LINE2DF_H