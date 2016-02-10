//
// Created by Brandon Grooters on 2/9/16.
//

#define BOOST_TEST_MODULE GeometryTests

#include <boost/test/unit_test.hpp>
#include <cmath>
#include "Geometry.h"


BOOST_AUTO_TEST_CASE(DistanceTest) {
    ByteTrail::Point pt_a{0, 0};
    ByteTrail::Point pt_b{0, 0};
    BOOST_CHECK_EQUAL(0.0, pt_a.Distance(pt_b));

    pt_b.x  = 10.0;
    BOOST_CHECK_EQUAL(10.0, pt_a.Distance(pt_b));

    pt_b.y = 10.0;
    BOOST_CHECK_EQUAL(std::sqrt(200), pt_a.Distance(pt_b));

}

