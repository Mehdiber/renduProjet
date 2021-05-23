#ifndef INTERFACE_H
#define INTERFACE_H

#include <gtkmm.h>
#include <cairomm/context.h>
#include <iostream>
#include "myarea.h"
#include "simulation.h"

//~ class MyArea : public Gtk::DrawingArea
//~ {
//~ public:
//~ MyArea();
//~ virtual ~MyArea();
//~ void clear();
//~ void draw();

//~ protected:
//~ //Override default signal handler:
//~ bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr) override;

//~ private:
//~ bool empty;
//~ void refresh();
//~ };

class MyEvent : public Gtk::Window
{
public:
  MyEvent();
  virtual ~MyEvent();

protected:
  void exit_handler();
  void open_handler();
  void start_handler();
  void step_handler();
  void t_link_handler();
  void t_range_handler();
  bool on_idle();

  Gtk::Box Box, Gen_Box, Boutons_Box, m_Box_Top, m_Box_Bottom, m_Box_toggle;
  Gtk::Frame Gen, tgl;
  //~ MyArea              m_Area;
  Gtk::Button exit, start, open, step, save;
  Gtk::ToggleButton t_link, t_range;
  MyArea canvas;

private:
  void draw();
  void load_simulation();

  bool start_sim{false};

  varglo data;
  geomod::Point pt;
  double r;
};

#endif // GTKMM_EXAMPLE_MYEVENT_H
