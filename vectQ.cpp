#include "vectQ.h"


vectQ::vectQ(double X, double Y) :x{ X }, y{ Y }
{
}


vectQ operator+(const vectQ & a, const vectQ & b) {
	return vectQ(a.x + b.x, a.y + b.y);
}

vectQ operator-(const vectQ& a, const vectQ& b) {
	return vectQ(a.x - b.x, a.y - b.y);
}