#include "operation.h"

#define M_PI 3.1415926535897932384

namespace operation
{
	// returns the angle between two bodies so that the result can be simply used with sin and cosine
	// a is the body we are taking into consideration, being attracted by b
	float getAngle(float xa, float ya, float xb, float yb) {
		float angle;
		float dx, dy;
		dx = abs(xa - xb); // x component
		dy = abs(ya - yb); // y component

		// a better explanation on these function can be found in the project report
		if (xa < xb && ya > yb)
			angle = -atan(dy / dx);
		else if (xa > xb && ya > yb)
			angle = atan(dy / dx) + M_PI;
		else if (xa < xb && ya < yb)
			angle = atan(dy / dx);
		else if (xa > xb && ya < yb)
			angle = M_PI - atan(dy / dx);
		else if (xa == xb){
			if (ya > yb)
				angle = -M_PI / 2;
			else
				angle = M_PI / 2;
		}
		else if (ya == yb){
			if (xa > xb)
				angle = M_PI;
			else
				angle = 0;
		}
		return angle;
	}

	// returns the distance between the two bodies
	float getR(float xa, float ya, float xb, float yb){
		float dx = abs(xa - xb);
		float dy = abs(ya - yb);

		// a simple application of Pythagoras
		return sqrt(pow(dx, 2) + pow(dy, 2));
	}


}