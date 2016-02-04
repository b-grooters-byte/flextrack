#ifndef CURVEVIEW_H
#define CURVEVIEW_H

#include <gtkmm/drawingarea.h>
#include "BezierCurve.h"

#define HEX_MAP_DEFAULT_SECTION         4

namespace ByteTrail
{

using namespace ByteTrail;

enum DragMode
{
    CENTER_POINT,
    END_POINT,
};

class CurveView : public Gtk::DrawingArea
{
    public:
        CurveView();
        virtual ~CurveView();

        void AddSegement();
        void RemoveSegment();
        void SetEditMode(bool edit_mode);

    protected:
        virtual bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr);
    private:
        float _scale;
        float _resolution;
        bool _edit_mode;
        bool _dragging;

        Point _drag_point;
        bool _drag_mode;
        unsigned _drag_idx;
        unsigned _sections;
        std::shared_ptr<BezierCurve> _active_curve;
        std::shared_ptr<BezierCurve> _attached_active_curve;

        std::vector<std::shared_ptr<ByteTrail::BezierCurve>> _curves;

        void RenderCurve(const Cairo::RefPtr<Cairo::Context>& cr,
                         std::shared_ptr<BezierCurve> & curve) const;
        std::unique_ptr<BezierCurve> CreateCurve() const;

        void draw_text(const Cairo::RefPtr<Cairo::Context>& cr);
        void draw_curves(const Cairo::RefPtr<Cairo::Context>& cr);
        void draw_curve(const Cairo::RefPtr<Cairo::Context>& cr, int idx);
        void parallel_curve(const Cairo::RefPtr<Cairo::Context>& cr, gdouble t, gdouble x, gdouble y);

        bool on_button_press(GdkEventButton * event);
        bool on_button_motion(GdkEventMotion * event);
        bool on_button_release(GdkEventButton * event);

};

};

#endif // CURVEVIEW_H
