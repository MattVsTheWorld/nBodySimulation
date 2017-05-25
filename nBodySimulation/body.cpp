#include "body.h"

Body::Body(float ix, float iy, float r) { // initial values for the body
	x = ix;
	y = iy;
	radius = r;
}

Body::~Body(){}

void Body::setColour(float r, float g, float b) { // assign an rgb colour
	colour[0] = r;
	colour[1] = g;
	colour[2] = b;
	colour[3] = 1.0;
}
void Body::setColour(float colour[]) { // set the colour
	for (int i = 0; i<4; i++) {
		this->colour[i] = colour[i];
	}
}
void Body::draw() { // draws a circle
	glColor4fv(colour);
	glLineWidth(3);
	glBegin(GL_POLYGON);
	const int NPOINTS = 25;
	const float TWOPI = 2 * 3.1415927;
	const float STEP = TWOPI / NPOINTS;
	for (float angle = 0; angle<TWOPI; angle += STEP)
		glVertex2f(x + radius*cos(angle), y + radius*sin(angle));
	glEnd();
}
void Body::move(float dx, float dy) { // moves by an amount (not used in this case)
	x += dx;
	y += dy;
}

void Body::moveTo(float nx, float ny){ // move to a position
	x = nx;
	y = ny;
}

void Body::resize(float newsize){ // resize the body
	radius = newsize;
}

// simple accessors for position
float Body::getx() { return x; }

float Body::gety() { return y; }
