#ifndef FLEXTRACKGEOMETRY_H_INCLUDED
#define FLEXTRACKGEOMETRY_H_INCLUDED

#include <BezierCurve.h>

namespace ByteTrail {
  class FlexTrackGeometry : public BezierCurve {
    public:
        /** Default constructor */
        FlexTrackGeometry();
        /** Default destructor */
        virtual ~FlexTrackGeometry();

    protected:

    private:
  };
}

#endif // FLEXTRACKGEOMETRY_H_INCLUDED
