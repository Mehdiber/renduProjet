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

class Model_columns : public Gtk::TreeModel::ColumnRecord
{
public:
  Model_columns()
  {
    add(_col_id);
    add(_col_nbP);
    add(_col_nbF);
    add(_col_nbT);
    add(_col_nbC);
    add(_col_resource);
    add(_col_resource_percentage);
  }

  Gtk::TreeModelColumn<int> _col_id;
  Gtk::TreeModelColumn<int> _col_nbP;
  Gtk::TreeModelColumn<int> _col_nbF;
  Gtk::TreeModelColumn<int> _col_nbT;
  Gtk::TreeModelColumn<int> _col_nbC;
  Gtk::TreeModelColumn<double> _col_resource;
  Gtk::TreeModelColumn<int> _col_resource_percentage;
};

class MyEvent : public Gtk::Window
{
public:
  MyEvent(int ac, char **av);
  virtual ~MyEvent();

protected:
  void exit_handler();
  void open_handler();
  void start_handler();
  void step_handler();
  void save_handler();
  void t_link_handler();
  void t_range_handler();
  bool on_idle();

  Gtk::Box Box, Gen_Box, Boutons_Box, m_Box_Top, m_Box_Bottom, m_Box_toggle;
  Gtk::Frame Gen, tgl;
  //~ MyArea              m_Area;
  Gtk::Button exit, start, open, step, save;
  Gtk::ToggleButton t_link, t_range;
  MyArea canvas;

  Gtk::ScrolledWindow _scrolled_window;
  Gtk::TreeView _tree_view;
  Model_columns _columns;

private:
  void draw();
  void load_simulation();
  void load_ranges();
  void load_links();
  void tree_view_update();

  bool start_sim{false};
  bool range{false};
  bool link{false};

  varglo data;
};

#endif // GTKMM_EXAMPLE_MYEVENT_H
