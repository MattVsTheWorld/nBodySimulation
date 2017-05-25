#pragma once
#ifndef BODY
#define BODY
#include<glut.h>
#include<cmath>
class Body {
public:
	Body(float ix, float iy, float r);

	~Body();

	void setColour(float r, float g, float b);
	void setColour(float colour[]);
	void draw();
	void move(float dx, float dy);
	void moveTo(float nx, float ny);
	void resize(float newsize);


	float getx();
	float gety();

private:
	float x, y, z; 
	float radius = 20;
	float colour[4];
};


#endif