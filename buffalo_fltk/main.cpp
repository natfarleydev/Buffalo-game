// Dragging boxes around a window

#include "declarations.h"

using namespace std;

// Incredibly useful for debugging; outputs grid[][] to see
// what the computer is calculating moves from.
void grid_cout() {
	for(int i=0; i<7; i++) {
		for(int j = 0; j<11; j++) {
			cout	<< grid[j][i];
		}
		cout << endl;
	}
}

// designed update the grid[][] based on the gui movements.
void grid_update(double x, double y, double x2, double y2, char t) {
	if (x != x2 || y != y2) {
		grid[(int)(x/50)][(int)(y/50)] = t;
		grid[(int)(x2/50)][(int)(y2/50)] = 'u';
	}

}

void close_window(Fl_Widget * w, void * data){ ((Fl_Window *)data)->hide(); }

void about_game(Fl_Widget* w, void * data) { 
	fl_message("This game was created for a c++ project for the\nUniversity of Birmingham using FTLK\n\nCreated 2011 by Nathanael Farley\nHave fun!");
}

// Windows only function to start the pdf with the default viewer.
void instructions(Fl_Widget * w, void * data) {
	system("start instructions_buffalo.pdf");
}

void check_indian_win_condition() {
	buff_blocked = 0;
	for(int i = 0; i<11; i++) { for(int j = 0; j<7;j++) {
		if(grid[i][j] == 'b') {
			for(int j2 = 0; j2<7;j2++) {
				if(grid[i][j2]=='d' || grid[i][j2] == 'i') 
					buff_blocked++;
			}
		}
	}}
	if(dead_buffalo >= 7 && buff_blocked == (11-dead_buffalo)) {
	int i = fl_choice
		("You protected the village! Play again?",
		 "Exit", "vs. human", "vs. CPU");
		new_game(i);
	}
}

