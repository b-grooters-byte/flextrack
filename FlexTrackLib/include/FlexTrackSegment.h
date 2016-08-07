#ifndef BYTETRAIL_FLEXTRACKSEGMENT_H
#define BYTETRAIL_FLEXTRACKSEGMENT_H

#include<memory>
#include <vector>

#include "Geometry.h"
#include "BezierCurve.h"
#include "TrackSegment.h"

namespace ByteTrail {

  class FlexTrackSegment : private TrackSegment {
    public:
      FlexTrackSegment();
      virtual ~FlexTrackSegment();

      const std::shared_ptr<BezierCurve> GetCurve();
      void GetTies();

    protected:
    private:
      std::shared_ptr<BezierCurve> _curve;
      std::vector<std::shared_ptr<Polygon>> _ties;

  };
}

#endif // BYTETRAIL_FLEXTRACKSEGMENT_H
