#ifndef BTS_GEOMETRY_H_INCLUDED
#define BTS_GEOMETRY_H_INCLUDED

#include <memory>
#include <vector>
#include <list>

namespace ByteTrail {

    struct Point;

    enum SegmentType {
        SEG_MOVE_TO,
        SEG_LINE_TO,
        SEG_CLOSE
    };

    struct PathSegment {
        SegmentType type;
        std::shared_ptr<Point> point;
    };

    const PathSegment PATH_SEGMENT_CLOSE{SEG_CLOSE, nullptr};

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

  class Path {
    public:
         virtual const std::list<std::shared_ptr<PathSegment>> & GetPath() = 0;
  };

    class Polygon : private Path {
      public:
          Polygon();
          virtual ~Polygon();

          //const std::vector<Point> & GetPoints() const;
          const std::list<std::shared_ptr<PathSegment>> & GetPath();
          int Add(const Point & point);
          int GetSize() const;
      protected:
      private:
          std::list<std::shared_ptr<PathSegment>> _path;
    };

}
#endif // BTS_GEOMETRY_H_INCLUDED