/////////////////////// Buffalo Class /////////////////////////////////////////
class Buffalo : public Fl_Box {
public:
	Fl_PNG_Image * buffalo_image;
	Buffalo(int X, int Y, int W, int H) : Fl_Box(X,Y,W,H) {
		buffalo_image = new Fl_PNG_Image("buffalo.png");
		this->image(buffalo_image);
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
			// relative posn for calculations with grid[][]
			p[0] = x() - a.x.o;
			p[1] = y() - a.y.o;

			// Snap to grid.
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
			
			// Buffalo movement rule.
			if(y() != (startpos[1] - 50) || (x() != startpos[0]))
			       	position(startpos[0], startpos[1]);

			// Is it your turn?
			if(player == 0) {
				position(startpos[0],startpos[1]);
				fl_message("It's the indian's turn!");
			}
			
			// Check if you put it back in the same place
			// If you did, don't change the player.
			if(player == 1  && (x() != startpos[0] 
					|| y() != startpos[1])) {
				player = 0;
			}

			// Housekeeping: update the grid[][] for collision
			// calculation.
			grid_update(x(),y(),startpos[0],startpos[1], 'b');

			// Win condition for the buffalo player
			for(int i = 0; i<11; i++) {
				if(grid[i][0] == 'b') {
					int i=fl_choice
						("Buffalos win! Play again?"
						 ,"Exit","vs. human", "vs. CPU");
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

/////////////////////// Dog Class /////////////////////////////////////////////

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

			// Check for collision
			if(grid[(int)(p[0]/50)][(int)(p[1]/50)] != 'u')
			      	position(startpos[0], startpos[1]);

			// Not past the river, dog! This restricts the movement
			// to only inside the two rivers.
			if(p[1] < 50)position(startpos[0],startpos[1]);
			if(p[1] >= 300)position(startpos[0],startpos[1]);
			
			// Dog movement rules.
			if(y() - startpos[1] != 0 
				&& x() - startpos[0] != 0 
				&& abs(x() - startpos[0]) 
					!= abs(y() - startpos[1]))
			       	position(startpos[0], startpos[1]);
			
			// Check for going through other pieces.
			int xcheck = 0, ycheck = 0;
			xcheck = abs(startpos[0]-x())/50;
			ycheck = abs(startpos[1]-y())/50;

			// I apologise for the lines way longer than 80 chars,
			// there isn't a nice way to show this without time-
			// consuming rewriting of the flow of the program.
			if(xcheck == 0) {
				if(y()-startpos[1] < 0) {
					for(int i = 1; i<=ycheck; i++) {
						if(grid[(int)p[0]/50][(startpos[1]-a.y.o)/50-i] != 'u') {
							position(startpos[0],startpos[1]);
							break;
						}
					}
				}
				else if(y()-startpos[1] > 0) {
					for(int i = 1; i<=ycheck; i++) {
						if(grid[(int)p[0]/50][(startpos[1]-a.y.o)/50+i] != 'u') {
							position(startpos[0],startpos[1]);
							break;
						}
					}
				}
			}
			else if(ycheck == 0) {
				if(x()-startpos[0] < 0) {
					for(int i = 1; i<=xcheck; i++) {
						if(grid[(startpos[0]-a.x.o)/50-i][(int)p[1]/50] != 'u') {
							position(startpos[0],startpos[1]);
							break;
						}
					}
				}
				else if(x()-startpos[0] > 0) {
					for(int i = 1; i<=xcheck; i++) {
						if(grid[(startpos[0]-a.x.o)/50+i][(int)p[1]/50] != 'u') {
							position(startpos[0],startpos[1]);
							break;
						}
					}
				}
			}
			else if(xcheck == ycheck) {
				if(x()-startpos[0] < 0 && y() - startpos[1] < 0) {
					for(int i = 1; i<=xcheck; i++ ){
						if(grid[(startpos[0]-a.x.o)/50-i][(startpos[1]-a.y.o)/50-i] != 'u') {
							position(startpos[0],startpos[1]);
							break;
						}

					}	
				}
				else if(x()-startpos[0] > 0 && y() - startpos[1] < 0) {
					for(int i = 1; i<=xcheck; i++ ){
						if(grid[(startpos[0]-a.x.o)/50+i][(startpos[1]-a.y.o)/50-i] != 'u') {
							position(startpos[0],startpos[1]);
							break;
						}

					}	
				}
				else if(x()-startpos[0] < 0 && y() - startpos[1] > 0) {
					for(int i = 1; i<=xcheck; i++ ){
						if(grid[(startpos[0]-a.x.o)/50-i][(startpos[1]-a.y.o)/50+i] != 'u') {
							position(startpos[0],startpos[1]);
							break;
						}

					}	
				}
				else if(x()-startpos[0] > 0 && y() - startpos[1] > 0) {
					for(int i = 1; i<=xcheck; i++ ){
						if(grid[(startpos[0]-a.x.o)/50+i][(startpos[1]-a.y.o)/50+i] != 'u') {
							position(startpos[0],startpos[1]);
							break;
						}

					}	
				}

			}

			if(player == 1) {
				position(startpos[0],startpos[1]);
				fl_message("It's the buffalo's turn!");
			}
			
			if(player == 0  && (x() != startpos[0] 
					|| y() != startpos[1])) {
				player = 1;
			}
			
			grid_update(x(),y(),startpos[0],startpos[1], 'd');

			check_indian_win_condition();
			cout	<< dead_buffalo << "<< no of dead" << endl;
			
			if(player == 1) {
				if(cpu_buffalo == 1) cpu_buffalo_move();
			}
			
			mainwin->redraw();
		return(1);
		}
		// If not used for moving, offer the event to the parent
		return Fl_Box::handle(event);
	}
	
};

///////////////////////// Indian Class ////////////////////////////////////////

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

			// redefine for the collision calculation
			p[0] = x() - a.x.o;
			p[1] = y() - a.y.o;

