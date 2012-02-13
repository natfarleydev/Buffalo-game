#include <gtk/gtk.h>
#include <iostream>
#include <cmath>
#include <string>
#include <glib.h>
#include <glib/gprintf.h>
#include <gtkmm.h> 

using namespace std;

/*-----------------------------------------------------------------------------
 *  Defining buff_position
 *  I fully intend to put this in another cpp. But later.
 *-----------------------------------------------------------------------------*/
struct buff_position {
	friend ostream& operator<<(ostream& os, buff_position& temp);
	friend istream& operator>>(istream& is, buff_position& temp);
	int x;
	int y;
	bool operator== (buff_position);
	bool operator% (buff_position);
	buff_position();
	buff_position(int,int);
};

buff_position::buff_position() {
	// People will expect it to be full of 0
	x = 0;
	y = 0;
}

buff_position::buff_position(int i, int j) {
	x = i;
	y = j;
}

bool buff_position::operator== (buff_position param) {
	if ((*this).x == param.x && (*this).y == param.y) {
		//cout << "param.x: " << param.x << " param.y: " << param.y << endl;
		//cout << "(*this).x: " << (*this).x << " (*this).y: " << (*this).y << endl;
		//cout << "It's a match!\n";
		return 0;
	}
	else{
		//cout << "param.x: " << param.x << " param.y: " << param.y << endl;
		//cout << "(*this).x: " << (*this).x << " (*this).y: " << (*this).y << endl;
		//cout << "It's not a match\n";
	       	return 1;
	}
}

bool buff_position::operator% (buff_position param) {
	//cout << "The vectors in question are " << (*this) << " and " << param << endl;
	if (abs((*this).x) ==  abs(param.x) || abs((*this).y) == abs(param.y)) return 0;
	else if((abs((*this).x - param.x) == abs((*this).y -param.y))) return 0;
	else return 1;
}


ostream& operator<< (ostream& os, buff_position& temp) {
	    os << "(" << temp.x << ", " << temp.y << ")";
		return os;
}


istream& operator>> (istream& is, buff_position& temp) {
	    is >> temp.x >> temp.y;
	    cout << "The vector inputted is: " << temp << endl;
		return is;
}



/*
 * ============================================================================
 *       Struct:  Piece
 *  Description:  This is a class for the pieces on the board.
 * ============================================================================
 */

 /* :TRICKY:02/11/11 08:37:47:: When in Rome...
  * I've made this a struct because all of Gtk seems to be a struct at this
  * point. I'm also hoping that putting the GtkImage at the begginging will
  * allow me to point to it, and then cast the pointer as a piece to gain
  * the information inside. */
struct Piece: public Gtk::Image{
	Gtk::Image piece_image;
	buff_position r;
	char name;
	bool player;
	Piece(string,int,int,char,bool);

	Gtk::Image get_image() { return piece_image; };
};

Piece::Piece(string imagename, int i, int j, char namein, bool playerin): Gtk::Image(imagename.c_str()) {
	r.x = i;
	r.y = j;
	namein = name;
	playerin = player;
}

/*-----------------------------------------------------------------------------
 *  The rest of the program.
 *-----------------------------------------------------------------------------*/

void newGame() {
	g_print("This will make a new game.");
}

void aboutBuffalo() {
	g_print("This will be the about function");
}

void quitBuffalo() {
	gtk_main_quit();
}

GtkActionEntry menuentries[] = {
	{ "FileMenuAction", NULL, "_File" },
	{ "HelpMenuAction", NULL, "_Help" },
	
	// Important to remember here, the functions in the xml are upper-
	// case first, and the proper functions are lowercase first
	{ "NewGame", NULL, "_New Game", "<control>N", "Start a new game", G_CALLBACK(newGame) },
	{ "QuitBuffalo", NULL, "_Quit", "<control>Q", "Quit", G_CALLBACK(quitBuffalo) },
	{ "AboutBuffalo", NULL, "_About", "<control>H", "Start a new game", G_CALLBACK(aboutBuffalo) },
};

guint nentries = G_N_ELEMENTS(menuentries);

