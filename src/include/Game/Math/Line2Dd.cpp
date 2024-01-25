#include "Line2Dd.hpp"
#include <iostream>
#include "Math.hpp"

namespace ShF {

void Line2Dd::rotate(double angle) {
    Point2Dd a(0, 0);
    Point2Dd b = B();

    b.rotateAround(a, angle);
    setB(b);
}

Line2Dd Line2Dd::getRotated(double angle) {
    Line2Dd b = *this;
    b.rotate(angle);
    return b;
}

Point2Dd Line2Dd::intersect(Line2Dd &b) {
    Point2Dd A1 = A(), B1 = B().sum(A1), A2 = b.A(), B2 = b.B().sum(A2);

    Point2Dd helper;
    if (B1.x < A1.x) {
        helper = A1;
        A1 = B1;
        B1 = helper;
    }
    if (B2.x < A2.x) {
        helper = A2;
        A2 = B2;
        B2 = helper;
    }

    Point2Dd slopeAndOriginA = Math::slopeAndOrigin(A1, B1);
    Point2Dd slopeAndOriginB = Math::slopeAndOrigin(A2, B2);

    double i = Math::intersection(slopeAndOriginA.x, slopeAndOriginA.y, slopeAndOriginB.x, slopeAndOriginB.y);
    Point2Dd inter(i, slopeAndOriginA.x*i + slopeAndOriginA.y);
    //std::cout << inter.x << " " << inter.y << " ";
    //printf("%f %f %f %f\n-> %f %f %f %f\n", A2.x, B2.x, A2.y, B2.y, A1.x, B1.x, A1.y, B1.y);

    Point2Dd point0(0, 0);

    if (inter.between(A1, B1) 
    &&  inter.between(A2, B2)) {
        return inter;
    }
    else {
        return Point2Dd(false);
    }
}

/*
double CCW(Point2Df a, Point2Df b, Point2Df c)
{ return (b.x-a.x)*(c.y-a.y) - (b.y-a.y)*(c.x-a.x); }

bool _intersect(Point2Df a, Point2Df b, Point2Df c, Point2Df d)
{ return (CCW(a,b,c)*CCW(a,b,d)<0 && CCW(c,d,b)*CCW(c,d,a)<0); }

Point2Df Line2Df::intersectNonSegment(Line2Df &b) {
    Point2Df a1 = A();
    Point2Df b1 = B().sum(a1);
    Point2Df a2 = b.A();
    Point2Df b2 = b.B().sum(a2);

    double h = ( (a1.x - b1.x)*(a2.y - b2.y) - (a1.y - b1.y)*(a2.x - b2.x) );
    double p1 = a1.x*b1.y - a1.y*b1.x;
    double p2 = a2.x*b2.y - a2.y*b2.x;

    double px = ( p1*(a2.x - b2.x) - p2*(a1.x - b1.x) ) / h;
    double py = ( p1*(a2.y - b2.y) - p2*(a1.y - b1.y) ) / h;

    return Point2Df(px, py);
}

Point2Df Line2Df::intersect(Line2Df &b) {
    Point2Df a1 = A();
    Point2Df b1 = B().sum(a1);
    Point2Df a2 = b.A();
    Point2Df b2 = b.B().sum(a2);

    //double px = ( (a1.x*b1.y - a1.y*b1.x)*(a2.x - b2.x) - (a1.x - b1.x)*(a2.x*b2.y - a2.y*b2.x) )
    //        /  ( (a1.x - b1.x)*(a2.y - b2.y) - (a1.y - b1.y)*(a1.x - b1.x) );
    if (_intersect(a1, b1, a2, b2)) return Point2Df(false);

    double h = ( (a1.x - b1.x)*(a2.y - b2.y) - (a1.y - b1.y)*(a2.x - b2.x) );

    double t = ( (a1.x - a2.x)*(a2.y - b2.y) - (a1.y - a2.y)*(a2.x - b2.x) ) / h;
    
    double u = ( (a1.x - b1.x)*(a1.y - a2.y) - (a1.y - b1.y)*(a1.x - a2.x) ) / h;

    //t =   ( (a1.x - a2.x)*(a2.y - b2.y) - (a1.y - a2.y)*(a2.x - b2.x) )
    //    / ( (a1.x - b1.x)*(a2.y - b2.y) - (a1.y - b1.y)*(a2.x - b2.x) )

    double px, py;
    
    if (t <= 1.0 && t >= 0.0) {
        px = a1.x + t*(b1.x - a1.x);
        py = a1.y + t*(b1.y - a1.y);
        return Point2Df(px, py);
    }
    else if (u <= 1.0 && u >= 0.0) {
        px = a2.x + u*(b2.x - a2.x);
        py = a2.y + u*(b2.y - a2.y);
        return Point2Df(px, py);
    } else {
        return Point2Df(false);
    }
}
*/

Point2Dd Line2Dd::A() {
    return Point2Dd(x, y);
}

Point2Dd Line2Dd::B() {
    return Point2Dd(x2, y2);
}

double Line2Dd::length() {
    return Math::fastSqrt((x2*x2) + (y2*y2));
}

void Line2Dd::setA(Point2Dd p) {
    x = p.x, y = p.y;
}

void Line2Dd::setB(Point2Dd p) {
    x2 = p.x, y2 = p.y;
}

Line2Dd::Line2Dd(Point2Dd a, Point2Dd b, bool absolute) {
    if (absolute) {
        x = a.x;
        y = a.y;
        x2 = b.x - a.x;
        y2 = b.y - a.y;
    } else {
        x = a.x;
        y = a.y;
        x2 = b.x;
        y2 = b.y;
    }
}

}