			// Check for collision
			if(grid[(int)(x()/50)][(int)(y()/50)] == 'd')  {
				position(startpos[0], startpos[1]);
			}

			// Not past the river, indian!
			if(p[1] < 50)position(startpos[0],startpos[1]);
			if(p[1] >= 300)position(startpos[0],startpos[1]);

			// Indian movement rule.
			if(y() < (startpos[1] - 50) || (y() > startpos[1]+50)
				|| x() > (startpos[0] + 50) 
				|| (x() < startpos[0]-50)) 
					position(startpos[0], startpos[1]);

			if(player == 1) {
				position(startpos[0],startpos[1]);
				fl_message("It's the buffalo's turn!");
			}
			
			if(player == 0  && (x() != startpos[0] 
					|| y() != startpos[1])) {
				player = 1;
			}

			takebuffalo(x(),y());
			grid_update(x(),y(),startpos[0],startpos[1], 'i');
			
			check_indian_win_condition();

			if(player == 1) {
				if(cpu_buffalo == 1) cpu_buffalo_move();
			}
			
			mainwin->redraw();
		return(1);
		}
		// If not used for moving, offer the event to the parent
		return Fl_Box::handle(event);
	}
	
};

// Obvious function. The grid_update function overwrites the buffalo
// naturally as it relies on other code to stop collisions before it 
// is called.
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
	// move on the {left 0, right 1}
	bool l0r1 = 0;
	int bfo_p[2] ={0,0};
	int successful_move=0; // assume unsuccessful.
