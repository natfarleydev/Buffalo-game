/*
 * =============================================================================
 *
 *       Filename:  buffalo.h
 *
 *    Description:  A header file for a buffalo piece.
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
#ifndef BUFFALO_BUFFALOPIECE_INC
#define BUFFALO_BUFFALOPIECE_INC

#include <gtkmm.h>
#include "piece.h"

class Buffalo: public Piece {
	public:
		Buffalo();
	private:
		Gtk::Image buffalo_image;
};

#endif
