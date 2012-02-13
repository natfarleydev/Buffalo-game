// Dragging boxes around a window

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

using namespace std;
class Buffalo;  // forward declaration of my special box variant
class Dog;
class Indian;
void cpu_buffalo_move();
// I may not need this anymore.
struct new_game_data {bool ai_b;};


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
bool player = 0; // 0 indian; 1 buffalo.
int dead_buffalo = 0;
int buff_blocked = 0;
//bool cpu_indian = 0; // I might implement this later. If I have time



char grid[11][7] = {{'u'}}; // This class is just an Fl_Box that responds to drag-related events
// Ima gonna perfect this, and then BLAM. I'll make the indian and the dogs.
// By copying this class and changing the relative rules. Inherit? I could, but
// then I'd have to work out how to reassign the image.
// TODO The list:
// 	fix the difficulty, allow the user to choose.
// 		three types could be good.
// 		random
// 		robot
// 		mixture: maybe this could be decided by a slider.
// 		advanced: pick the right 'quadrant' but move randomly. Also, if there
// 			is nothing stopping it, go to the penulimate space.
//
// 	about dialog.
// 		I'll probably just make this an fl_message for ease.

struct scalefactor_compt {
	// offset
	int o;
	// width
	int w;
};

struct scalefactor { scalefactor_compt x;
	scalefactor_compt y;
}a;



void grid_cout() {
	for(int i=0; i<7; i++) {
		for(int j = 0; j<11; j++) {
			cout	<< grid[j][i];
		}
		cout << endl;
	}
}

void grid_update(double x, double y, double x2, double y2, char t) {
	if (x != x2 || y != y2) {
		grid[(int)(x/50)][(int)(y/50)] = t;
		grid[(int)(x2/50)][(int)(y2/50)] = 'u';
	}

}

void compare_start_posn_end_posn(double x, double y, double x2, double y2) {
	cout 	<< x << "==" << x2 << " " << y << "==" << y2 << endl;
}

void close_window(Fl_Widget * w, void * data){ ((Fl_Window *)data)->hide(); }
void about_game(Fl_Widget* w, void * data) { 
	fl_message("This game was created for a c++ project for the\nUniversity of Birmingham using FTLK\n\nCreated 2011 by Nathanael Farley\nHave fun!");
}


	
class Buffalo : public Fl_Box {
public:
	Fl_PNG_Image * buffalo_image;
// 	Buffalo(int X, int Y, int W, int H, const char *L) : Fl_Box(X,Y,W,H,L) {
	Buffalo(int X, int Y, int W, int H) : Fl_Box(X,Y,W,H) {
		buffalo_image = new Fl_PNG_Image("buffalo.png");
		this->image(buffalo_image);
	}
// 	Buffalo* operator+ (int i) {
// 		return *this + i * (sizeof(Fl_Box) + sizeof(Fl_PNG_Image));
// 	}

	
private:
	int handle(int event) {
	static int startpos[2] = {0, 0};
	static int p[2] = {0, 0};
	static int offset[2] = {0, 0};
        
        switch (event) {
		case FL_PUSH:
		// record the starting position (top left of box)
		startpos[0] = x(); 
		startpos[1] = y();
			// record where in the box the cursor was when button
			//was pushed
			offset[0] = x() - Fl::event_x();
			offset[1] = y() - Fl::event_y();
			return(1);
		case FL_DRAG:
			// while dragging, update the position of the box to be
			// under the cursor 
			position(Fl::event_x() + offset[0], Fl::event_y() +
				offset[1]);
			mainwin->redraw();
			return(1);
		case FL_RELEASE:
			p[0] = x() - a.x.o;
			p[1] = y() - a.y.o;
			cout	<< endl;
			cout	<< "The current position is " << x() 
			       	<< ", " << y()	<< endl;
			cout	<< "The relative position is " << p[0] 
			       	<< ", " << p[1]	<< endl;

			// This is the snapping.
			if(p[0]%a.x.w< 25) position(x() -p[0]%a.x.w,y());
			if(p[0]%a.x.w>= 25 && x()%a.x.w < 50) 
				position(x() -p[0]%a.x.w + a.x.w,y());
			if(p[1]%a.y.w < 25) position(x(),y() -p[1]%a.y.w);
			if(p[1]%a.y.w >= 25 && y()%a.y.w < 50) 
				position(x(),y() -p[1]%a.y.w + a.y.w);
			
			// redifine for the collision calculation
			p[0] = x() - a.x.o;
			p[1] = y() - a.y.o;

			// Collision issues
			if(grid
				[(int)(p[0]/50)]
				[(int)(p[1]/50)] != 'u')
				position(startpos[0], startpos[1]);
// 			compare_start_posn_end_posn
// 				(x(),y(),startpos[0],startpos[1]);
			
			// Buffalo only rule!
			if(y() != (startpos[1] - 50) || (x() != startpos[0]))
			       	position(startpos[0], startpos[1]);

			// Movement on the grid
			
			// check you haven't put the piece back.
			if(player == 0) {
				position(startpos[0],startpos[1]);
				fl_message("It's not your turn!");
			}
			if(player == 1  && (x() != startpos[0] 
					|| y() != startpos[1])) {
				player = 0;
			}

			// Housekeeping TODO Must come after all else.
			grid_update(x(),y(),startpos[0],startpos[1], 'b');
			grid_cout();
			// Win condition for the buffalo player
			for(int i = 0; i<11; i++) {
				if(grid[i][0] == 'b') {
			if(int i=fl_choice("Buffalos win! Play again?","No",
				"vs. human", "vs. CPU"))
				new_game(i);
				}
			}

			
			mainwin->redraw();
		return(1);
		}
		// If not used for moving, offer the event to the parent
		return Fl_Box::handle(event);
	}
	
};

