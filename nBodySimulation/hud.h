#ifndef HUD
#define HUD
#include<string>
#include<glut.h>

namespace hud {
	void drawString(void *font, float x, float y, const char *str);
	void displayHUD();
}

#endif