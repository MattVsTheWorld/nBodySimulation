/////////////////////////////////////////////////////////////
/////// Software developer - Matteo Marcuzzo B00273607 //////
/////////////////////////////////////////////////////////////
#include <iostream>
#include <glut.h>
#include <cmath>

#include "body.h"
#include "random.h"
#include "operation.h"
#include "hud.h";
#include "Bitmap.h"
#include <vector>

// definition of some constants
#define windowWidth	 1440
#define windowHeight 900
#define DEG_TO_RAD 0.017453293
#define M_PI 3.1415926535897932384
#define NUM_BODIES 80
// intialisation of position and speed vectors
std::vector<float> y_i(NUM_BODIES);
std::vector<float> x_i(NUM_BODIES);
std::vector<float> v_i_y(NUM_BODIES);
std::vector<float> v_i_x(NUM_BODIES);
// initialisastion of bodies mass vector
std::vector<float> mass(NUM_BODIES);
// definition of time step and gravitational constant (arbitrary value)
const float dt = 0.01;
const float G = 400000;
// initialisation of bodies and background
Body *bodies[NUM_BODIES];
Bitmap *background = NULL;
bool display_background = true;

// control value for different scenarios
int controlNumBodies = NUM_BODIES;

// initialisation of actual positions and speeds
// some of these are set arbitrarily to describe different scenarios
void initVectors(){
	for (int i = 0; i < controlNumBodies; i++)
		bodies[i] = NULL;
	y_i[0] = 450;
	x_i[0] = 600;
	v_i_y[0] = 30.0;
	v_i_x[0] = 0.0;

	y_i[1] = 450;
	x_i[1] = 720;
	v_i_y[1] = -30.0;
	v_i_x[1] = 0.0;

	y_i[2] = 450;
	x_i[2] = 840;
	v_i_y[2] = 30.0;
	v_i_x[2] = 0.0;

	// random values for the later scenarios
	for (int i = 3; i < controlNumBodies; i++){ 
		y_i[i] = rnd(100, 800);
		x_i[i] = rnd(100, 1340);
		v_i_y[i] = rnd(-20, 20);
		v_i_x[i] = rnd(-20, 20);
	}
	// initially, all the masses are equal to 1
	for (int i = 0; i < controlNumBodies; i++)
		mass[i] = 1;
}

// initialization point for the program
void init(){
	initVectors();
	background = new Bitmap("background.bmp", false);
	for (int i = 0; i < controlNumBodies; i++){ 
		bodies[i] = new Body(x_i[i], y_i[i], 6);
		bodies[i]->setColour(rnd(0.2, 1), rnd(0.2, 1), rnd(0.2, 1)); // random colours for the bodies
	}

}


void display() {
	glClear(GL_COLOR_BUFFER_BIT);
	if (display_background)
		background->draw(0, 0, 1440, 900);

	for (int i = 0; i < controlNumBodies;i++)
		bodies[i]->draw(); // bodies drawn on top of the background

	hud::displayHUD(); // displays controls
	glutSwapBuffers();
}

void gravity(int numBodies){
	// initialise vectors for acceleration, second velocity, average velocity and new position for both components
	std::vector<float> acc_y(numBodies);
	std::vector<float> v_2_y(numBodies);
	std::vector<float> v_avg_y(numBodies);
	std::vector<float>	y_2(numBodies);
	std::vector<float> acc_x(numBodies);
	std::vector<float> v_2_x(numBodies);
	std::vector<float> v_avg_x(numBodies);
	std::vector<float> x_2(numBodies);

	// epsilon is the softening factor of the equation
	// the simulation does not take collisions in consideration, but this prevents divions by 0 (although extremely unlikely)
	// it also "softens" the acceleration gained by bodies who get extremely close
	float epsilon;

	for (int i = 0; i < numBodies; i++) // curent body
	{
		for (int k = 0; k < numBodies; k++) // body applying force on body i
		{
			if (k == i) // each body skips itself. This can be unnecessary after the introduction of epsilon, but it would be wasteful to still make those calculations
				k++;

			if (k != numBodies)
			{
				float r = operation::getR(bodies[i]->getx(), bodies[i]->gety(), bodies[k]->getx(), bodies[k]->gety());
				epsilon = 1000 / pow(r, 2); // epsilon is defined by a factor > 0. In this case, it is inversely proportional to the distance between bodies.
				float angle = operation::getAngle(bodies[i]->getx(), bodies[i]->gety(), bodies[k]->getx(), bodies[k]->gety());
				// a = (G*m1*m2) / (r^2 + (factor)^2) / m1, mass m1 is simplified
				acc_y[i] += ((G * mass[k]) / (pow(r, 2) + pow(epsilon, 2)) * sin(angle));  // y component
				acc_x[i] += ((G * mass[k]) / (pow(r, 2) + pow(epsilon, 2)) * cos(angle));  // x component

			}
		}
		// euler's method
			v_2_y[i] = v_i_y[i] + acc_y[i] * dt; // next velocity
			v_avg_y[i] = (v_i_y[i] + v_2_y[i]) / 2; // average velocoiy
			y_2[i] = y_i[i] + v_avg_y[i] * dt; // new position
			// same for x component
			v_2_x[i] = v_i_x[i] + acc_x[i] * dt;
			v_avg_x[i] = (v_i_x[i] + v_2_x[i]) / 2;
			x_2[i] = x_i[i] + v_avg_x[i] * dt;

			bodies[i]->moveTo(x_2[i], y_2[i]); // move to new position
			// update values
			y_i[i] = y_2[i];
			v_i_y[i] = v_2_y[i];

			x_i[i] = x_2[i];
			v_i_x[i] = v_2_x[i];
	}
}

void update(){
	// display bodies and apply gravitational force to the ones desired in the current simulation
	gravity(controlNumBodies);
	glutDisplayFunc(display);
}

void keyboard(unsigned char key, int x, int y)
{
	switch (key) {
	case 'q':		// quit
		exit(0);	// Exit The Program
		break;
	case '1':		// simple 2 bodies with same mass case, orbiting a common barycenter external to both bodies, with eccentric elliptic orbits (a common situation for binary stars)
		controlNumBodies = 2;
		init();
		display_background = true;
		break;
	case '2':		// Two bodies with a major difference in mass approximatively orbiting a common barycenter internal to one body (similar to the Earth–Moon system)
		controlNumBodies = 2;
		init();
		mass[0] = 5;
		v_i_y[1] = -120.0; // the small body requires a higher speed so to create an orbit
		bodies[0]->resize(20);
		display_background = true;
		break;
	case '3':
		controlNumBodies = 3; // three bodies of similar mass
		init();
		display_background = true;
		break;
	case '4':
		controlNumBodies = 10; // ten bodies of similar mass
		init();
		display_background = true;
		break;	
	case '5':
		controlNumBodies = 80;	 // eighty bodies of similar mass
		init();
		display_background = true;
		break;
	case '6':					// enable or disable the background in case it's in the way
		if (display_background)
			display_background = false;
		else
			display_background = true;
		break;
	}
}

void timer(int value){
	update();
	glutPostRedisplay();
	glutTimerFunc(dt*1000, timer, 0); // the fucntion takes milliseconds, while dt is in seconds (hence *1000)
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(windowWidth, windowHeight);
	glutInitWindowPosition(100, 100);
	glutCreateWindow(argv[0]);
	init();
	glutKeyboardFunc(keyboard);
	glutTimerFunc(20, timer, 0);
	gluOrtho2D(0, windowWidth, 0, windowHeight);
	glutMainLoop();
	return 0;
}
