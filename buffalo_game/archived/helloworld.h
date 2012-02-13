/*
 * =====================================================================================
 *
 *       Filename:  helloworld.h
 *
 *    Description:  A test for hellow world.
 *
 *        Version:  1.0
 *        Created:  11/02/2011 11:55:12 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */


/*-----------------------------------------------------------------------------
 *  I'M SO EXCITED. IT USES INHERITANCE AS STANDARD. STANDARD.
 *-----------------------------------------------------------------------------*/

#ifndef GTKMM_EXAMPLE_HELLOWORLD_H
#define GTKMM_EXAMPLE_HELLOWORLD_H

#include <gtkmm/button.h>
#include <gtkmm/window.h>

class HelloWorld : public Gtk::Window
{

	public:
		HelloWorld();
		virtual ~HelloWorld();

	protected:
		// Signal Handlers
		void on_button_clicked();

		// Member Widgets
		Gtk::Button m_button;
};

#endif // GTKMM_EXAMPLE_HELLOWORLD_H
