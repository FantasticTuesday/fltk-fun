#include <FL/Fl.h>
#include <FL/Fl_Box.H>
#include <FL/names.h>
#include <vector>

//
#include <list>
//

#include <FL/Fl_Button.H>

#include "vectQ.h"

//
#include <iostream>
//



class Phys_object {
	double massvar;
	vectQ velocityvar;
	vectQ positionvar;

	//bool effected_gravity; //store if object is to be effected by global gravity
	//bool paused;

public:
	Phys_object(double, double, double);

	virtual void update_position(unsigned int);  //given the time elapsed for this frame, update_position physics position and velocity

	double mass() { return massvar; }
	double mass(double M) { massvar = M; return massvar; }
	vectQ velocity() { return velocityvar; }
	vectQ velocity(vectQ V) { velocityvar = V; return velocityvar; } //accessing this way is turgid, needs improvement
	vectQ Pposition() { return positionvar; }
	vectQ Pposition(vectQ P) { positionvar = P; return positionvar; }

};

//crude first go at a delayed speed change request system (what is that even called in correct terms?)
struct physchange { //terrible name
	Phys_object* object; //passing as a pointer is going to cause problems
	vectQ amount;
	unsigned int time;

	physchange(Phys_object*, vectQ, unsigned int);
};

class Phys_Environment : public Fl_Box {
	std::vector<Phys_object*> objects; //pointers to all physics objects owned by this environment
	unsigned int framecount; //frames elapsed
	unsigned int fps; //fps of simulation
	double timescale; //speed at which to run physics (default 1.0)

	std::list<physchange> changelist; //this is likely not the right container to use, inserts need to be in time-ascending order and other containers may support that inately

public:
	Phys_Environment(int,int,int,int,char*);
	unsigned int get_framecount() { return framecount; }
	void attach(Phys_object* O) { objects.push_back(O); }
	void update_all(); //simulate physics for all objects for this frame

	void attach_change(physchange);
	void show_changes();
};

class Phys_Button : public Fl_Button, public Phys_object {

public:
	Phys_Button(int,int,int,int,char*,double);

	void update_position(unsigned int);
};