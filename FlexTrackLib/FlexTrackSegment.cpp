#include <cmath>

#include "FlexTrackSegment.h"
#include "NScale.h"

namespace ByteTrail
{

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
FlexTrackSegment::FlexTrackSegment() {
    _curve->SetControlPoint(0, 0, 0);
    _curve->SetControlPoint(kFlexTrackLength * 0.25, 0,  1);
    _curve->SetControlPoint(kFlexTrackLength * 0.75, 0, 2);
    _curve->SetControlPoint(kFlexTrackLength, 0, 3);
    _curve->SetResolution(kFlexTrackLength / kAverageTieSpacing);
}

FlexTrackSegment::~FlexTrackSegment() {
    //dtor
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
    for(auto&& tan_pt : tangent_points) {
      double tan_x = tan_pt.x;
      double tan_y = tan_pt.y;

      double dist = std::sqrt(tan_x * tan_x + tan_y * tan_y);
      tan_x /= dist;
      tan_y /= dist;
      #offset from the midpoint along the tangent line
      double pos_x = points[idx].x + kAverageTieWidth / 2.0 * tan_x;
      double pos_y = points[idx].y + kAverageTieWidth / 2.0 * tan_y;

      pos_x = points[idx].x - kAverageTieWidth / 2.0 * tan_x;
      pos_y = points[idx].y - kAverageTieWidth / 2.0 * tan_y;

      idx++;
    }
  }
} // namepace ByteTrail
