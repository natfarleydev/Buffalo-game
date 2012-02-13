#include<inti/main.h>
#include <inti/core.h>
#include <inti/gtk/button.h>

using namespace Inti;

class DestinationButton : public Gtk::Button
{
protected:
    virtual void on_drag_data_received(Gtk::DragContext& context, int x, int y, const Gtk::SelectionData& data,
                                      unsigned int info, unsigned int event_time);
public:
    DestinationButton(const String& label, const Gtk::TargetEntry& entry);
    virtual ~DestinationButton();
};

class SourceButton : public Gtk::Button
{
    static std::vector<Gtk::TargetEntry> target_entries;

    String target_html;
    String target_string;

protected:
    virtual void on_drag_begin(Gtk::DragContext& context);
    virtual void on_drag_end(Gtk::DragContext& context);
    virtual void on_drag_data_get(Gtk::DragContext& context, Gtk::SelectionData& data,
                                 unsigned int info, unsigned int time);

public:
    SourceButton(const String& label);
    virtual ~SourceButton();
};

class Window : public Gtk::Window
{
public:
    Window();
    virtual ~Window();
};
