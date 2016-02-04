#include "beziercurve.h"

#include <cassert>
#include <cmath>
#include <iostream>

namespace ByteTrail
{


BezierCurve::BezierCurve() :
        _resolution(kDefaultResolution),
        _parallels_distance(kDefaultDistance)
{
    _control_points[0].x = 4;
    _resolution_modified = true;
    _control_point_modified = true;
}

BezierCurve::~BezierCurve()
{
    //dtor
}

double BezierCurve::GetResolution() const
{
    return _resolution;
}

void BezierCurve::SetResolution(double resolution)
{
    assert(resolution > 0.0 && resolution < 1.0);
    if(resolution != _resolution)
    {
        _resolution = resolution;
        _resolution_modified = true;
    }
}

const Point & BezierCurve::GetControlPoint(int index) const
{
    assert(index >= 0 && index < BTS_CUBIC_CURVE_CTRL_PTS);

    return _control_points[index];
}

void BezierCurve::SetControlPoint(const Point & point, unsigned index)
{
    SetControlPoint(point.x, point.y, index);
}

void BezierCurve::SetControlPoint(double x, double y, unsigned index)
{
    assert(index < BTS_CUBIC_CURVE_CTRL_PTS);
    if( _control_points[index].x != x || _control_points[index].y != y)
    {
        _control_point_modified = true;
        _control_points[index].x = x;
        _control_points[index].y = y;
    }
}

const std::vector<Point> & BezierCurve::GetCurve(unsigned idx)
{
    if(_resolution_modified)
    {
        ResizeCurve();
        RecalculateCurve();
    }
    else if (_control_point_modified)
    {
        RecalculateCurve();
    }
    _control_point_modified = false;
    _resolution_modified = false;

    std::vector<Point> & points = _curve_points;
    switch(idx)
    {
    case 1:
        points = _top_left_points;
        break;
    case 2:
        points = _bottom_right_points;
        break;
    }
    return points;
}

void BezierCurve::ResizeCurve()
{
    int size = (int)(1.0F / _resolution + 1);
    _curve_points.resize(size);
    _top_left_points.resize(size);
    _bottom_right_points.resize(size);
}

void BezierCurve::RecalculateCurve()
{
    int idx = 0;
    double t;

    // recalculate the derived control points
    for(int i = 0; i < BTS_DERIVATIVE_CTRL_PTS; i++)
    {
        m_derivative_ctrl_pts[i].x = (3.0F * (_control_points[i + 1].x - _control_points[i].x));
        m_derivative_ctrl_pts[i].y = (3.0F * (_control_points[i + 1].y - _control_points[i].y));
    }

    _curve_points[0].x = _control_points[0].x;
    _curve_points[0].y = _control_points[0].y;

    // recalculate the primary curve points
    for(auto itr = _curve_points.begin()+1; itr != _curve_points.end()-1; itr++)
    {
        t = _resolution * idx++;

        double x =
              _control_points[0].x * std::pow((1 - t), 3)
            + _control_points[1].x* 3 * std::pow((1 - t), 2) * t
            + _control_points[2].x * 3 * (1 - t) * t * t
            + _control_points[3].x * std::pow(t, 3);
        double y =
              _control_points[0].y * std::pow((1 - t), 3)
            + _control_points[1].y * 3 * std::pow((1 - t), 2) * t
            + _control_points[2].y * 3 * (1 - t) * t * t
            + _control_points[3].y * std::pow(t, 3);
        (*itr).x = x;
        (*itr).y = y;
    }

    _curve_points.back().x = _control_points[3].x;
    _curve_points.back().y = _control_points[3].y;

    // get the tangent points
    std::unique_ptr<std::vector<Point>> tangent_points = RecalculateTangentPoints();
    // recalculate the parallel lines
    RecalculateParallels(tangent_points, _parallels_distance);
}

std::unique_ptr<std::vector<Point>> BezierCurve::RecalculateTangentPoints() const
{
    std::unique_ptr<std::vector<Point>> tangent_points =
            std::unique_ptr<std::vector<Point>>(new std::vector<Point>);


    int size = (int)(1.0F / _resolution + 1);
    std::cout << size << std::endl;
    std::cout << _curve_points.size() << std::endl;

    // start point = initial control point
    Point p;
    p.x = m_derivative_ctrl_pts[0].x;
    p.y = m_derivative_ctrl_pts[0].y;
    tangent_points->push_back(p);
    // calculate the points between 1st and last
    double t = 0.0;
    for (int idx=1; idx<size-1; ++idx)
    {
        t = _resolution * idx;
        Point p;
        p.x = m_derivative_ctrl_pts[0].x * std::pow((1-t),2)
                 + m_derivative_ctrl_pts[1].x * 2 * (1-t) * t
                 + m_derivative_ctrl_pts[2].x * std::pow(t,2);
        p.y = m_derivative_ctrl_pts[0].y * std::pow((1-t),2)
                 + m_derivative_ctrl_pts[1].y * 2 * (1-t) * t
                 + m_derivative_ctrl_pts[2].y * std::pow(t,2);
        tangent_points->push_back(p);
    }
    // end point = last control point
    Point p2;
    p2.x = m_derivative_ctrl_pts[BTS_DERIVATIVE_CTRL_PTS-1].x;
    p2.y = m_derivative_ctrl_pts[BTS_DERIVATIVE_CTRL_PTS-1].y;
    tangent_points->push_back(p2);

    return tangent_points;
}

void BezierCurve::RecalculateParallels(
        const std::unique_ptr<std::vector<Point>> & tangent_points,
        double distance)
{
    double tan_x = 0.0,
           tan_y = 0.0;

    int idx = 0;
    std::cout << tangent_points->size() << std::endl;
    std::cout << _top_left_points.size() << std::endl;

    for(auto itr = tangent_points->begin(); itr != tangent_points->end(); ++itr)
    {
        tan_x = (*itr).x;
        tan_y = (*itr).y;
        double dist = std::sqrt(tan_x * tan_x  + tan_y * tan_y);
        tan_x /= dist;
        tan_y /= dist;

        _top_left_points[idx].x = _curve_points[idx].x + tan_y * distance;
        _top_left_points[idx].y = _curve_points[idx].y - tan_x * distance;

        _bottom_right_points[idx].x = _curve_points[idx].x - tan_y * distance;
        _bottom_right_points[idx].y = _curve_points[idx].y + tan_x * distance;

        ++idx;
    }
}


}
