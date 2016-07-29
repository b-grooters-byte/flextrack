//
// Created by Brandon Grooters on 2016.07.23
//

#define BOOST_TEST_MODULE BezierTest

#include <boost/test/unit_test.hpp>
#include <cmath>
#include <iostream>
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

//---------------------------------------------------------------------------------------
//! \brief Validates distance calculation of a BezierCurve using an approximation of
//! a circular arc for the control points.
//!
//! A circle can be approximated with 4 bezier curves with the control points at a
//! distance, d = r*4*(sqrt(2)-1)/3 from the end points and in a direction tangent to
//! the circle at the end points. This test is run with a higher floating point
//! tolerance than the straight line test to account for radial error in the
//! approximation.
//---------------------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE(ArcDistanceTest, * utf::tolerance(0.001)) {
    BezierCurve curve;

    double ctrl_offset = 10.0 * 4.0 * (std::sqrt(2.0)-1.0) / 3.0;
    double arc_distance = 2 * M_PI * 10.0 / 4.0;
    Point p0 = {10,0};
    Point p1 = {10, ctrl_offset};
    Point p2 = {ctrl_offset,10};
    Point p3 = {0,10};

    curve.SetControlPoint(p0, 0);
    curve.SetControlPoint(p1, 1);
    curve.SetControlPoint(p2, 2);
    curve.SetControlPoint(p3, 3);

    // high resolution single quadrant arc
    curve.SetResolution(0.0125);
    double len = curve.GetLength();
    BOOST_TEST(len == arc_distance);
}


}
