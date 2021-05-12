#include "gui.h"
#include <iostream>

Myevent::Myevent() :
Box(Gtk::ORIENTATION_VERTICAL,10),
m_Box_Bottom(Gtk::ORIENTATION_HORIZONTAL,5),
m_Box_Top(GtK::ORIENTATION_VERTICAL, 0),
Boutons_Box(Gtk::ORIENTATION_VERTICAL, 2),
exit("exit"),
start("start"),
open("open"),
step("step"),
save("save"),
m_Box_toggle(Gtk::ORIENTATION_VERTICAL,2),
t_link("Toggle link"),
t_range("Toggle range"),

tgl.add(m_Box_toggle);
m_Box_toggle.add(t_link);
m_Box_toggle.add(t_range);
tgl.set_label("Toggle display");


Général.add(Boutons_Box);
Boutons_Box.add(exit);
Boutons_Box.add(start);
Boutons_Box.add(open);
Boutons_Box.add(step);
Boutons_Box.add(save);

Bouton.set_label("Général");



void Myevent::open_handler
{
  Gtk::FileChooserDialog dialog("Please choose a file",
          Gtk::FILE_CHOOSER_ACTION_OPEN);
  dialog.set_transient_for(*this);

  //Add response buttons the the dialog:
  dialog.add_button("_Cancel", Gtk::RESPONSE_CANCEL);
  dialog.add_button("_Open", Gtk::RESPONSE_OK);
;

  //Show the dialog and wait for a user response:
  int result = dialog.run();

  //Handle the response:
  switch(result)
  {
    case(Gtk::RESPONSE_OK):
    {
      std::cout << "Open clicked." << std::endl;

      //Notice that this is a std::string, not a Glib::ustring.
      std::string filename = dialog.get_filename();
      std::cout << "File selected: " <<  filename << std::endl;
      break;
    }
    case(Gtk::RESPONSE_CANCEL):
    {
      std::cout << "Cancel clicked." << std::endl;
      break;
    }
    default:
    {
      std::cout << "Unexpected button clicked." << std::endl;
      break;
    }
  }
}
