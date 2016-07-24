//
// Created by Brandon Grooters on 2016.07.23
//

#define BOOST_TEST_MODULE BezierTest

#include <boost/test/unit_test.hpp>
#include <cmath>
#include "BezierCurve.h"

namespace utf = boost::unit_test;

namespace ByteTrail {

//---------------------------------------------------------------------------------------
//! \brief Validates distance calculation of a BezierCurve using straight line
//!        estimation based on the curve resolution
//---------------------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE(DistanceTest, * utf::tolerance(0.00001)) {
    BezierCurve curve;

    Point p1 = {0,0};
    Point p2 = {10,0};

    curve.SetControlPoint(p1, 0);
    curve.SetControlPoint(p1, 1);
    curve.SetControlPoint(p2, 2);
    curve.SetControlPoint(p2, 3);

    double len = curve.GetLength();
    BOOST_TEST(10.0F == len);

    // high resolution straight line
    curve.SetResolution(0.0125);
    len = curve.GetLength();
    BOOST_TEST(10.0F == len);
}

}