int main(int argc, char** argv) {
	GtkWidget * window;
	GtkWidget * menubox;
	GtkActionGroup * actiongroup;
	GtkUIManager * menumanager;
	GError * error;
	GtkWidget * menubar;
	GtkWidget * gamezone;
	GtkWidget * eventbox[11][7];
	GtkWidget * testlabel; // This isn't meant to stay, just something to put into the EventBox
	GtkWidget * messagezone;
	GtkWidget * messagetext;
	GtkTextBuffer * messagebuffer;
	GtkWidget * box;
	GtkWidget * buffaloimage;
	GtkWidget * piece[11][7];

	// Not a good idea to start gtk without this line
	// In fact, I'm not sure if it starts without it.
	gtk_init(&argc, &argv);

	// Make the main window
	// TOPLEVEL means that the window manager deals with it
	window  = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(window), "Buffalo");
	gtk_window_set_default_size(GTK_WINDOW(window), 900, 600);
	
	// The menubox, the place to pack the menu
	menubox = gtk_vbox_new(FALSE, 0); // Really should look that FALSE up later
	
	// As everything in gtk does, actions need a box too
	actiongroup = gtk_action_group_new("MainActions");

	// Not sure what this does yet...
	// Maybe it'll be obvious when I have to refer to it later
	// Named reservation after indian reservations
	gtk_action_group_set_translation_domain(actiongroup, "reservation");

	menumanager = gtk_ui_manager_new(); // This shows by itself

	gtk_container_add(GTK_CONTAINER(window), menubox);
	// I need to understand the next two entries thoroughly before I 
	// hand in my report. I don't know how much of the report I will
	// have to take explaining the procedure.
	gtk_action_group_add_actions(actiongroup, menuentries, nentries, NULL);
	gtk_ui_manager_insert_action_group(menumanager, actiongroup, 0);

	// No errors! I certainly don't want random errors showing from
	// unassigned memory
	error = NULL;

	// Load the XML file
	gtk_ui_manager_add_ui_from_file(menumanager, "BuffaloMainMenu.xml", &error);

	// Output errors loading the xml file, if any.
	if(error) {
		g_message ("The menu failed. Gtk says: %s", error->message);
		g_error_free(error);
	}

	// Connect the quit signal. I don't know why gtk doesn't just 
	// have this as the default. Maybe GTK3 does.
	g_signal_connect(window, "destroy", G_CALLBACK(quitBuffalo),NULL);

	// Time to pack the menubar
	menubar = gtk_ui_manager_get_widget(menumanager, "/MainMenu");
	gtk_box_pack_start(GTK_BOX(menubox), menubar, FALSE, FALSE, 0);

	// The notes on the example say, 'Make sure that the accelerators work'
	// What?!
	gtk_window_add_accel_group(GTK_WINDOW(window),gtk_ui_manager_get_accel_group(menumanager));

	// The box to pack in the rest of the game
	box = gtk_hbox_new(FALSE,0);

	// gamezone needs to get it's game on. TODO eventboxes everywhere.
	// Pack it into the vbox created for the menu
	gtk_box_pack_start(GTK_BOX(menubox), box, FALSE,FALSE,0);

	// Create the table for the eventbox (I think that's what they're called)
	gamezone = gtk_table_new(11,7,TRUE);

	// Just indicate I'm done with the table (even though I'm not done packing it)
	gtk_widget_show(gamezone);

	for(int i=0; i<7; i++) {
		for(int j=0;j<11; j++) {
			// Here, I make my eventboxes. They need to be specific, so
			// I'll have to make a smart array of them.
			eventbox[i][j] = gtk_event_box_new();
			gtk_widget_set_usize(eventbox[i][j],50,50);

			// These things are not important, should be cleaned out later
			buffaloimage = gtk_image_new_from_file("buffalo.png");
			testlabel = gtk_label_new("box");

			(Piece)piece[i][j] = Piece("buffalo.png", i, j, 'b', 0);

			gtk_container_add(GTK_CONTAINER(eventbox[i][j]),(piece[i][j]).get_image());
			gtk_widget_show(testlabel);
			
			// TODO Dragndrop test here. I'll need to remove it later.
//			gtk_drag_source_set(eventbox[i][j],GDK_BUTTON1_MASK,gamezone,0,GDK_ACTION_MOVE);
			// Pack it in the table. Yes... the table...
			gtk_table_attach_defaults(GTK_TABLE(gamezone), eventbox[i][j], j, j+1, i, i+1);
				}
	}



	// Hopefully my events window! This will show all the events of the current game
	// Maybe even stay after the game.
	messagetext = gtk_text_view_new();
	messagebuffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(messagetext));
	gtk_text_buffer_set_text(messagebuffer, "This will be the notification area\nI just need to find out to	append to this.", -1);
	gtk_widget_show(messagetext);

	// OK, this is the message zone. The text widget etc. is defined in messagetext and messagebuffer
	messagezone = gtk_scrolled_window_new(NULL,NULL);
	gtk_widget_set_size_request(messagezone,300,600);
	gtk_scrolled_window_add_with_viewport(GTK_SCROLLED_WINDOW(messagezone), messagetext);
	gtk_widget_show(messagezone);

	gtk_box_pack_start(GTK_BOX(box), gamezone, FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(box), messagezone, FALSE, FALSE, 0);
	gtk_widget_show(box);

	// show_all is new!
	gtk_widget_show_all(window);

	// THE moment of a gui program.
	gtk_main();

	return 0;

}

