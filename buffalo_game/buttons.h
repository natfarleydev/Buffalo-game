/*
 * ============================================================================
 *
 *       Filename:  buttons.h
 *
 *    Description:  Etc. etc.
 *
 *        Version:  1.0
 *        Created:  11/02/2011 12:19:14 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * ============================================================================
 */

#ifndef GTKMM_EXAMPLE_BUTTONS_H
#define GTKMM_EXAMPLE_BUTTONS_H

#include <gtkmm/window.h>
#include <gtkmm/button.h>

class Buttons : public Gtk::Window
{
	public:
		Buttons();
		virtual ~Buttons();

	protected:
		// Signal handlers:
		void on_button_clicked();

		// Child widgets:
		Gtk::Button m_button;
};

#endif //GTKMM_EXMAPLE_BUTTONS_H
