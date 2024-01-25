#ifndef POINT2DF_H
#define POINT2DF_H

namespace ShF {

class Point2Dd {
    public:
        double x, y;
        bool exists;

        Point2Dd(double x, double y) : x(x), y(y), exists(true) {};
        Point2Dd(bool exists) : exists(exists) {};
        Point2Dd() : exists(false) {};

        void rotateAround(Point2Dd &b, double angle);
        Point2Dd getRotated(Point2Dd &b, double angle);
        Point2Dd sum(Point2Dd b);
        Point2Dd sub(Point2Dd b);
        bool between(Point2Dd a, Point2Dd b);
};

}

#endif //POINT2DF_H