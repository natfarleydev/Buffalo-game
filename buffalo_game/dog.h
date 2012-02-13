/*
 * =============================================================================
 *
 *       Filename:  dog.h
 *
 *    Description:  A header file for a dog piece.
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
#ifndef BUFFALO_DOGPIECE_INC
#define BUFFALO_DOGPIECE_INC

#include <gtkmm.h>
#include "piece.h"

class Dog: public Piece {
	public:
		Dog();
	private:
		Gtk::Image dog_image;
};

#endif
