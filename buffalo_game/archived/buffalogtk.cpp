/*
 * =====================================================================================
 *
 *       Filename:  buffalo.cpp
 *
 *    Description:  This is a game called buffalo. I am very familiar with
 *    the rules now. I'm just sick of FLTK so I'm going to make this in the
 *    terminal to start with, and then see if I can adapt it from there.
 *
 *        Version:  1.1
 *        Created:  10/18/2011 05:42:11 PM
 *       Compiler:  gcc
 *
 *         Author:  Nathanael Farley, 
 *
 * =====================================================================================
 */

// TODO WEll, thisngs have gone well for this session. I need to
// 	Dogs can move through stuff, that shouldn't happen
// 	cout's need cleaning up
//
 /* :TODO:29/10/11 22:09:57:: Well, as admirable as the button idea was, it progressively
  * became more and more complicated, duplicating information all over the place. I 
  * really need to get inheritance down, make each piece a GtkWidget, and then this will
  * allow me to move the piece without an incredible amount of duplicate information.
  *
  * This means I need to master Gtk sharpish. */


/*-----------------------------------------------------------------------------
 *  This is a list of all the things I could include.
 *  Fixed containers could be used. They are really easy to move codewise.
 *  Scrolled Windows will be pretty essential for the event area.
 *  ItemFactory is the way forward for menus. I will probably set that up first. Just so I know.
 *  	Or at least I would. If they hadn't depreciated. The `hard way' it is!
 *  Apparently 1 is TRUE. Apart from at the end of a program. GREAT.
 *-----------------------------------------------------------------------------*/

#include <iostream>
#include <cmath>
#include <gtk/gtk.h>

using namespace std;


/*-----------------------------------------------------------------------------
 *  Global Declarations
 *-----------------------------------------------------------------------------*/
int movephase = 0; // This is to tell the program what phase of move it's at: identify piece or move piece already chosen.

struct position { 
	friend ostream& operator<<(ostream& os, position& temp);
	friend istream& operator>>(istream& is, position& temp);
	int x;
	int y;
	bool operator== (position);
	bool operator% (position);
	position();
};

position::position() {
	// People will expect it to be full of 0
	x = 0;
	y = 0;
}

