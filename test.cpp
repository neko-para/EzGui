#include "EApp.h"
#include "EUserWindow.h"
#include <GL/glew.h>

class MyMain : public Eg::EUserWindow {
public:
	using Eg::EUserWindow::EUserWindow;
	virtual void draw() {
		// glClear(GL_COLOR_BUFFER_BIT);
		static float x;
		glPushMatrix();
		glRotated(x, 0, 0, 1);
		glScaled(5, 5, 1);
		x += 0.1;
		glBegin(GL_TRIANGLES);
		glColor3d(1, 0, 0);
		glVertex2d(-8.6, 5);
		glColor3d(0, 1, 0);
		glVertex2d(0, -10);
		glColor3d(0, 0, 1);
		glVertex2d(8.6, 5);
		glEnd();
		glPopMatrix();
	}
};

int main() {
	Eg::EApp app([]() {
		new MyMain(Eg::eRootWindow, 160, 120, 320, 240);
	});
	return app.exec();
}