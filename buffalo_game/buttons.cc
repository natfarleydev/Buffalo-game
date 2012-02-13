/*
 * ============================================================================
 *
 *       Filename:  buttons.cc
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  11/02/2011 12:22:08 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =============================================================================
 */

#include "buttons.h"
#include <iostream>

Buttons::Buttons()
{
	m_button.add_pixlabel("info.xpm", "cool button");

	    set_title("Pixmap'd buttons!");
	      set_border_width(10);

	        m_button.signal_clicked().connect( sigc::mem_fun(*this,
					              &Buttons::on_button_clicked) );

		  add(m_button);

		    show_all_children();
};

Buttons::~Buttons()
{
}

void Buttons::on_button_clicked()
{
	  std::cout << "The Button was clicked." << std::endl;
}
