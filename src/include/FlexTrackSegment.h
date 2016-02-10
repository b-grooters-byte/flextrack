#ifndef BYTETRAIL_FLEXTRACKSEGMENT_H
#define BYTETRAIL_FLEXTRACKSEGMENT_H

#include<memory>

#include "TrackSegment.h"
#include "BezierCurve.h"

namespace ByteTrail
{

    class FlexTrackSegment : private TrackSegment
    {
        public:
            FlexTrackSegment();
            virtual ~FlexTrackSegment();
        protected:
        private:
        std::shared_ptr<BezierCurve> _curve;

    };

}

#endif // BYTETRAIL_FLEXTRACKSEGMENT_H
