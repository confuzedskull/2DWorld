#ifndef LINE2F_H
#define LINE2F_H
#include "point2f.h"

//A line2f is a 2D line that consists of three point2f's
class line2f
{
    public:
    point2f A;
    point2f B;
    point2f midpoint();
    void set(point2f a,point2f b);
    bool hasPoint(point2f p);
    float slope();
    line2f();
    line2f(point2f a, point2f b);
};
#endif // LINE2F_H
