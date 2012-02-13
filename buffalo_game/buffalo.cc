/*
 * =============================================================================
 *
 *       Filename:  buffalo.cc
 *
 *    Description:  The functions for a buffalo piece. The only real difference
 *    between this and a piece is it's image, and it's move ability.
 *
 *        Version:  1.0
 *        Created:  11/02/2011 08:38:32 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Nathanael Farley (), nasfarley88@gmail.com
 *        Company:  None
 *
 * =============================================================================
 */

#include "buffalo.h"

Buffalo::Buffalo() : buffalo_image("buffalo.png") {
	add(buffalo_image);
	buffalo_image.show();

	
}
