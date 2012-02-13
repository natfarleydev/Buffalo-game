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

void close_window(Fl_Widget * w, void * data){ ((Fl_Window *)data)->hide(); }

void about_game(Fl_Widget* w, void * data) { 
	fl_message("This game was created for a c++ project for the\nUniversity of Birmingham using FTLK\n\nCreated 2011 by Nathanael Farley\nHave fun!");
}

void instructions(Fl_Widget * w, void * data) {
	system("start instructions_buffalo.pdf");
}