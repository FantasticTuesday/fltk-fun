#include <FL/Fl.h>
#include <FL/Fl_Window.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Output.H>
#include <iostream>
#include <string>
#include "Phys_Environment.h"

using namespace std;

double FRAME_T{ 1.0 / 30.0 }; //time for each frame

Fl_Double_Window* win = new Fl_Double_Window(800, 600, "pretty test");

Fl_Output* framecounter = new Fl_Output(0, 0, 40, 20, "frames");

Phys_Environment* world = new Phys_Environment(100, 100, 600, 400, "world");

void callback_t(void* t){
// update_position positions of all objects
	world->update_all();
	Fl::redraw();
	Fl::repeat_timeout(FRAME_T,callback_t);
	framecounter->value(std::to_string(world->get_framecount()).c_str());
}

int main() {
	
	try {
		Phys_Button* button1 = new Phys_Button(50,200,50,50,"woop", 10);
		button1 -> velocity(vectQ(30.0,-75.0));
		world->attach(button1);

		Phys_Button* button2 = new Phys_Button(25,300,40,80,"boop", 10);
		button2 -> velocity(vectQ(30.0,10.0));
		world->attach(button2);

		test_cb trycb1(button1, vectQ(-10.0, -20.0));
		test_cb trycb2(button1, vectQ(0.0, -20.0));
		test_cb trycb3(button2, vectQ(0.0, -20.0));
		Phys_Event event1(20, trycb1);
		Phys_Event event2(60, trycb2);
		Phys_Event event3(60, trycb3);
		world->attach_Event(event1);
		world->attach_Event(event2);
		world->attach_Event(event3);

		void* W = static_cast<void*>(world);

		Fl::add_timeout(FRAME_T, callback_t);
		win->show();
		return Fl::run();
		
		double j, k;
		vectQ line (0,0);
		while (cin >> j >> k) {
				vectQ newline(j,k);
				line = line + newline;
				cout << "\n(" << line.x << ',' << line.y << ") mag/dir: " << line.mag() <<',' << line.dir();
		}
	}
	catch (exception& e) {
		cerr << '\n' << e.what() << '\n';
	}
	catch (...) {
		cerr << "\nUncaught error.\n";
	}
	
}