#include "dndwindow.h"
#include <gtkmm/main.h>

int main (int argc, char *argv[])
{
  Gtk::Main kit(argc, argv);

  DnDWindow dndWindow;
  //Shows the window and returns when it is closed.
  Gtk::Main::run(dndWindow);

  return 0;
}
