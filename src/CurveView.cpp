#include <iostream>
#include <cmath>
#include "CurveView.h"

namespace ByteTrail
{

    static std::valarray<double> dashes(2);

    void SetDashPattern()
    {
        dashes[0] = 4.0;
        dashes[1] = 4.0;
    }


CurveView::CurveView() : _scale(1.0F), _resolution(0.025F),
        _edit_mode(false), _dragging(false), _sections(3)
{

    SetDashPattern();

    int x, y;

    for(int i=0; i<3; i++)
    {
        std::shared_ptr<BezierCurve> curve = std::make_shared<BezierCurve>(BezierCurve());

        if(i == 0 )
        {
            x = std::rand() % 250;
            y = std::rand() % 250;
            curve->SetControlPoint(x, y, 0);
            x = std::rand() % 250;
            y = std::rand() % 250;
            curve->SetControlPoint(x, y, 1);
        }
        else
        {
            const Point p3  = _curves.back()->GetControlPoint(3);
            curve->SetControlPoint(p3.x, p3.y, 0);
            const Point p2 = _curves.back()->GetControlPoint(2);
            std::unique_ptr<Point> p = p2.GetPointFrom(p3);
            curve->SetControlPoint(p->x, p->y, 1);
        }

        x = std::rand() % 250;
        y = std::rand() % 250;
        curve->SetControlPoint(x, y, 2);
        x = std::rand() % 250;
        y = std::rand() % 250;
        curve->SetControlPoint(x, y, 3);

        _curves.push_back(std::move(curve));
    }


    set_events(Gdk::EventMask::BUTTON_PRESS_MASK
               | Gdk::EventMask::BUTTON_MOTION_MASK
               | Gdk::EventMask::BUTTON_RELEASE_MASK);

    signal_button_press_event().connect(sigc::mem_fun(this, &CurveView::on_button_press));
    signal_button_release_event().connect(sigc::mem_fun(this, &CurveView::on_button_release));
    signal_motion_notify_event().connect(sigc::mem_fun(this, &CurveView::on_button_motion));
}

CurveView::~CurveView()
{
    //dtor
}

void CurveView::SetEditMode(bool edit_mode)
{
    if(edit_mode != _edit_mode)
    {
        _edit_mode = edit_mode;
        queue_draw();
    }
}

void CurveView::AddSegement()
{
    _curves.push_back(CreateCurve());
    queue_draw();
}

void CurveView::RemoveSegment()
{
    // undefined behavior if empty
    if(!_curves.empty())
        _curves.pop_back();

    queue_draw();
}

bool CurveView::on_draw(const Cairo::RefPtr<Cairo::Context>& cr)
{
    //Gtk::Allocation allocation = get_allocation();
//    const int width = allocation.get_width();
//    const int height = allocation.get_height();

    // coordinates for the center of the window

    cr->scale(_scale, _scale);

    if(_edit_mode)
    {
        for(auto & curve : _curves)
        {
            for(int i=0; i<4; i++)
            {
                cr->set_source_rgb(0.8, 0.0, 0.0);
                cr->set_line_width(2);
                const Point & current_point = curve->GetControlPoint(i);
                cr->arc(current_point.x, current_point.y, 5, 0.0, 2.0 * 3.14159);
                if( i == 0 || i == 3 )
                    cr->fill();
                else
                {
                    cr->stroke();
                    cr->set_line_width(2);
                    cr->set_source_rgba(1.0, 0.4, 0.0, 0.5);
                    cr->set_dash(dashes, 1.0);
                    cr->set_line_width(2);
                    cr->move_to(current_point.x, current_point.y);
                    Point next_point;
                    if( i == 1)
                    {
                        next_point = curve->GetControlPoint(0);
                    }
                    else
                    {
                        next_point = curve->GetControlPoint(3);
                    }
                    cr->line_to(next_point.x, next_point.y);
                    cr->stroke();
                    cr->unset_dash();
                }
            }
        }
    }
    DrawCurves(cr);

  return true;
}

void CurveView::DrawCurves(const Cairo::RefPtr<Cairo::Context> &cr)
{
     for(auto & curve : _curves)
     {
         DrawCurve(cr, curve);
     }
}

void CurveView::DrawCurve(const Cairo::RefPtr<Cairo::Context>& cr,
        std::shared_ptr<BezierCurve> & curve) const
{
    cr->set_source_rgb(1.0, 0, 0);
    cr->set_line_width(1);

    std::vector<Point> points = curve->GetCurve(1);
    Point & p = points.front();
    for(auto itr = points.begin()+1; itr != points.end(); ++itr)
    {
        cr->move_to(p.x, p.y);
        p = *itr;
        cr->line_to(p.x, p.y);
        cr->stroke();
    }

    cr->set_source_rgb(0, 1.0, 0);
    points = curve->GetCurve(2);
    p = points.front();
    for(auto itr = points.begin()+1; itr != points.end(); ++itr)
    {
        cr->move_to(p.x, p.y);
        p = *itr;
        cr->line_to(p.x, p.y);
        cr->stroke();
    }
}

bool CurveView::on_button_press(GdkEventButton * event)
{
    bool hit = false;
    if(_edit_mode)
    {
        for(auto itr = _curves.begin(); itr != _curves.end(); ++itr)
        {
            auto & curve = *itr;
            for(int i=0; i<4; i++)
            {
                const Point & p = curve->GetControlPoint(i);
                Rect r {p.x-5, p.y-5, 10, 10};
                if(r.Contains(event->x, event->y))
                {
                    _attached_active_curve = nullptr;
                    _dragging = true;
                    _drag_idx = i;
                    if(i == 0 || i == 3)
                        _drag_mode = DragMode::END_POINT;
                    else
                        _drag_mode = DragMode::CENTER_POINT;
                    if( i <= 1&& itr != _curves.begin())
                        _attached_active_curve = *(itr - 1);
                    else if (i >= 2 && itr != _curves.end() - 1)
                        _attached_active_curve = *(itr + 1);
                    _active_curve = curve;
                    hit = true;
                    break;
                }
                if(hit)
                    break;
            }
        }
    }
    return false;
}

bool CurveView::on_button_motion(GdkEventMotion * event)
{
    if(_dragging && _drag_mode == DragMode::END_POINT)
    {
        const Point & p = _active_curve->GetControlPoint(_drag_idx);
        double cx = event->x - p.x;
        double cy = event->y - p.y;
        _active_curve->SetControlPoint(event->x, event->y, _drag_idx);
        Point attached_point;
        if(_attached_active_curve != nullptr)
        {
            if(_drag_idx == 0)
            {
                _attached_active_curve->SetControlPoint(event->x, event->y, 3);
                attached_point = _attached_active_curve->GetControlPoint(2);
                _attached_active_curve->SetControlPoint(attached_point.x + cx, attached_point.y + cy, 2);
                attached_point = _active_curve->GetControlPoint(1);
                _active_curve->SetControlPoint(attached_point.x + cx, attached_point.y + cy, 1);
            }
            else
            {
                _attached_active_curve->SetControlPoint(event->x, event->y, 0);
                attached_point = _attached_active_curve->GetControlPoint(1);
                _attached_active_curve->SetControlPoint(attached_point.x + cx, attached_point.y + cy, 1);
                attached_point = _active_curve->GetControlPoint(2);
                _active_curve->SetControlPoint(attached_point.x + cx, attached_point.y + cy, 2);
            }
        }
       this->queue_draw();
    }
    else if(_dragging && _drag_mode == DragMode::CENTER_POINT)
    {
        const Point & p = _active_curve->GetControlPoint(_drag_idx);
        double cx = event->x - p.x;
        double cy = event->y - p.y;
        _active_curve->SetControlPoint(event->x, event->y, _drag_idx);
        unsigned attached_index = 0;
        if(_drag_idx == 1)
        {
            if(_attached_active_curve !=nullptr)
                attached_index = 2;
        }
        else
        {
            if(_attached_active_curve !=nullptr)
                attached_index = 1;
        }
        if( attached_index != 0 )
        {
            const Point & attached_point = _attached_active_curve->GetControlPoint(attached_index);
            _attached_active_curve->SetControlPoint(attached_point.x - cx,
                                                    attached_point.y - cy,
                                                    attached_index);
        }
        this->queue_draw();
    }
    return false;
}

bool CurveView::on_button_release(GdkEventButton * event)
{
    _dragging = false;
    return false;
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
std::unique_ptr<BezierCurve> CurveView::CreateCurve() const
{
    std::unique_ptr<BezierCurve> curve = std::unique_ptr<BezierCurve>(new BezierCurve());
    double x;
    double y;
    if(_curves.size() == 0)
    {
        x = std::rand() % 250;
        y = std::rand() % 250;
        curve->SetControlPoint(x, y, 0);
        x = std::rand() % 250;
        y = std::rand() % 250;
        curve->SetControlPoint(x, y, 1);
    }
    else
    {
        const Point p3  = _curves.back()->GetControlPoint(3);
        curve->SetControlPoint(p3.x, p3.y, 0);
        const Point p2 = _curves.back()->GetControlPoint(2);
        std::unique_ptr<Point> p = p2.GetPointFrom(p3);
        curve->SetControlPoint(p->x, p->y, 1);
    }
    x = std::rand() % 250;
    y = std::rand() % 250;
    curve->SetControlPoint(x, y, 2);
    x = std::rand() % 250;
    y = std::rand() % 250;
    curve->SetControlPoint(x, y, 3);

    return curve;
}


};
