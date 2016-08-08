#include "Geometry.h"

#include <cmath>
#include <iostream>

namespace ByteTrail {

  double Point::Distance(const Point & other) const {
      return std::sqrt((x - other.x) * (x - other.x) + (y - other.y) * (y - other.y));
  }

  //---------------------------------------------------------------------------
  //! \brief Gets the slope of a line
  //!
  //! Gets the slope for 2 points where:
  //!      m =  cy / cx
  //! or:
  //!          (y2 - y1)
  //!      m = ---------
  //!          (x2 - x1)
  //! the point passed in the parameter list is considered as x2, y2
  //---------------------------------------------------------------------------
  double Point::Slope(const Point & other) const {
    double cy = (other.y - y);
    double cx = (other.x - x);
    if( cx != 0)
      return cy / cx;
    else
      return std::nan("UNDEFINED");
  }

    std::unique_ptr<Point> Point::GetPointFrom(const Point & midpoint) const {
        std::unique_ptr<Point> point = std::unique_ptr<Point>(new Point());

        double cy = (midpoint.y - y);
        double cx = (midpoint.x - x);


        point->x = midpoint.x + cx;
        point->y = midpoint.y + cy;

        return point;
    }


    bool Rect::Contains(const Point & p ) const {
        return Contains(p.x, p.y);
    }

    bool Rect::Contains(double x, double y) const {
        return ((x >= this->x) && (x <= (this->x + width)) && (y >= this->y) && (y <= (this->y+height)));
    }

  //---------------------------------------------------------------------------
  //---------------------------------------------------------------------------
  Polygon::Polygon() {
  }

  //---------------------------------------------------------------------------
  //---------------------------------------------------------------------------
  Polygon::~Polygon() {
  }

  //---------------------------------------------------------------------------
  //! \brief Adds a point to the polygon
  //---------------------------------------------------------------------------
  Polygon::Add(const Point & point) {
    std::shared_ptr<PathSegment> segment = std::make_shared<PathSegment>();
    if(_path.empty()) {
      _path.push_back(std::make_shared<PathSegment>(PATH_SEGMENT_CLOSE));
      segment->type = SEG_MOVE_TO;
    } else {
        segment->type = SEG_LINE_TO;
    }
    std::shared_ptr<Point> pt = std::make_shared<Point>(point);
    segment->point = std::move(pt);
    _path.insert(_path.end(), segment);
  }

  //---------------------------------------------------------------------------
  //---------------------------------------------------------------------------
  const std::list<std::shared_ptr<PathSegment>> & Polygon::GetPath() {
      return _path;
  }

  //---------------------------------------------------------------------------
  //---------------------------------------------------------------------------
  int Polygon::GetSize() const {
    return _path.size();
  }
}
