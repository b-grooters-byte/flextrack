#include <cmath>
#include <memory>
#include <iostream>
#include <gtkmm.h>
#include "CurveView.h"


int segments;

static ByteTrail::CurveView  *curve_view;
static Gtk::CheckButton *edit_button;
static std::unique_ptr<Gtk::SpinButton> segments_button;
static std::unique_ptr<Gtk::SpinButton> width_button;

void on_button_toggled()
{
   curve_view->SetEditMode(edit_button->get_active());
}

void on_segments_changed()
{
    int delta = segments_button->get_value() - segments;
    if(delta < 0 )
    {
        delta = std::abs(delta);
        for(int i=0; i<delta; ++i)
            curve_view->RemoveSegment();
    }
    else
    {
        for(int i=0; i<delta; ++i)
            curve_view->AddSegement();
    }
    segments = segments_button->get_value();
}

void on_width_changed()
{
    std::cout << "WIDGHT: " << width_button->get_value() << std::endl;
}

int main(int argc, char **argv)
{

    segments = 3;

    Glib::RefPtr<Gtk::Application> app =
            Gtk::Application::create(argc, argv, "org.bytetrail.hexmap");
    Gtk::Window window;
    window.set_default_size(800, 600);
    window.set_title("River Test");

    Gtk::Box h_box(Gtk::ORIENTATION_HORIZONTAL, 4);
    Gtk::Grid grid;

    Gtk::Label label("Segments: ");
    label.set_alignment(Gtk::Align::ALIGN_END);
    grid.attach(label, 0, 0, 1, 1);

    Glib::RefPtr<Gtk::Adjustment> seg_adjustment = Gtk::Adjustment::create(3, 3, 16, 1, 1, 1);
    segments_button = std::unique_ptr<Gtk::SpinButton>(new Gtk::SpinButton());
    segments_button->set_adjustment(seg_adjustment);
    grid.attach(*segments_button, 1, 0, 1, 1);
    segments_button->signal_value_changed().connect(sigc::ptr_fun(&on_segments_changed));

    Gtk::Label label_width("Zoom: ");
    label_width.set_alignment(Gtk::Align::ALIGN_END);
    grid.attach(label_width, 0, 1, 1, 1);

    Glib::RefPtr<Gtk::Adjustment> width_adjustment = Gtk::Adjustment::create(100, 10, 400, 10, 20, 10);
    width_button = std::unique_ptr<Gtk::SpinButton>(new Gtk::SpinButton());
    width_button->set_adjustment(width_adjustment);
    grid.attach(*width_button, 1, 1, 1, 1);
    segments_button->signal_value_changed().connect(sigc::ptr_fun(&on_width_changed));

    edit_button = new Gtk::CheckButton();
    edit_button->set_label("Editing");
    edit_button->set_active(false);
    grid.attach(*edit_button, 0, 2, 2, 1);
    edit_button->signal_toggled().connect(sigc::ptr_fun(&on_button_toggled));

    h_box.pack_end(grid, false, false, 0);
    curve_view = new ByteTrail::CurveView();
    h_box.pack_start(*curve_view, true, true, 0);

    window.add(h_box);
    window.show_all();

    int result = app->run(window);

    return result;
}