// 	int successful_move_b=0; // assume unsuccessful.
	int range[2] = {0, 10}; // current range of usable buffalo
	int random = rand()%11; // for chosing a random buffalo!
	int rand_range = 10; // for adv player, decides the range to choose 
				// across.
	int possible_moves = 11; // a check if there are any possible moves left
	int max_tries = 1000; // how many times to try a random piece before giving up
	int tries = 0; // the counter for max_tries
	bool possibles[11] = {0}; // flag for which pieces are movable
	int chosen_buffalo_x = -1; // -1 so I know if it's not chosen properly

	// Decide where to move; locate indian
	if(indian->x()>((range[1]-range[0])*a.x.w/2+range[0])) l0r1 = 0;
	else l0r1 = 1;		

	do {
		random = rand()%11;
		
		successful_move = 0;
		
		if(indian->x()>((range[1]-range[0])*a.x.w/2+range[0])) l0r1 = 0;
		else l0r1 = 1;		
		
		// a switch to choose which buffalo to try and move.
		switch (difficulty) {
			case 0: chosen_buffalo_x = random; tries++; break;
			case 1: chosen_buffalo_x = range[l0r1]; break;
			case 2:
				for(int i = 0; i<11; i++) {
					successful_move = 0;
					for(int j = 0; j<7; j++) {
						if(grid[i][j] == 'b') {
							successful_move = 1;
							break;
						}
					}

					// Check if there is a dog there.
					for(int j = 0; j<7; j++) {
						if(grid[i][j]=='d' 
								||grid[i][j] 
								== 'i' ) 
							successful_move = 0;
					}
					
					if(successful_move == 1) 
						possibles[i] = 1;
					else possibles[i] = 0;
				}
				for(int i = 0; i<11; i++) cout << possibles[i];
				cout << endl;
				
				// Assume failure, if there's a piece that can 
				// move, it will.
				successful_move = 0;
				if(l0r1 == 0) {
					for (int i = 0; i<=300; i++) {
						random = rand()%6;
						cout << random << endl;
						if(possibles[random]==1) {
							chosen_buffalo_x 
								= random;
							successful_move = 1;
							break;
						}
					}
					
					
					if(successful_move == 0) {
						for (int i = 0; i<=300; i++) {
							random = 5+rand()%6;
							if(possibles[random]==1) {
								chosen_buffalo_x = random;
								successful_move = 1;
								break;
							}
						}
					}
					
				}
				
				else {
					for (int i = 0; i<=300; i++) {
						random = 5+rand()%6;
						cout << random << endl;
						if(possibles[random]==1) {
							chosen_buffalo_x = random;
							successful_move = 1;
							break;
						}
					}
					
					if(successful_move == 0) {
						for (int i = 0; i<=300; i++) {
							random = rand()%6;
							if(possibles[random]==1) {
								chosen_buffalo_x = random;
								successful_move = 1;
								break;
							}
						}
					}
				}
				
				// If the buffalo is just about the cross the river, do it!
				for(int i = 0; i<11; i++) {
					if(grid[i][1] == 'b') {
						chosen_buffalo_x = i;
						successful_move = 1;
						break;
					}
				}
				
				if(successful_move == 0) {
					for(int i = 0; i<11; i++) {
						if(possibles[i] == 1) {
							chosen_buffalo_x = i;
							successful_move = 1;
							break;
						}
					}
				}
				
				// If it gets to the end of this and can't move,
				// there is no way to win, and the difficulty
				// 0 should give the desired win condition
				if(successful_move == 0) {
					difficulty = 0;
					chosen_buffalo_x = 0;
				}
		}
		int look_ahead = 0; // just so the buffalo doesn't get scared 
				//when the dog is behind it.
				
		// Check a buffalo is in the chosen spot.
		for(int i = 0; i<7; i++) {
			if(grid[chosen_buffalo_x][i] == 'b') {
				successful_move = 1;
				look_ahead = i;
				break;
			}
		}

		// Check if there is a dog/indian ahead.
		for(int i = 0; i<look_ahead; i++) {
			if(grid[chosen_buffalo_x][i]=='d' 
					||grid[chosen_buffalo_x][i] == 'i' ) 
				successful_move = 0;
		}
		
		// If the move wasn't successful, try and shorten the range.
		// only do it if difficuly is not on random
		if(successful_move == 0 && difficulty !=0) {
			possible_moves--;
			if(l0r1 == 1) range[l0r1] = range[l0r1]--;
			if(l0r1 == 0) range[l0r1] = range[l0r1]++;
		}
		// If there are no viable buffalo, complain.
		if(range[0] > range[1] || possible_moves <= 0 
				|| tries >= max_tries) {
			cout << "All the buffalo are dead?!" << endl;
			cout	<< "There are no more possible moves!" << endl;
			cout	<< "barring stupidity on the side of the indian,"
				<< "the village is safe" << endl;
			int k = fl_choice
				("You protected the village! Play again?",
				 "Exit", "vs. human", "vs. CPU");
			new_game(k);
			break;
		}
		cout	<< "Range is " << range[0] << ", " << range[1] << endl;
		cout	<< dead_buffalo << "<< no of dead" << endl;
	} while (successful_move == 0);

	bfo_p[0] = herd->child(chosen_buffalo_x)->x();
	bfo_p[1] = herd->child(chosen_buffalo_x)->y();
	herd->child(chosen_buffalo_x)->position(bfo_p[0],bfo_p[1]-50);

	// updating the grid; the imaginary, but useful board.
	grid_update(bfo_p[0],bfo_p[1]-50,bfo_p[0],bfo_p[1], 'b');


	// the computer will never cheat, so the player can just change
	player = 0;

	for(int i = 0; i<11; i++) {
		if(grid[i][0] == 'b') {
			int i=fl_choice("CPU wins! Play again?","Exit",
			       	"vs. human", "vs. CPU");
			       	new_game(i);
				break;
		}
	}
}

