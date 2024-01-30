#ifndef POINT2DI_H
#define POINT2DI_H

namespace ShF {

class Point2Di {
    public:
        int x, y;
        bool exists;

        Point2Di(int x, int y) : x(x), y(y) {};
};

}

#endif //POINT2DI_H