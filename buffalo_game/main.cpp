/*
 * =============================================================================
 *
 *       Filename:  main.cpp
 *
 *    Description:  This is the 3rd attempt to code the game buffalo in a gui.
 *
 *        Version:  1.0
 *        Created:  11/02/2011 11:45:42 AM
 *       Compiler:  gcc
 *
 *         Author:  Nathanael Farley
 *
 * =============================================================================
 */

#include "examplewindow.h"
#include "piece.h"
#include "buffalo.h"
#include "dog.h"
#include "indian.h"
#include "dndwindow.h"
#include "placeonboard.h"
#include <gtkmm.h>

using namespace Gtk;

/* 
 * ===  FUNCTION  =============================================================
 *         Name:  main
 *  Description:  Whatever I want it to be.
 * ============================================================================
 */
int main ( int argc, char *argv[] ) {

	Main kit(argc, argv);

	MainWindow window;

	  /* :TODO:11/02/2011 02:14:06 PM:: So, ExampleWindow sorts the menu
	   * bar for me, so I don't have to worry about it in the main code.
	   * That just leaves the rest of it. */

	Table 	gamezone(11,7,TRUE);
	PlaceOnBoard place_on_board[11][7];

	Buffalo	buffalo[11];
	Dog	dog[4];
	Indian	indian;

	// Fill the table
	for(int i = 0; i<11; i++){
		for(int j = 0; j<7; j++){
			gamezone.attach(place_on_board[i][j],i,i+1,j,j+1,
					SHRINK,SHRINK, 0, 0);
			place_on_board[i][j].show();
		}

	}

	for(int i = 0; i<11; i++) place_on_board[i][6].add(buffalo[i]);
	
	for(int i = 0; i<11; i++) buffalo[i].show();

	gamezone.attach(dog[0],1,2,1,2,SHRINK,SHRINK,0,0);
	gamezone.attach(dog[1],3,4,1,2,SHRINK,SHRINK,0,0);
	gamezone.attach(dog[2],7,8,1,2,SHRINK,SHRINK,0,0);
	gamezone.attach(dog[3],9,10,1,2,SHRINK,SHRINK,0,0);

	gamezone.attach(indian,5,6,1,2,SHRINK,SHRINK,0,0);
	
//	gamezone.show_all_children();
	gamezone.show();

	window.m_Box.add(gamezone);
	DnDWindow dndwindow;
	window.m_Box.add(dndwindow);

	Main::run(window);

	return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */
