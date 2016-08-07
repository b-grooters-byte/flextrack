#include <cmath>

#include "FlexTrackSegment.h"
#include "NScale.h"

namespace ByteTrail
{

  //-----------------------------------------------------------------------------
  //-----------------------------------------------------------------------------
  FlexTrackSegment::FlexTrackSegment() {
      _curve = std::make_shared<BezierCurve>();

      _curve->SetControlPoint(0, 0, 0);
      _curve->SetControlPoint(kFlexTrackLength * 0.25, 0,  1);
      _curve->SetControlPoint(kFlexTrackLength * 0.75, 0, 2);
      _curve->SetControlPoint(kFlexTrackLength, 0, 3);
      _curve->SetResolution(kFlexTrackLength / kAverageTieSpacing);
  }

  FlexTrackSegment::~FlexTrackSegment() {
      //dtor
  }

  const std::shared_ptr<BezierCurve> FlexTrackSegment::GetCurve() {
      return _curve;
  }


  //---------------------------------------------------------------------------
  //! \brief Gets the points for each tie in a flex track segment
  //---------------------------------------------------------------------------
  void FlexTrackSegment::GetTies() {
    const std::vector<Point> & tangent_points = _curve->GetTangentPoints();

    // the tangent point is the midpoint of the tie
    // need the +/- tie edges
    const std::vector<Point> & points = _curve->GetCurve(0);
    int idx = 0;
    double tieLength = kAverageTieLength / 2.0;
    for(auto&& tan_pt : tangent_points) {
      double tan_x = tan_pt.x;
      double tan_y = tan_pt.y;

      double dist = std::sqrt(tan_x * tan_x + tan_y * tan_y);
      tan_x /= dist;
      tan_y /= dist;
      // offset from the midpoint along the tangent line
      Point pos;
      pos.x = points[idx].x + kAverageTieWidth / 2.0 * tan_x;
      pos.y = points[idx].y + kAverageTieWidth / 2.0 * tan_y;
      // get the normal points for the tangent line offset
      Point norm;

      std::shared_ptr<Polygon> tie = std::make_shared<Polygon>();
      // point 1
      norm.x = pos.x + tan_y * tieLength;
      norm.y = pos.y - tan_x * tieLength;
      tie->Add(norm);
      // point 2
      norm.x = pos.x - tan_y * tieLength;
      norm.y = pos.y + tan_x * tieLength;
      tie->Add(norm);

      pos.x = points[idx].x - kAverageTieWidth / 2.0 * tan_x;
      pos.y = points[idx].y - kAverageTieWidth / 2.0 * tan_y;
      // point 3
      norm.x = pos.x + tan_y * tieLength;
      norm.y = pos.y - tan_x * tieLength;
      tie->Add(norm);
      // point 4
      norm.x = pos.x - tan_y * tieLength;
      norm.y = pos.y + tan_x * tieLength;
      tie->Add(norm);

      idx++;
    }
  }
} // namespace ByteTrail
