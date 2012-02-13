/*
 * =============================================================================
 *
 *       Filename:  piece.cc
 *
 *    Description:  Yeah. Piece. Innit.
 *
 *        Version:  1.0
 *        Created:  11/02/2011 02:24:22 PM
 *       Compiler:  gcc
 *
 *         Author:  Nathanael Farley (), nasfarley88@gmail.com
 *        Company:  None
 *
 * =============================================================================
 */

#include "piece.h"

Piece::Piece() { 

	
	/*---------------------------------------------------------------------
	 *  The drag and drop beast.
	 *-------------------------------------------------------------------*/
//	std::vector<Gtk::TargetEntry> listTargets;
//	listTargets.push_back( Gtk::TargetEntry("STRING") );
//	listTargets.push_back( Gtk::TargetEntry("text/plain") );
//
//	drag_source_set(listTargets);

	set_events(Gdk::BUTTON_PRESS_MASK);
	signal_button_press_event().connect(
	sigc::mem_fun(*this,&Piece::on_eventbox_button_press) );
//	signal_drag_data_get().connect(sigc::mem_fun(*this,on_button_drag_data_get));


	set_tooltip_text("(position)");

	show();

}

Piece::~Piece() {

}

bool Piece::on_eventbox_button_press(GdkEventButton*) {
	std::cout	<< "YOU PRESSED A PIECE!" << std::endl;
	return true;
}

void hello_world() {
	std::cout << "Hello World." << std::endl;
}

//void Piece::on_button_drag_data_get(
//        const Glib::RefPtr<Gdk::DragContext>&,
//        const Gtk::SelectionData& selection_data, guint, guint)
//{
//  selection_data.set(selection_data.get_target(), 8 /* 8 bits format */,
//          (const guchar*)"I'm Data!",
//          9 /* the length of I'm Data! in bytes */);
//}
