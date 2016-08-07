#ifndef BTS_GEOMETRY_H_INCLUDED
#define BTS_GEOMETRY_H_INCLUDED

#include <memory>
#include <vector>

namespace ByteTrail
{
    struct Point {
      double x;
      double y;

      inline Point() {}

      inline Point(double x, double y) {
          this->x = x;
          this->y = y;
      }

      inline Point(const Point & point) {
          x = point.x;
          y = point.y;
      }

      double Distance(const Point & other) const;
      double Slope(const Point & other) const;
      std::unique_ptr<Point> GetPointFrom(const Point & midpoint) const;

      inline void operator=(const Point & point) {
          x = point.x;
          y = point.y;
      }

      inline friend bool operator==(const Point & a, const Point & b) {
          return a.x == b.x && a.y == b.y;

      }
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
          int Add(const Point & point);
          int GetSize() const;
      protected:
      private:
          std::vector<Point> _points;
    };

}
#endif // BTS_GEOMETRY_H_INCLUDED
