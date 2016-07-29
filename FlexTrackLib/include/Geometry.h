#ifndef BTS_GEOMETRY_H_INCLUDED
#define BTS_GEOMETRY_H_INCLUDED

#include <memory>

namespace ByteTrail
{
    struct Point
    {
        double x;
        double y;

        double Distance(const Point & other) const;
        double Slope(const Point & other) const;
        std::unique_ptr<Point> GetPointFrom(const Point & midpoint) const;
    };

    struct Rect
    {
        double x;
        double y;
        double width;
        double height;

        bool Contains(const Point & p ) const;
        bool Contains(double x, double y) const;
    };

}
#endif // BTS_GEOMETRY_H_INCLUDED
