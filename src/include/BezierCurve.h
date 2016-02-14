#ifndef BEZIERCURVE_H_INCLUDED
#define BEZIERCURVE_H_INCLUDED

#include <memory>
#include <vector>

#include "Geometry.h"


namespace ByteTrail {

    class BezierCurve {
    public:
        BezierCurve();
        virtual ~BezierCurve();

        float GetResolution() const;
        void SetResolution(float resolution);

        float GetLength() const;
        void  SetLength(float length);

        bool IsFixedLength() const;
        void SetFixedLength( bool fixed_length );

        const Point & GetControlPoint(int index) const;
        void SetControlPoint(const Point & point, unsigned index);
        void SetControlPoint(double x, double y, unsigned index);

        void Move(double cx, double cy);

        const std::vector<Point> & GetCurve(unsigned idx);

        const std::vector<Point> & GetTangentPoints() const;

    protected:
        static constexpr float kDefaultResolution = 0.025;
        static constexpr float kDefaultDistance = 4.5;
        static constexpr float kDefaultLength = 100.0;
        static constexpr unsigned kControlPoints = 4;
        static constexpr unsigned kDerivativeControlPoints = 3;

    private:
        void ResizeCurve();
        void RecalculateCurve();
        std::unique_ptr<std::vector<Point>> RecalculateTangentPoints() const;
        void RecalculateParallels(
                const std::unique_ptr<std::vector<Point>> & tangent_points,
                double distance);


        float _resolution;
        float _length;
        bool _fixed_length;
        float _parallels_distance;

        Point _control_points[kControlPoints];
        Point m_derivative_ctrl_pts[kDerivativeControlPoints];
        std::vector<Point> _curve_points;
        std::vector<Point> _top_left_points;
        std::vector<Point> _bottom_right_points;

        // State fields
        bool _control_point_modified;
        bool _resolution_modified;
    };

}

#endif // BEZIERCURVE_H_INCLUDED
