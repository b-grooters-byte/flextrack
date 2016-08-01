#ifndef BTS_GEOMETRY_H_INCLUDED
#define BTS_GEOMETRY_H_INCLUDED

#include <memory>
#include <vector>

namespace ByteTrail
{
    struct Point {
      double x;
      double y;

      double Distance(const Point & other) const;
      double Slope(const Point & other) const;
      std::unique_ptr<Point> GetPointFrom(const Point & midpoint) const;
    };

    struct Rect {
      double x;
      double y;
      double width;
      double height;

      bool Contains(const Point & p ) const;
      bool Contains(double x, double y) const;
    };

    class Polygon {
      public:
          Polygon();
          virtual ~Polygon();

          const std::vector<Point> & GetPoints() const;
          int Add(Point & point);
          int GetSize() const;
      protected:
      private:
          std::vector<Point> _points;
    };

}
#endif // BTS_GEOMETRY_H_INCLUDED