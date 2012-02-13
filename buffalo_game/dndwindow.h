#ifndef GTKMM_EXAMPLE_DNDWINDOW_H
#define GTKMM_EXAMPLE_DNDWINDOW_H

#include <gtkmm.h>

class DnDWindow : public Gtk::HBox
{

public:
  DnDWindow();
  virtual ~DnDWindow();

protected:
  //Signal handlers:
  void on_button_drag_data_get(
          const Glib::RefPtr<Gdk::DragContext>& context,
          Gtk::SelectionData& selection_data, guint info, guint time);
  void on_label_drop_drag_data_received(
          const Glib::RefPtr<Gdk::DragContext>& context, int x, int y,
          const Gtk::SelectionData& selection_data, guint info, guint time);

  //Member widgets:
  Gtk::HBox m_HBox;
  Gtk::EventBox m_Button_Drag;
  Gtk::Label m_Label_Drop;
};

#endif // GTKMM_EXAMPLE_DNDWINDOW_H
