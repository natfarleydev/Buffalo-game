/*
 * =============================================================================
 *
 *       Filename:  placeonboard.h
 *
 *    Description:  An eventbox for the place on the board.
 *
 *        Version:  1.0
 *        Created:  11/03/2011 08:59:02 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Nathanael Farley (), nasfarley88@gmail.com
 *        Company:  None
 *
 * =============================================================================
 */

 /* :TODO:11/03/2011 08:59:36 PM:: I might want to make this an HBox just so I
  * can add the river. Maybe. Doing it this way would allow me to make a 
  * background. I'm not sure if gtk allows overlayed images though. Maybe if I 
  * asked really nicely... */


#ifndef  PLACEONBOARD_INC
#define  PLACEONBOARD_INC


#include <gtkmm.h>
#include <iostream>
#include "piece.h"

class PlaceOnBoard : public Gtk::Button {
	public:
		PlaceOnBoard();

	protected:
		void on_eventbox_button_press();
		Gtk::Image placeonboard_image;
		static bool movephase;
		static Piece * piece_in_play;

}; 

#endif 
