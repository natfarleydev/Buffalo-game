/*
 * =============================================================================
 *
 *       Filename:  indian.h
 *
 *    Description:  A header file for a indian piece.
 *
 *        Version:  1.0
 *        Created:  11/02/2011 08:35:03 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Nathanael Farley (), nasfarley88@gmail.com
 *        Company:  None
 *
 * =============================================================================
 */
#ifndef BUFFALO_INDIANPIECE_INC
#define BUFFALO_INDIANPIECE_INC

#include <gtkmm.h>
#include "piece.h"

class Indian: public Piece {
	public:
		Indian();
	private:
		Gtk::Image indian_image;
};

#endif
