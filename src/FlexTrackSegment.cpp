#include "FlexTrackSegment.h"

namespace ByteTrail
{

FlexTrackSegment::FlexTrackSegment()
{
    _curve->SetControlPoint(0, 0, 0);
    _curve->SetControlPoint(25, 0,  1);
    _curve->SetControlPoint(75, 0, 2);
    _curve->SetControlPoint(100.0, 0, 3);
}

FlexTrackSegment::~FlexTrackSegment()
{
    //dtor
}

}
