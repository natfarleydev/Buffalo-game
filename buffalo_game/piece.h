/*
 * =============================================================================
 *
 *       Filename:  piece.h
 *
 *    Description:  A header file for a piece.
 *
 *        Created:  11/02/2011 02:20:17 PM
 *
 *         Author:  Nathanael Farley (), nasfarley88@gmail.com
 *
 * =============================================================================
 */


#ifndef  BUFFALO_PIECE_INC
#define  BUFFALO_PIECE_INC

#include <gtkmm.h>
#include <iostream>

class Piece : public Gtk::EventBox{
	public:
		Piece();
		virtual ~Piece();
		void hello_world();

	protected:
		virtual bool on_eventbox_button_press(GdkEventButton * event);
		int x;
		int y;

};
#endif

