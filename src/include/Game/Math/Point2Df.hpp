#ifndef POINT2DF_H
#define POINT2DF_H

namespace ShF {

class Point2Df {
    public:
        float x, y;
        bool exists;

        Point2Df(float x, float y) : x(x), y(y), exists(true) {};
        Point2Df(bool exists) : exists(exists) {};
        Point2Df() : exists(false) {};

        void rotateAround(Point2Df &b, float angle);
        Point2Df getRotated(Point2Df &b, float angle);
        Point2Df sum(Point2Df b);
        Point2Df sub(Point2Df b);
        bool between(Point2Df a, Point2Df b);
};

}

#endif //POINT2DF_H