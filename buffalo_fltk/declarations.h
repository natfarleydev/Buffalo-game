#include <FL/Fl.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_PNG_Image.H>
#include <FL/fl_draw.H>
#include <FL/fl_ask.H>
#include <FL/Fl_Group.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Menu_Bar.H>
#include <iostream>
#include <cmath>
#include <ctime>

class Buffalo;  // forward declaration of my special box variant
class Dog;
class Indian;
void cpu_buffalo_move();

// global pointers for the gui widgets
Buffalo * buffalo[11];
Fl_Group * herd;
Dog * dog[4];
Indian * indian;
Fl_Window *mainwin;
Fl_Menu_Bar * m_menu;
void new_game(int);
void new_game(Fl_Widget * w, void * datavoid);
// some useful flags
// TODO I'd like to make them static somewhere, but the place to do that would
// be in a piece class. which currently eludes me.
bool cpu_buffalo = 0;
bool player = 1; // 0 indian; 1 buffalo.
int dead_buffalo = 0;
int buff_blocked = 0;
int difficulty = 0;
char grid[11][7] = {{'u'}};

struct scalefactor_compt {
	// offset
	int o;
	// width
	int w;
};

struct scalefactor { scalefactor_compt x;
	scalefactor_compt y;
}a;

void grid_cout();
void grid_update(double x, double y, double x2, double y2, char t);
void close_window(Fl_Widget * w, void * data);
void about_game(Fl_Widget* w, void * data);
void instructions(Fl_Widget * w, void * data);
void check_indian_win_condition();
void cpu_buffalo_move();
void new_game(int i);