bool position::operator== (position param) {
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

bool position::operator% (position param) {
	//cout << "The vectors in question are " << (*this) << " and " << param << endl;
	if (abs((*this).x) ==  abs(param.x) || abs((*this).y) == abs(param.y)) return 0;
	else if((abs((*this).x - param.x) == abs((*this).y -param.y))) return 0;
	else return 1;
}



class Piece {
	// TODO research about scopes. Why wouldn't a function in Piece allow me to use a global function?!
	friend ostream& operator<<(ostream& os, Piece& temp);
	friend Piece* identifypointer(Piece * temp, position testr);
	friend char identifychar(Piece * temp, position testr) ;
	position r;
	char name;
	bool player; // Player 0 or 1, so that the other player can't move the
		     // other piece.
	public:
	Piece(int,int,char,bool);
	Piece(); // An empty one for good measure.
	Piece* operator+ (int);
	int move(Piece * collisiontestpointer);
	int movebuffalo(Piece * collisiontestpointer);
	int killbuffalo(Piece * collisiontestpointer, position testr);
	int movedog(Piece * collisiontestpointer);
	int moveindian(Piece * collisiontestpointer);
	int collision(Piece * collisiontestpointer, position testr);
///	void identify(Piece* temp);
	position getr() { return r; };
	char gettype() { return name; };
} many[17];

// I know this is awful practice, but I don't know another way to make 
// this globally reckognised without making it global.
Piece * pointermany = many;

struct briefcase { Piece * piecepointer; bool player; position r;} carryon[11][7];

briefcase * carryonpreviouspointer = &(carryon[0][0]);

Piece::Piece(int a, int b, char c, bool d) {
	r.x = a;
	r.y = b;
	name = c;
	player = d;
}

// The empty one, so I an define a grid of them to start with
Piece::Piece() {
	r.x = 0;
	r.y = 0;
	name = 'e';
	player = 0;
}

int Piece::move(Piece * collisiontestpointer) {
	int a,b;
	
	// I should really have some kind of piece detection here. I'd like to use
	// those sub class things here.
	cout << "Give the x co-ordinate then y co-ordinate you wish to move to: ";
	cin >> a >> b;
	position testr;
	testr.x = a;
	testr.y = b;
	// Collision detection. For this, I need the same pointer from identify.
		for(int i = 0 ; i <= 15; collisiontestpointer = collisiontestpointer + 1 ) {
			cout << *collisiontestpointer << endl;
			if (((*collisiontestpointer).getr() == testr) == 0) {
				cout << "Someone is already there. Sucks for you." << endl;
				return 1;
			}
			i++;
		}
	(*this).r.x = a;
	(*this).r.y = b;
	//cout << "You just moved to (" << (*this).r.x << ", " << (*this).r.y << ").\n";
	return 0;
}

int Piece::movebuffalo(Piece * collisiontestpointer) {
	position testr = (*this).getr();
	position buffalor = testr; // TODO find out why g++ complains if this is a const.
	cout << buffalor << " or " << testr;
	//cout << "PARTY ANIMAL "<< testr;
	// counter for this.
	if (testr.y == 0) {
		cout << "This buffalo is already safe" << endl;
		return 1;
	}
	testr.y--; // Because I want to test the square before it

	if ((*this).collision(collisiontestpointer,testr)==1) return 1;
	else {
		cout << "Move the buffalo at " << buffalor << "?";
		cout	<< "Assumed yes" << endl;
		(*this).r.y--;
		carryon[testr.x][testr.y-1].piecepointer = this;
		carryon[testr.x][testr.y].piecepointer = &many[16];
		cout << "Move successful" << endl;
		return 0;
	}
	// if it got this far, it really failed
	return 1;

}

int Piece::killbuffalo(Piece * collisiontestpointer, position testr) {
	// The indian does this
	Piece * buffalovictim = identifypointer(collisiontestpointer,testr);
	(*buffalovictim).r.x = -1;
	(*buffalovictim).r.y = -1;
	cout << "The buffalo at " << testr << " has been OBLITERATED." << endl;
	return 0;
}
int Piece::movedog(Piece * collisiontestpointer) {
	position testr = (*this).getr(); // Using a test variable is neater than 
					// putting (*this).r everywhere
	position dogr = testr; // see buffalo equivilent


	bool illegalmoveflag = 1; // Assume moves are legal until checked
	do{
		illegalmoveflag = 1; // Assume the next move will be legal
		cout << "Where would you like to move this dog? ";
		cin >> testr;
		// test if move is like a chess queen.
		if (testr%dogr == 1) illegalmoveflag = 0;
	} while (illegalmoveflag==0);
	if ((*this).collision(collisiontestpointer,testr)==1) return 1;
	else {
		(*this).r = testr;
		return 0;
	}
	
}

int Piece::moveindian(Piece * collisiontestpointer) {
	position testr = (*this).getr();
	position indianr = testr;

	bool illegalmoveflag = 1; // Assume moves are legal until checked
	do {
		illegalmoveflag = 1; // Assume the next move will be legal
		cout << "Where would you like to move, Chief?";
		cin >> testr;

		// Test if the move is a straight line.
		if (testr%indianr == 1) { cout << "That's not a striaght line!" << endl; illegalmoveflag = 0;}
		if (abs(testr.x - indianr.x) > 1 || abs(testr.y - indianr.y) > 1) { cout << "Too far!" << endl; illegalmoveflag = 0;}
	} while(illegalmoveflag==0);
	if ((*this).collision(collisiontestpointer,testr)==1) {
		if ((identifychar(collisiontestpointer,testr))=='b') {
			(*this).killbuffalo(collisiontestpointer,testr);
			(*this).r = testr;
			return 0;
		} else illegalmoveflag = 0;	
	} else {
		(*this).r = testr;
		return 0;
	}
	return 1;
}

// Perhaps I should invest in a vim plugin for commenting
int Piece::collision(Piece * collisiontestpointer, position testr) {
	
	// out of bounds check
	// The check is type specific. One day, I'll have classes here.
	if((*this).gettype() != 'b'){
		if (testr.x < 0 || testr.x > 15 || testr.y < 1 || testr.y > 7) {
			cout << "Out of bounds." << endl;
			return 1;
		}
	} else if ((*this).gettype() == 'b'){
		if (testr.x < 0 || testr.x > 15 || testr.y < 0 || testr.y > 8) {
			cout << "Out of bounds." << endl;
			return 1;
		}
	}

	// I'll implement the indian thing here. Maybe... sub class of collsion for the indian?
	// sub classes would mean that the buffalo wouldn't need an out of bounds check;
	// out of bounds is already checked in move.
	// It would also allow for the different bounds of the buffalo and the rest

	for(int i = 0 ; i <= 15; collisiontestpointer = collisiontestpointer + 1 ) {
		cout << *collisiontestpointer << endl;
		if (((*collisiontestpointer).getr() == testr) == 0) {
			cout << "Someone is already there. Sucks for you." << endl;
			return 1;
		}
		i++;
	}


	//cout << "You can move there.";
	return 0; // Assume success if the func got to the end
}

Piece * Piece::operator+ (int i) {
	return *this + i * (2*sizeof(int) + sizeof(char) + sizeof(bool));
}

/* I've abandoned this bit, at least for now, because I don't understand how to implement
 * the inheritance. I'll probably have to change how they are stored in the first place.
 *
 * Thinking about it, I might be able to get away with it if I make an array of pointers, 
 * and just point all the pointers to the pointer array. Hopefully. I'll read a little more
 * about it before implementation. This way looks way neater tbh.
 * 
class Buffalo: public Piece {
	// As the point of this class is to contain this function
	// I may as well define it here!
	public:
		int move(Piece ** collisiontestpointer) {
			(*this)
		}
*/

Piece* identifypointer(Piece * temp, position testr) {
	// This identify is given a position and gives a pointer to the
	// object at this point
	
	for(int i = 0 ; i <= 15; temp = temp + 1 ) {
		if (((*temp).getr() == testr) == 0) return temp;
		i++;
	}
	return 0; 
	
}

char identifychar(Piece * temp, position testr) {
	for(int i = 0 ; i <= 15; temp = temp + 1 ) {
		if (((*temp).getr() == testr) == 0) return (*temp).gettype();
		i++;
	}
	return 'u'; // 'u' for unoccupied
}

//void identify(Piece * temp, int player, position testr) {
//	// this will be easily extendable to have buttons on all the grid squares for 
//	// FLTK to enter the co-ordinates (I hope!)
//	//
//	// This function could have an extra piece of information to forward the information
//	// on to a new function i.e. int forwarder and then forwarder could be 0 for move,
//	// 1 for give to the board etc.
//	int movesuccessflag = 0;
////	position testr; 
//	Piece * collisiontestpointer;
//	Piece * tempbeginning;
//	tempbeginning = temp; // Because I need the beggining of the array to pass to move
//	collisiontestpointer = tempbeginning;
//	cout << "You've called the identify function\n";
//	// This switch is now how to choose player.
//	movesuccessflag = 0; // assume success until told otherwise.
//	
//	// This loop allows the user to try again if they try to move but ends up in a collision
//	do {
//
//		/*-----------------------------------------------------------------------------
//		 *  This is replaced by gtk, I'm hoping!
//		 *-----------------------------------------------------------------------------*/
///* 		testr.x = 0;
// * 		testr.y = 0;
// * 		if(movesuccessflag==1) cout << "That move wasn't successful." << endl;
// * 		movesuccessflag = 0; // Assume the next move will be successful
// * 		cout << "Player " << (int)player + 1 << ": " << endl;
// * 		cout << "Please enter co-ordinates of the piece you wish to use: ";
// * 		cin >> testr; // Hopefully this'll be replaced by a gui function eventually
// */
//		temp = tempbeginning; // Because the loop needs temp to reset
//		for(int i = 0 ; i <= 15; temp = temp + 1 ) {
//			if (((*temp).getr() == testr) == 0){
//				// check who it is and move them
//				if ((*temp).gettype() == 'b'){
//					movesuccessflag = (*temp).movebuffalo(collisiontestpointer); 
//					if(movesuccessflag == 0) break; // stop after a successful move
//				}
//				else if ((*temp).gettype() == 'd') {
//					movesuccessflag = (*temp).movedog(collisiontestpointer); 
//					if(movesuccessflag == 0) break; // stop after a successful move
//				}
//				else if ((*temp).gettype() == 'i') {
//					movesuccessflag = (*temp).moveindian(collisiontestpointer); 
//					if(movesuccessflag == 0) break; // stop after a successful move
//				}
//				else{
//					cout << "That piece isn't yours! Try again." << endl;
//					movesuccessflag = 1; 
//				}
//			} else { movesuccessflag = 1; } // fail if the user didn't put in a proper number	
//			i++;
//		}
//	} while (movesuccessflag==1);
//}


void identifycallback(GtkWidget * widget, void * data) {

	position testr = (*((briefcase *)data)).r;
	briefcase testluggage = *(briefcase *)data;
	pointermany = &many[0];
	testluggage.piecepointer = pointermany;
	cout	<< "The value of testr is: " << testr << "." << endl;
//	cout	<< "The value at pointermany is " << *pointermany << endl;
	int movesuccessflag = 0;
	// testr is going to be pointed in.
	Piece * collisiontestpointer;
	//Piece * tempbeginning;
	// This needs to be pointed properly
	collisiontestpointer = &many[0];// I may replace this variable with &many[0] now that I understand how to use it.
//	cout << "You've called the identifycallback function\n";
	// This switch is now how to choose player.
	movesuccessflag = 0; // assume success until told otherwise.
	
	// This loop allows the user to try again if they try to move but ends up in a collision
	do {
		for(int i = 0 ; i <= 15; i++) {
//			cout	<< "You've entered the for loop that checks all the pieces" << endl;

			/*-----------------------------------------------------------------------------
			 *  First phase of a turn
			 *-----------------------------------------------------------------------------*/
			if (((*pointermany).getr() == testr) == 0 && movephase == 0){

				// If it needs resetting, reset it!
				carryonpreviouspointer = &(carryon[0][0]);
				// check who it is and move them
				if ((*pointermany).gettype() == 'b'){
					movephase = 1;
					cout	<< "testluggage is full of " << *(testluggage.piecepointer) << endl;
					break;
				}
				else if ((*pointermany).gettype() == 'd') {
					testluggage.piecepointer = &many[i]; movephase = 1;
					cout	<< "testluggage is full of " << *(testluggage.piecepointer) << endl;
					break;
				}
				else if ((*pointermany).gettype() == 'i') {
					testluggage.piecepointer = &many[i]; movephase = 1;
					cout	<< "testluggage is full of " << *(testluggage.piecepointer) << endl;
					break;
				}
				else{
					cout << "That's empty." << endl;
					movesuccessflag = 1; 
				}


				cout	<< "The piece at this point is a " << pointermany->gettype()<< endl;
				position justfornow = (*pointermany).getr();
				cout	<< "The testr that was matched was " << justfornow << "and" << testr << endl;
				
			} 

			
			/*-----------------------------------------------------------------------------
			 *  Second phase of a turn
			 *-----------------------------------------------------------------------------*/

			if((pointermany->getr() == testr) == 1 && movephase == 1 && pointermany->getr()%testr) {
				// I could incorporate collisions here, it would check if there was anything valid 
				// 'in' the button, i.e. the carryon.
				if((*pointermany).gettype() == 'b') pointermany->movebuffalo(collisiontestpointer);
				
				movephase = 0;

			}
			pointermany = pointermany + 1;
			carryonpreviouspointer = carryonpreviouspointer + sizeof(carryon);
		}
		cout	<< "movephase == " << movephase << endl;
	} while (movesuccessflag==1);
}
ostream& operator<< (ostream& os, position& temp) {
	    os << "(" << temp.x << ", " << temp.y << ")";
		return os;
}
ostream& operator<< (ostream& os, Piece& temp) {
	    os << "(" << temp.r.x << ", " << temp.r.y << ", " << temp.name << ", " << temp.player << ")";
		return os;
}

istream& operator>> (istream& is, position& temp) {
	// This operator breaks iff you put -2 for temp.y. other negative numbers are fine
	// and -2 in temp.x is fine too. Haven't tried it outside of identify() yet
	// FLTK should get rid of any problems of the user trying to put that in though.
	    is >> temp.x >> temp.y;
	    cout << "The vector inputted is: " << temp << endl;
		return is;
}


/* void checkcontent(GtkWidget * widget, void * data) {
 * 	briefcase testluggage2 = *(briefcase *)data;
 * 	cout	<< "The piece picked up was " << *(testluggage2.piecepointer) << endl;
 * }
 */

int main( int argc, char * argv[]) {
	int count = 0; // To count how many buffalo are safe.
	bool player = 1;
	position testr;  /* :TODO:29/10/11 12:50:55:: Check this is initialised to something sensible */

	// 16 is for the unoccupied one, so that the program doesn't moan
	// that there is a NULL pointer around.
	many[16] = Piece(-1,-1,'u',0);
	 
	for(int j = 0; j < 7; j++) {
		for(int i; i<11; i++) {
			carryon[i][j].piecepointer = &many[16];
		}
	}

	// 0-10 are buffalo
	for(int i=0; i <= 10; i++) {
		many[i] = Piece(i,6,'b',0);
		carryon[i][6].piecepointer = &many[i];
	       //cout << many[i] << endl;
	       }

	// 11-14 are dogs
	many[11] = Piece(1,1,'d',1); 
	carryon[1][1].piecepointer = &many[11];
	many[12] = Piece(3,1,'d',1); 
	carryon[3][1].piecepointer = &many[12];
	many[13] = Piece(7,1,'d',1); 
	carryon[7][1].piecepointer = &many[13];
	many[14] = Piece(9,1,'d',1); 
	carryon[9][1].piecepointer = &many[14];

	// 15 is for the indian
	many[15] = Piece(5,1,'i',1);
	carryon[5][1].piecepointer = &many[15];
	//cout << many[15] << endl;
	

	
	// Time to draw the grid
	char grid[13][9];

	//system("clear");

//	do {

	// Fill it full of nothing
	// This is the easiest way to check that there are no false positives of where pieces are
	for(int i = 0; i<=8; i++) {
		for(int j = 0; j <=12; j++) {
			grid[j][i] = '.';
		}
	}

	// The edges
	for(int i=1; i <=11; i++) grid[i][0] = '0' + i-1;
	for(int i=1; i <=11; i++) grid[i][8] = '0' + i-1;
	for(int i=1; i <=7; i++) grid[0][i] = '0' + i-1;
	for(int i=1; i <=7; i++) grid[12][i] = '0' + i-1;

	// Where are the pieces?
	// This will update as pieces are moved
	 
	for(int i=0; i<= 15; i++) {
		// here I need to give the locations of the pieces to the grid
		position tempposition = many[i].getr();
		grid[(tempposition.x)+1][(tempposition.y)+1] = many[i].gettype();
	//	cout << "Dude, " << many[i].gettype() << " was just assigned to (" << tempposition.x << ", " << tempposition.y << ")." 
	//		<< " Or at least I hope so..." << endl;
	}
	

	// Draw it
	for(int i = 0; i<=8; i++) {
		for(int j = 0; j <=12; j++) {
			cout << grid[j][i] << " ";
		}
		if (i == 1 || i == 6) cout << endl << "*************************" << endl; // The river
		else cout << endl << endl; 
	}

	// Check for winning! 1 buffalo is apparently the winning condition.
	for(int i = 0; i <1; i++) {
		count = 0; // count the number of buffalo safe
		position testr;
		testr.x = i;
		if(many[i].getr() == testr) count++;
	}
	if (count == 11) {
		cout << "You have won" << endl;
		cout << "It's time to PARTY PARTY PARTY PARTY.";
		return 0;
	}
// Now, finally for the players.
	if(player == 0) player = 1; else if(player == 1) player = 0;	
	// So basically, this needs to be replaced by a gtk function.
//	cin >> testr;
//	identify(pointermany,player,testr);

 /* :TODO:29/10/11 12:53:26:: Make the gtk application after this point. get rid of the cin, and hopefully I'll have a working set of buttons
  * Maybe I'll drag and drop in the end, but I think the callback functions will be unchanged, they will simply react to different signals.
  * Dang I feel posh using the real terms for stuff like this. */

	GtkWidget * window;
	GtkWidget * table;
	GtkWidget * button;

	gtk_init(&argc,&argv);

	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);

	table = gtk_table_new(11,7,TRUE);

	gtk_container_add(GTK_CONTAINER(window), table);

	position testrmain[11][7];
	for(int j = 0; j < 7; j++ ){
		for(int i = 0; i < 11; i++){
			// This is a for for loop for making the grid of buttons to input to the identify func.
			// It should be easy from then to simply make the callbacks respond to the signal of
			// a dragging thing being dropped.
			//
			// Great news! The grid worked. Issues with identify though...
			
			button = gtk_button_new();

			testrmain[i][j].x = i;
			testrmain[i][j].y = j;

			carryon[i][j].player = 0;
			carryon[i][j].r = testrmain[i][j];
			
			g_signal_connect(button, "clicked", G_CALLBACK(identifycallback), &(carryon[i][j]));
			// For some bizarre reason, this code will not work, despite the fact it's pointers
			// are almost identical to the previous one. I should sort this. Later.
//			g_signal_connect(button, "clicked", G_CALLBACK(checkcontent), &(carryon[i][j]));

			gtk_table_attach_defaults(GTK_TABLE(table),button, i,i+1, j, j+1);

			gtk_widget_show(button);
		}
	}
	button = gtk_button_new_with_label("FOO BAR");

	gtk_widget_show(table);

	gtk_widget_show(window);

	gtk_main();
	
	return 0;
}

