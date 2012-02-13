class Piece : public Fl_Box {
public:
	Fl_PNG_Image * indian_image;
	Piece(int X, int Y, int W, int H) : Fl_Box(X,Y,W,H) 
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

			// Movement on the grid
			grid_update(x(),y(),startpos[0],startpos[1], 'i');
			grid_cout();
			
			mainwin->redraw();
		return(1);
		
		// If not used for moving, offer the event to the parent
		return Fl_Box::handle(event);
	}
	
};