/////////////////////// Drawing Class /////////////////////////////////////////
// Just for drawing the lines in fltk. This also provides a framework for the 
// board if the images are not found for some reason.
// This class is based on code found on WebCT
///////////////////////////////////////////////////////////////////////////////
class Drawing : public Fl_Widget {
  public:
  	Drawing(int X,int Y,int W,int H) : Fl_Widget(X,Y,W,H) {}
  private:
	void draw() {
		fl_color(FL_BLACK);
		fl_line_style(0,2);
		for(int i = 1; i <=10; i++) 
			fl_line(i*50,0+a.y.o,i*50,350+a.y.o);
		for(int i = 1; i <= 6; i++)
		       fl_line(0,i*50+a.y.o,550,i*50+a.y.o);
		fl_line_style(0);
	}
};


void new_game(int i) {
	Fl_Widget * dummy;
	cout << "new_game's int is " << i << endl;
	cpu_buffalo = (bool)(i-1);
	if(i == 0) mainwin->hide();
	if(cpu_buffalo != -1) new_game(dummy,&cpu_buffalo);
}

void difficulty_chooser(Fl_Widget *,void *);
void difficulty_chooser(int i);
void new_game(Fl_Widget * w, void * datavoid) {
	player = 1;
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

	if(cpu_buffalo  == 1) {
	  difficulty_chooser(difficulty);
	  cpu_buffalo_move();
	}
	if(cpu_buffalo  == 0) mainwin->label("Buffalo - Player vs. Player");
	mainwin->redraw();
}

void difficulty_chooser(int i) {
	Fl_Widget * dummy;
	difficulty_chooser(dummy,&difficulty);
}

void difficulty_chooser(Fl_Widget * w, void * data) {
	difficulty = *((int *)(data));
	if(cpu_buffalo == 1) {
		switch(difficulty){
			case 0: mainwin->label
				("Buffalo - Player vs. CPU (easy)"); break;
			case 1: mainwin->label
				("Buffalo - Player vs. CPU (medium)"); break;
			case 2: mainwin->label
				("Buffalo - Player vs. CPU (hard)"); break;
		}
	}
}


int main() {
	srand(time(0));
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
	

	// The duplicity of herd_real and herd here is needed fltk.
	// fltk complains if it's not a pointer.
	Fl_Group herd_real(0,0,11*a.x.w,7*a.y.w+a.y.o);
	herd = &herd_real;
	
	for(int i = 0; i<11; i++) {
		buffalo[i] = new Buffalo(i*a.x.w,6*a.y.w+a.y.o,a.x.w,a.y.w);
		grid[i][6] = 'b';
	}
	herd_real.end();

	dog[0] = new Dog(1*a.x.w,a.y.w+a.y.o,50,50); grid[1][1] = 'd';
	dog[1] = new Dog(3*a.x.w,a.y.w+a.y.o,50,50); grid[3][1] = 'd';
	dog[2] = new Dog(7*a.x.w,a.y.w+a.y.o,50,50); grid[7][1] = 'd';
	dog[3] = new Dog(9*a.x.w,a.y.w+a.y.o,50,50); grid[9][1] = 'd';

	indian = new Indian(5*50,50+a.y.o,50,50); grid[5][1] = 'i';
	
	int cpu_b = 1;
	int human = 0;
	int easy = 0;
	int medium = 1;
	int hard = 2;
	
	// Menu
	m_menu = new Fl_Menu_Bar(0,0,550,25);
	m_menu->add("&File/&New Game vs. human",0, new_game, &human, 0);
	m_menu->add("&File/New Game vs. &CPU",0, new_game, &cpu_b, 0);
	m_menu->add("&File/&Quit",0, close_window, mainwin,0);
	m_menu->add("&Difficulty/&Easy",0, difficulty_chooser, &easy, 0);
	m_menu->add("&Difficulty/&Medium",0, difficulty_chooser, &medium, 0);
	m_menu->add("&Difficulty/&Hard",0, difficulty_chooser, &hard, 0);
	m_menu->add("&Help/&Instructions (Opens pdf)",0, instructions);
	m_menu->add("&Help/&About",0, about_game);
	mainwin->end();
	mainwin->show();  

	new_game(2);
	return Fl::run();
}


