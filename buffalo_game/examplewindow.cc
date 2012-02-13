#include "examplewindow.h"
#include <gtkmm/stock.h>
#include <iostream>

MainWindow::MainWindow()
{
  set_title("Buffalo");
//  set_default_size(400, 400);

  add(m_Box); // put a MenuBar at the top of the box and other stuff below it.

  //Create actions for menus and toolbars:
  m_refActionGroup = Gtk::ActionGroup::create();


  //File menu:
  m_refActionGroup->add(Gtk::Action::create("FileMenu", "File"));
  m_refActionGroup->add(Gtk::Action::create("FileNew", Gtk::Stock::NEW));
  m_refActionGroup->add(Gtk::Action::create("FileQuit", Gtk::Stock::QUIT),
          sigc::mem_fun(*this, &MainWindow::on_menu_file_quit));


  //Help menu:
  m_refActionGroup->add( Gtk::Action::create("HelpMenu", "Help") );
  m_refActionGroup->add( Gtk::Action::create("HelpAbout", Gtk::Stock::HELP ),
          sigc::mem_fun(*this, &MainWindow::on_menu_help) );

  m_refUIManager = Gtk::UIManager::create();
  m_refUIManager->insert_action_group(m_refActionGroup);

  add_accel_group(m_refUIManager->get_accel_group());

  //Layout the actions in a menubar and toolbar:
  Glib::ustring ui_info = 
        "<ui>"
        "  <menubar name='MenuBar'>"
        "    <menu action='FileMenu'>"
        "      <menuitem action='FileNew' />"
        "      <menuitem action='FileQuit'/>"
        "    </menu>"
        "    <menu action='HelpMenu'>"
        "      <menuitem action='HelpAbout'/>"
        "    </menu>"
        "  </menubar>"
        "</ui>";

  try
  {
    m_refUIManager->add_ui_from_string(ui_info);
  }
  catch(const Glib::Error& ex)
  {
    std::cerr << "building menus failed: " <<  ex.what();
  }

  //Get the menubar and toolbar widgets, and add them to a container widget:
  Gtk::Widget* pMenubar = m_refUIManager->get_widget("/MenuBar");
  if(pMenubar)
    m_Box.pack_start(*pMenubar, Gtk::PACK_SHRINK);

  show_all_children();
}

MainWindow::~MainWindow()
{
}

void MainWindow::on_menu_file_quit()
{
  hide(); //Closes the main window to stop the Gtk::Main::run().
}

void MainWindow::on_menu_file_new_generic()
{
   std::cout << "A File|New menu item was selected." << std::endl;
}

void MainWindow::on_menu_help()
{
  std::cout << "This will be the about section." << std::endl;
}

