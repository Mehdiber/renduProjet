#ifndef INTERFACE_H
#define INTERFACE_H

#include <gtkmm.h>
#include <cairomm/context.h>
#include <iostream>
//~ #include <graphic.h>

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

  Gtk::Box Box, Boutons_Box, m_Box_Top, m_Box_Bottom, m_Box_toggle;
  Gtk::Frame Gen, tgl;
  //~ MyArea              m_Area;
  Gtk::Button exit, start, open, step, save, t_link, t_range; 
private:
	void draw();
};

#endif // GTKMM_EXAMPLE_MYEVENT_H