void check_indian_win_condition() {
	buff_blocked = 0;
	for(int i = 0; i<11; i++) { for(int j = 0; j<7;j++) {
		if(grid[i][j] == 'b') {
			for(int j2 = 0; j2<7;j2++) {
				if(grid[i][j2]=='d') buff_blocked++;
			}
		}
	}}
	if(dead_buffalo >= 7 && buff_blocked == (11-dead_buffalo)) {
	if(int i = fl_choice
		("You protected the village! Play again?",
		 "No", "vs. human", "vs. CPU"))
		new_game(i);
	}
}

class Dog : public Fl_Box {
public:
	Fl_PNG_Image * dog_image;
	Dog(int X, int Y, int W, int H) : Fl_Box(X,Y,W,H) {
		dog_image = new Fl_PNG_Image("dog.png");
		this->image(dog_image);
	}
private:
	int handle(int event) {
	static int startpos[2] = {0, 0};
	static int p[2] = {0, 0};
	static int offset[2] = {0, 0};
        
        switch (event) {
		case FL_PUSH:
		// record the starting position (top left of box)
		startpos[0] = x(); 
		startpos[1] = y();
			// record where in the box the cursor was when button
			//was pushed
			offset[0] = x() - Fl::event_x();
			offset[1] = y() - Fl::event_y();
			return(1);
		case FL_DRAG:
			// while dragging, update the position of the box to be
			// under the cursor 
			position(Fl::event_x() + offset[0], Fl::event_y() +
				offset[1]);
			mainwin->redraw();
			return(1);
		case FL_RELEASE:
			p[0] = x() - a.x.o;
			p[1] = y() - a.y.o;
			if(p[0]%a.x.w< 25) position(x() -p[0]%a.x.w,y());
			if(p[0]%a.x.w>= 25 && x()%a.x.w < 50) 
				position(x() -p[0]%a.x.w + a.x.w,y());
			if(p[1]%a.y.w < 25) position(x(),y() -p[1]%a.y.w);
			if(p[1]%a.y.w >= 25 && y()%a.y.w < 50) 
				position(x(),y() -p[1]%a.y.w + a.y.w);
			
			// redifine for the collision calculation
			p[0] = x() - a.x.o;
			p[1] = y() - a.y.o;

			// Collision issues
			if(grid[(int)(p[0]/50)][(int)(p[1]/50)] != 'u')
			      	position(startpos[0], startpos[1]);

			// Not past the river, dog!
			if(p[1] < 50)position(startpos[0],startpos[1]);
			if(p[1] >= 300)position(startpos[0],startpos[1]);
//			compare_start_posn_end_posn
//				(x(),y(),startpos[0],startpos[1]);
			
			// Dog only rule!
			if(y() - startpos[1] != 0 
				&& x() - startpos[0] != 0 
				&& abs(x() - startpos[0]) 
					!= abs(y() - startpos[1]))
			       	position(startpos[0], startpos[1]);

			// turns. TODO
			if(player == 1) {
				position(startpos[0],startpos[1]);
				fl_message("It's not your turn!");
			}
			if(player == 0  && (x() != startpos[0] 
					|| y() != startpos[1])) {
				player = 1;
			}
			// Movement on the grid
			grid_update(x(),y(),startpos[0],startpos[1], 'd');
			grid_cout();

			check_indian_win_condition();
			cout	<< dead_buffalo << "<< no of dead" << endl;
			
			if(cpu_buffalo == 1) cpu_buffalo_move(); 
			mainwin->redraw();
		return(1);
		}
		// If not used for moving, offer the event to the parent
		return Fl_Box::handle(event);
	}
	
};


