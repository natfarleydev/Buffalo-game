// C++ Libraries
#include <cmath>
#include <iostream>
#include <iomanip>
#include <string>
#include <ctime>
#include <cstdlib> 
#include <sstream>

// FLTK Libraries
#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Menu_Bar.H>
#include <FL/Fl_Value_Output.H>
#include <FL/Fl_draw.H>
#include <FL/Fl_Shared_Image.H>
#include <FL/Fl_JPEG_Image.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Text_Display.H>
#include <FL/Fl_Text_Buffer.H>
#include <Fl/Fl_Double_Window.H>

// Custom Libraries
#include "./headerfiles/draw.h"
#include "./headerfiles/callbacks.h"
#include "./headerfiles/card.h"
#include "./headerfiles/deck.h"
#include "./headerfiles/cardimages.h"
#include "./headerfiles/windows.h"

using namespace std;

// Global pointers for the GUI objects

int main() {
	
	// Seed the time for better generation	
	srand (time(0)); 

	// Registering images
	fl_register_images();
		
	// Windows
	setup_windows();
	
	// Assign Images
	image_card_assign();
	
	//Setting up main window (Double buffered)

   	w_main = new Fl_Double_Window(1024, 768,"Caravan");
	                         
    side = new Fl_Box(0,0,200,768);
    side_image = new Fl_JPEG_Image("./images/greenleather.jpg");     
    side->image(side_image);
	
	main_area = new Fl_Box(200,0,824,768);    
    main_area->image(background_image);
	
	discard_area = new Fl_Box(50,644,100,100);
	discard_image = new Fl_JPEG_Image("./images/discard.jpg");
	discard_area->image(discard_image);
	
	// Message Box	  
	statusbox = new Fl_Box(412,748,400,20);
		
	// Drawing the board area
    Draw board(0,0,1024,768);
	
	// Menu bar
	b_menu = new Fl_Menu_Bar(0,0,1024,25);
	b_menu->add("&File/&Load Profile",0,menu_load_cb);
	b_menu->add("&File/&Save Profile",0,menu_save_cb);
	b_menu->add("&File/S&tats",0,menu_displaystats_cb);
	b_menu->add("&Menu/&New Game/Human Vs &Human",0,menu_newgamehvh_cb);
	b_menu->add("&Menu/&New Game/Human Vs &AI",0,menu_newgamehvai_cb);
	b_menu->add("&Menu/&Options",0,menu_options_cb);
	b_menu->add("&Menu/&Quit Game",0,menu_quit_cb);
	b_menu->add("&About/&Rules",0,menu_displayrules_cb);
	b_menu->add("&About/&Credits",0,menu_displaycredits_cb);
	
	// Discard Buttons	  
	b_discard_pile_l = new Fl_Button(125,504,20,20);
	b_discard_pile_l->callback(cb_discard_pile_l);
	b_discard_pile_l->label("X");
	
	b_discard_pile_m = new Fl_Button(125,544,20,20);
	b_discard_pile_m->callback(cb_discard_pile_m);
	b_discard_pile_m->label("X");
	
	b_discard_pile_r = new Fl_Button(125,584,20,20);
	b_discard_pile_r->callback(cb_discard_pile_r);
	b_discard_pile_r->label("X");
	
	// Output boxes displaying values	 
	ai_pile_l = new Fl_Value_Output(85,234,30,20, "Left: ");
	ai_pile_m = new Fl_Value_Output(85,274,30,20, "Middle: ");
	ai_pile_r = new Fl_Value_Output(85,314,30,20, "Right: ");
	
	ai_pile_l->color(FL_GREEN);
	ai_pile_m->color(FL_GREEN);
	ai_pile_r->color(FL_GREEN);
	
	pl_pile_l = new Fl_Value_Output(85,504,30,20, "Left: ");
	pl_pile_m = new Fl_Value_Output(85,544,30,20, "Middle: ");
	pl_pile_r = new Fl_Value_Output(85,584,30,20, "Right: ");
	cards_remaning_title = new Fl_Box(35,464,100,20, "Cards in Deck: ");	
	pl_cards_remaining = new Fl_Value_Output(135,464,30,20);
	
	pl_pile_l->color(FL_GREEN);
	pl_pile_m->color(FL_GREEN);
	pl_pile_r->color(FL_GREEN);
	pl_cards_remaining->color(FL_GREEN);
	
	// Initialising Hands
	Deck pl_hand [8] = {0};
	Deck ai_hand [8] = {0};
	
	// Initialising Piles 
	Deck pl_caravan_l [8] = {0};
	Deck pl_caravan_m [8] = {0};
	Deck pl_caravan_r [8] = {0};
	
	// Initialising Groups	  
	gr_pl_hand = new Fl_Group (200,0,824,768);
	gr_pl_pile_l = new Fl_Group (200,0,824,768);
	gr_pl_pile_m = new Fl_Group (200,0,824,768);
	gr_pl_pile_r = new Fl_Group (200,0,824,768);
		
	cout << " ";
	cout << "\n\nFinished Initialisation\n\n";
	
	// Window refresh
	w_main->show();
		
	// Begin Running
    return Fl::run();
	
}

