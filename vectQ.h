
#define _USE_MATH_DEFINES //allow use of M_PI in math.h
#include <math.h>
#include <exception>


struct vectQ { // a vector quantity
	double x;
	double y;

	vectQ(double, double); //(x, y)

	double dir() {
		return atan2(y,x);
	}
	double mag() {
		return sqrt(pow(x,2) + pow(y,2));
	}
};

vectQ operator+(const vectQ&, const vectQ&);

vectQ operator-(const vectQ&, const vectQ&);