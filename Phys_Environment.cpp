#include "Phys_Environment.h"

Phys_Object::Phys_Object(double x, double y, double m) :massvar{ m }, velocityvar{ 0.0,0.0 }, positionvar{ x,y } //for now, initialisation of objects with non-zero starting velocity is disallowed
{

}

void Phys_Object::update_position(unsigned int fps)
{
	int xdisp = positionvar.x + velocityvar.x/fps;
	int ydisp = positionvar.y + velocityvar.y/fps;
	positionvar = vectQ(positionvar.x + xdisp, positionvar.y + ydisp);
}

Phys_CB::Phys_CB() //protected constructor for abstract class
{}

test_cb::test_cb(Phys_Object* O, vectQ J) : joltamount{ J }
{
	obj = O; //not 100% sure why putting this in the initialiser list gives a 'not a static member' error
}

Phys_Event::Phys_Event(unsigned t, Phys_CB& CB) :delay{ t }, callback{ CB }
{}


Phys_Environment::Phys_Environment(int x, int y, int w, int h, char* p) : Fl_Box(x, y, w, h, p), framecount{ 0 }, fps{ 30 }, timescale{ 1.0 }
{
	Fl_Boxtype(FL_UP_BOX);
	show();
}

void Phys_Environment::update_all() {

	//this might be replaced with a 'find' function
	auto itr = Eventlist.begin();
	while (itr != Eventlist.end() && framecount >= itr->delay) {
		itr->callback(); //perform the callback
		itr = Eventlist.erase(itr); //erase the callback from the list and point to the next element
	}


	for (Phys_Object* P : objects) {
		P->update_position(fps);
	}
	++framecount;
}

void Phys_Environment::attach_Event(Phys_Event event) {
	
	//this might be replaced with a 'find' function
	auto itr = Eventlist.begin();
	while (itr != Eventlist.end() && itr->delay < event.delay){
	++itr;
	}
	Eventlist.insert(itr, event);
}

Phys_Button::Phys_Button(int x, int y, int w, int h, char* p, double m) : Fl_Button(x, y, w, h, p), Phys_Object(x, y, m)
{

}

void Phys_Button::update_position(unsigned int fps) {
	double tframe = 1.0/fps;
	vectQ vel(velocity().x * tframe, velocity().y * tframe); //scale velocity to frame length
	//clear this up by adding vector scaling operators
	Pposition(Pposition() + vel); 	//calculate the physical (ie: float) position as opposed to the integer position used by fltk
	Fl_Button::position(Pposition().x, Pposition().y); //update_position fltk position
	redraw();
}
