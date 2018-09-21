#include "Phys_Environment.h"

Phys_object::Phys_object(double x, double y, double m) :massvar{ m }, velocityvar{ 0.0,0.0 }, positionvar{ x,y } //for now, initialisation of objects with non-zero starting velocity is disallowed
{

}

void Phys_object::update_position(unsigned int fps)
{
	int xdisp = positionvar.x + velocityvar.x/fps;
	int ydisp = positionvar.y + velocityvar.y/fps;
	positionvar = vectQ(positionvar.x + xdisp, positionvar.y + ydisp);
}


physchange::physchange(Phys_object* ob, vectQ am, unsigned int t) :object{ ob }, amount{ am }, time{ t }
{}


Phys_Environment::Phys_Environment(int x, int y, int w, int h, char* p) : Fl_Box(x, y, w, h, p), framecount{ 0 }, fps{ 30 }, timescale{ 1.0 }
{
	Fl_Boxtype(FL_UP_BOX);
	show();
}

void Phys_Environment::update_all() {

	//this might be replaced with a 'find' function
	auto itr = changelist.begin();
	while (itr != changelist.end() && itr->time > framecount) {
		++itr;
	}
	if (itr != changelist.end()) {
		itr->object->velocity(itr->amount);
		changelist.erase(itr);
	}


	for (Phys_object* P : objects) {
		P->update_position(fps);
	}
	++framecount;
}

void Phys_Environment::attach_change(physchange change) {
	
	//this might be replaced with a 'find' function
	auto itr = changelist.begin();
	while (itr != changelist.end() && itr->time < change.time){
	++itr;
	}
	changelist.insert(itr, change);
}

void Phys_Environment::show_changes() { //to be removed
	std::cout << changelist.size() << '\n';
	for (physchange elem : changelist) {
		std::cout << elem.time << '\n';
	}
}

Phys_Button::Phys_Button(int x, int y, int w, int h, char* p, double m) : Fl_Button(x, y, w, h, p), Phys_object(x, y, m)
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