class Indian : public Fl_Box {
public:
	Fl_PNG_Image * indian_image;
	Indian(int X, int Y, int W, int H) : Fl_Box(X,Y,W,H) {
		indian_image = new Fl_PNG_Image("indian.png");
		this->image(indian_image);
	}
	void takebuffalo(int,int);
private:
	int handle(int event) {
	static int startpos[2] = {0, 0};
	static int p[2] = {0,0};
	static int offset[2] = {0, 0};
        
        switch (event) {
		case FL_PUSH:
		// record the starting position (top left of box)
		startpos[0] = x(); 
		startpos[1] = y();
			// record where in the box the cursor was when button
			//was pushed
			offset[0] = x() - Fl::event_x();
			offset[1] = y() - Fl::event_y();
			return(1);
		case FL_DRAG:
			// while dragging, update the position of the box to be
			// under the cursor 
			position(Fl::event_x() + offset[0], Fl::event_y() +
				offset[1]);
			mainwin->redraw();
			return(1);
		case FL_RELEASE:
			p[0] = x() - a.x.o;
			p[1] = y() - a.y.o;
			if(p[0]%a.x.w< 25) position(x() -p[0]%a.x.w,y());
			if(p[0]%a.x.w>= 25 && x()%a.x.w < 50) 
				position(x() -p[0]%a.x.w + a.x.w,y());
			if(p[1]%a.y.w < 25) position(x(),y() -p[1]%a.y.w);
			if(p[1]%a.y.w >= 25 && y()%a.y.w < 50) 
				position(x(),y() -p[1]%a.y.w + a.y.w);

			// redifine for the collision calculation
			p[0] = x() - a.x.o;
			p[1] = y() - a.y.o;

			// Collision issues
			if(grid[(int)(x()/50)][(int)(y()/50)] == 'd')  {
				position(startpos[0], startpos[1]);
			}

			// Not past the river, indian!
			if(p[1] < 50)position(startpos[0],startpos[1]);
			if(p[1] >= 300)position(startpos[0],startpos[1]);

			// Indian only rule!
			// Indian movement not there.
			if(y() < (startpos[1] - 50) || (y() > startpos[1]+50)
				|| x() > (startpos[0] + 50) 
				|| (x() < startpos[0]-50)) 
					position(startpos[0], startpos[1]);

			// turns. TODO
			if(player == 1) {
				position(startpos[0],startpos[1]);
				fl_message("It's not your turn!");
			}
			if(player == 0  && (x() != startpos[0] 
					|| y() != startpos[1])) {
				player = 1;
			}

			// TODO make sure this comes after everything else;
			// Movement on the grid
			// AND OBITERATING BUFFALO
			takebuffalo(x(),y());
			grid_update(x(),y(),startpos[0],startpos[1], 'i');
			grid_cout();
			
			check_indian_win_condition();

			if(cpu_buffalo == 1) cpu_buffalo_move();
			grid_cout();
			
			mainwin->redraw();
		return(1);
		}
		// If not used for moving, offer the event to the parent
		return Fl_Box::handle(event);
	}
	
};

