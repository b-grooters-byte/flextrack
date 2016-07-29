//
// Created by Brandon Grooters on 2/9/16.
//

#define BOOST_TEST_MODULE GeometryTest

#include <boost/test/unit_test.hpp>
#include <cmath>
#include "Geometry.h"

//---------------------------------------------------------------------------------------
//! \brief Test the distance function
//!
//! Test for:  horizontal line, vertical line, positive slope line, negative slope line
//---------------------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE(DistanceTest) {

    BOOST_TEST_MESSAGE( "Distance Test" );

    ByteTrail::Point pt_a{0, 0};
    ByteTrail::Point pt_b{0, 0};
    BOOST_CHECK_EQUAL(0.0, pt_a.Distance(pt_b));

    // horizontal line
    pt_b.x = 10.0;
    BOOST_CHECK_EQUAL(10.0, pt_a.Distance(pt_b));

    //vertical line
    pt_b.x  = 0.0;
    pt_b.y  = 10.0;
    BOOST_CHECK_EQUAL(10.0, pt_a.Distance(pt_b));

    // positive slope
    pt_b.x = 10.0;
    pt_b.y = 10.0;
    BOOST_CHECK_EQUAL(std::sqrt(200), pt_a.Distance(pt_b));

    // negative slope
    pt_b.x = 10.0;
    pt_b.y = -10.0;
    BOOST_CHECK_EQUAL(std::sqrt(200), pt_a.Distance(pt_b));
}

//---------------------------------------------------------------------------------------
//! \brief Validates undefined slope
//---------------------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE(UndefinedSlopeTest) {
    ByteTrail::Point pt_a{0, 0};
    ByteTrail::Point pt_b{0, 1};

    BOOST_CHECK(std::isnan(pt_a.Slope(pt_b)));
}

//---------------------------------------------------------------------------------------
//! \brief Validates slope for defined slopes
//!
//! Tests several positive and negative slope values including lines with a slope of 0.0
//! This does not test undefined slopes. For undefined slope test see
//! UndefinedSlopeTest()
//---------------------------------------------------------------------------------------
BOOST_AUTO_TEST_CASE(SlopeTest) {
    ByteTrail::Point pt_a{0, 0};
    ByteTrail::Point pt_b{2, 0};

    BOOST_CHECK_EQUAL(0.0, pt_a.Slope(pt_b));

    pt_b = {2, 2};
    BOOST_CHECK_EQUAL(1.0, pt_a.Slope(pt_b));

    pt_b = {2, -2};
    BOOST_CHECK_EQUAL(-1.0, pt_a.Slope(pt_b));
}
