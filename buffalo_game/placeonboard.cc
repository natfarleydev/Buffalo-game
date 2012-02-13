/*
 * =============================================================================
 *
 *       Filename:  placeonboard.cc
 *
 *    Description:  This is the class for placeonboard. It shouldn't be more 
 *    than a place for the piece to be held in, and so the user can click on
 *    it to put the piece there.
 *
 *        Version:  1.0
 *        Created:  11/03/2011 09:06:03 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Nathanael Farley (), nasfarley88@gmail.com
 *        Company:  None
 *
 * =============================================================================
 */

#include "placeonboard.h"

PlaceOnBoard::PlaceOnBoard(){

//	add(placeonboard_image);
//	placeonboard_image.show();
	
	set_events(Gdk::BUTTON_PRESS_MASK);

	// This is for an EventBox.
//	signal_button_press_event().connect(

	// This is for a button
	signal_clicked().connect(
	sigc::mem_fun(*this,&PlaceOnBoard::on_eventbox_button_press) );

//	on_clicked(PlaceOnBoard::on_eventbox_button_press);
}


void PlaceOnBoard::on_eventbox_button_press() {
	

	if(this->get_child() !=NULL) { 
		piece_in_play = (Piece *)(this->get_child());
		movephase = 1;

		// Just to prove it's working...
		piece_in_play->hello_world();
	}
	// program adding the piece into the new place.
	// I can use the NULL trick above to check if there is a piece there
	// and then check what kind of piece it is (I think there is way to do
	// that...
	std::cout	<< "movephase is: " << movephase << std::endl;

	// I need this for an EventBox
//	return true;
}