void Indian::takebuffalo(int x, int y) {
	Buffalo * take_me;
	if(grid[(int)(x/50)][(int)(y/50)] == 'b') {
		for(int i = 0; i <11; i++) {
			if(herd->child(i)->x() == x 
					&& herd->child(i)->y() == y) {
				take_me = (Buffalo * )herd->child(i);
				take_me->hide();
				dead_buffalo++;
			}
		}
	}
}

void cpu_buffalo_move() {
	// Decide where to move; locate indian
	// left 0 right 1
	bool l0r1 = 0;
	int i; // counter
	int bfo_p[2] ={0,0};
	int successful_move=0; // assume unsuccessful.
	int successful_move_b=0; // assume unsuccessful.
	int range[2] = {0, 10}; // current range of usable buffalo
	int random = rand()%11; // for chosing a random buffalo!
	
	do {
		random = rand()%11;
		// Check indians posn
		if(indian->x()>((range[1]-range[0])*a.x.w/2+range[0])) l0r1 = 0;
		else l0r1 = 1;
		// check if there is a buffalo at the extremities of the range.
//		for(i = 0; i<7; i++) {
//			if(grid[range[l0r1]][i] == 'b') {
//				successful_move = 1;
//				break;
//			}
//		}
		
		for(i = 0; i<7; i++) {
			if(grid[random][i] == 'b') {
				successful_move = 1;
				break;
			}
		}

		// Check if there is a dog there.
		for(i = 0; i<7; i++) {
//			if(grid[range[l0r1]][i]=='d') successful_move = 0;
			if(grid[random][i]=='d' 
					||grid[random][i] == 'i' ) 
				successful_move = 0;
		}
		
		// If the move wasn't successful, try and shorten the range.
		if(successful_move == 0) {
			if(l0r1 == 1) range[l0r1] = range[l0r1]--;
			if(l0r1 == 0) range[l0r1] = range[l0r1]++;
		}
		// If there are no viable buffalo, complain.
		if(range[0] == range[1]) {
			cout << "All the buffalo are dead?!" << endl;
			cout	<< "They will be soon..." << endl;
			// turns out, the player version of this manages just fine.
//			if(int i = fl_choice
//			("CPU loses. Play again?","No", "Yes", "Cancel"))
//				new_game(i);
//			break;
		}
		cout	<< "Range is " << range[0] << ", " << range[1] << endl;
		cout	<< dead_buffalo << "<< no of dead" << endl;
	} while (successful_move == 0);

	// The moving of the piece on the visable board.
//	bfo_p[0] = herd->child(range[l0r1])->x();
//	bfo_p[1] = herd->child(range[l0r1])->y();
//	herd->child(range[l0r1])->position(bfo_p[0],bfo_p[1]-50);

	bfo_p[0] = herd->child(random)->x();
	bfo_p[1] = herd->child(random)->y();
	herd->child(random)->position(bfo_p[0],bfo_p[1]-50);

	// updating the grid; the imaginary, but useful board.
	grid_update(bfo_p[0],bfo_p[1]-50,bfo_p[0],bfo_p[1], 'b');

	grid_cout();

	// the computer will never cheat, so the player can just change
	player = 0;

	for(int i = 0; i<11; i++) {
		if(grid[i][0] == 'b') {
//			fl_message("CPU Wins!");
			if(int i=fl_choice("CPU wins! Play again?","No",
			       	"vs. human", "vs. CPU"))
			       	new_game(i);
		}
	}
}



/*
 * ============================================================================
 *        Class:  Drawing
 *  Description:  This is for drawing the lines
 * ============================================================================
 */
class Drawing : public Fl_Widget {
  public:
  	Drawing(int X,int Y,int W,int H) : Fl_Widget(X,Y,W,H) {}
  private:
	void draw() {
		fl_color(FL_BLACK);
		fl_line_style(0,2);
		for(int i = 1; i <=10; i++) 
			fl_line(i*50,0+a.y.o,i*50,350+a.y.o);
		cout 	<< a.x.o << " " << a.x.o;
		for(int i = 1; i <= 6; i++)
		       fl_line(0,i*50+a.y.o,550,i*50+a.y.o);
		fl_line_style(0);	 // must reset if we changed it
	}
};


