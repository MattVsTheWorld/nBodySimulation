#include "hud.h"


namespace hud {

	void drawString(void *font, float x, float y, const char *str)
	{
		char *ch;
		glRasterPos3f(x, y, 0.0);
		for (ch = (char*)str; *ch; ch++)
			glutBitmapCharacter(font, (int)*ch);
	}

	void displayHUD() {
		glColor3f(0.8, 1.0, 0.8);
		drawString(GLUT_BITMAP_HELVETICA_18, 50, 850, "[1] 2 bodies, same mass");
		drawString(GLUT_BITMAP_HELVETICA_18, 300, 850, "[2]: 2 bodies, different mass");
		drawString(GLUT_BITMAP_HELVETICA_18, 600, 850, "[3]: 3 bodies");
		drawString(GLUT_BITMAP_HELVETICA_18, 800, 850, "[4]: 10 bodies");
		drawString(GLUT_BITMAP_HELVETICA_18, 1000, 850, "[5]: 80 bodies");
		drawString(GLUT_BITMAP_HELVETICA_18, 1200, 850, "[6]: background ON/OFF");

	}

}
