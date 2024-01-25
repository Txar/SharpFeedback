#ifndef LINE2DF_H
#define LINE2DF_H

#include "Point2Dd.hpp"

namespace ShF {

class Line2Dd {
    public:
        double x, y, x2, y2;

        Line2Dd(double x, double y, double x2, double y2) : x(x), y(y), x2(x2), y2(y2) {};
        Line2Dd(Point2Dd a, Point2Dd b) : x(a.x), y(a.y), x2(b.x), y2(b.y) {};
        Line2Dd(Point2Dd a, Point2Dd b, bool absolute);
        Line2Dd() {};

        void rotate(double angle);
        Line2Dd getRotated(double angle);
        Point2Dd A();
        Point2Dd B();
        void setA(Point2Dd p);
        void setB(Point2Dd p);
        double length();
        Point2Dd intersect(Line2Dd &b);
        Point2Dd intersectNonSegment(Line2Dd &b);
};

}

#endif //LINE2DF_H