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



class Phys_Object {
	double massvar;
	vectQ velocityvar;
	vectQ positionvar;

	//bool effected_gravity; //store if object is to be effected by global gravity
	//bool paused;

public:
	Phys_Object(double, double, double);

	virtual void update_position(unsigned int);  //given the time elapsed for this frame, update_position physics position and velocity

	double mass() { return massvar; }
	double mass(double M) { massvar = M; return massvar; }
	vectQ velocity() { return velocityvar; }
	vectQ velocity(vectQ V) { velocityvar = V; return velocityvar; } //accessing this way is turgid, needs improvement
	vectQ Pposition() { return positionvar; }
	vectQ Pposition(vectQ P) { positionvar = P; return positionvar; }

};

class Phys_CB { //abstract callback class
public:
//	void callCB() { operator(); }
	virtual void operator()() {
		std:: cout << "virtual called\n";
	}
protected:
	Phys_Object* obj{ nullptr };
	Phys_CB();
};

class test_cb : public Phys_CB {
	vectQ joltamount;
public:
	test_cb(Phys_Object*, vectQ);
	void operator()() {
		obj->velocity(joltamount);
		std::cout << "test_cb called\n";
	}
};

struct Phys_Event {
	unsigned delay;
	Phys_CB& callback; //if not stored as a reference/pointer, this abstract class would be subject to slicing
	Phys_Event(unsigned, Phys_CB&);
};

class Phys_Environment : public Fl_Box {
	std::vector<Phys_Object*> objects; //pointers to all physics objects owned by this environment
	unsigned int framecount; //frames elapsed
	unsigned int fps; //fps of simulation
	double timescale; //speed at which to run physics (default 1.0)

	std::list<Phys_Event> Eventlist; //this is likely not the right container to use, inserts need to be in time-ascending order and other containers may support that inately

public:
	Phys_Environment(int,int,int,int,char*);
	unsigned int get_framecount() { return framecount; }
	void attach(Phys_Object* O) { objects.push_back(O); }
	void update_all(); //simulate physics for all objects for this frame

	void attach_Event(Phys_Event);
};

class Phys_Button : public Fl_Button, public Phys_Object {

public:
	Phys_Button(int,int,int,int,char*,double);

	void update_position(unsigned int);
};