void new_game(int i) {
	Fl_Widget * dummy;
	cpu_buffalo = (bool)(i-1);
	new_game(dummy,&cpu_buffalo);
}

void new_game(Fl_Widget * w, void * datavoid) {
	player = 0;
	dead_buffalo = 0;
	int * data = (int * )datavoid;
	cpu_buffalo = *data;

	for(int i=0; i<11; i++) {
		for(int j = 0; j<7; j++) {
			grid[i][j] = 'u';
		}
	}

	for(int i = 0; i<11; i++) {
		buffalo[i]->position(i*a.x.w,6*a.y.w+a.y.o);
		buffalo[i]->show();
		grid[i][6] = 'b';
	}
	
	dog[0]->position(1*a.x.w,a.y.w+a.y.o); grid[1][1] = 'd';
	dog[1]->position(3*a.x.w,a.y.w+a.y.o); grid[3][1] = 'd';
	dog[2]->position(7*a.x.w,a.y.w+a.y.o); grid[7][1] = 'd';
	dog[3]->position(9*a.x.w,a.y.w+a.y.o); grid[9][1] = 'd';

	indian->position(5*50,50+a.y.o); grid[5][1] = 'i';

	if(cpu_buffalo  == 1) mainwin->label("Buffalo - Player vs. CPU");
	if(cpu_buffalo  == 0) mainwin->label("Buffalo - Player vs. Player");
	mainwin->redraw();
}


int main() {
	a.x.o = 0;
	a.x.w = 50;
	a.y.o = 25;
	a.y.w = 50;

	// Use a double-buffered window to prevent all the redraws causing
	//flicker
	mainwin = new Fl_Double_Window(11*a.x.w,7*a.y.w+a.y.o,"Buffalo");
	if(cpu_buffalo  == 1) mainwin->label("Buffalo - Player vs. CPU");
	if(cpu_buffalo  == 0) mainwin->label("Buffalo - Player vs. Player");
	Fl_Box * background_box;
	background_box = new Fl_Box(a.x.o,a.y.o,550,350);
	Fl_PNG_Image * background_image;
	background_image = new Fl_PNG_Image("background.png");
	background_box->image(background_image);
	background_box->show();
	mainwin->color(FL_YELLOW);

	// This is to initilse the grid, the collision detector.
	for(int i=0; i<11; i++) {
		for(int j = 0; j<7; j++) {
			grid[i][j] = 'u';
		}
	}
	Drawing canvas(10,10,300,300);
	Fl_Group herd_real(0,0,11*a.x.w,7*a.y.w+a.y.o);
	herd = &herd_real;

	for(int i = 0; i<11; i++) {
		buffalo[i] = new Buffalo(i*a.x.w,6*a.y.w+a.y.o,a.x.w,a.y.w);
// 		(buffalo++)->position(i*a.x.w,5*a.y.w+a.y.o);
		grid[i][6] = 'b';
	}
	herd_real.end();
// 	cout << herd.children() << endl;
	

	dog[0] = new Dog(1*a.x.w,a.y.w+a.y.o,50,50); grid[1][1] = 'd';
	dog[1] = new Dog(3*a.x.w,a.y.w+a.y.o,50,50); grid[3][1] = 'd';
	dog[2] = new Dog(7*a.x.w,a.y.w+a.y.o,50,50); grid[7][1] = 'd';
	dog[3] = new Dog(9*a.x.w,a.y.w+a.y.o,50,50); grid[9][1] = 'd';

	indian = new Indian(5*50,50+a.y.o,50,50); grid[5][1] = 'i';
	
	int cpu_b = 1;
	int human = 0;
	
	// Menu
	m_menu = new Fl_Menu_Bar(0,0,550,25);
	m_menu->add("&File/&New Game",0, new_game, &human, 0);
	m_menu->add("&File/New Game vs. &CPU",0, new_game, &cpu_b, 0);
	m_menu->add("&File/&Quit",0, close_window);
	m_menu->add("&Help/&About",0, about_game);
	mainwin->end();
	mainwin->show();  

	return Fl::run();
}


