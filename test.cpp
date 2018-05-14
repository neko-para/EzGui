#include "EApp.h"
#include "EUserWindow.h"
#include "EMsg.h"
#include <GL/glew.h>
#include "EPainter.h"
#include <stdio.h>

using namespace Eg;

class MyMain : public EUserWindow {
protected:
	virtual void mouseMove(EMouseMoveMsg*) override {
		// printf("msg: %+04d    %+04d\n", m->pos.x, m->pos.y);
		// fflush(stdout);
	}

	EPainter::PointData vertexs;
	EPainter::ColorData colors;
public:
	MyMain(EWindow* p) : EUserWindow(p), vertexs({
			-8.6, 5,
			0, -10,
			8.6, 5
		}), colors({
			1.0, 0.0, 0.0, 1.0,
			0.0, 1.0, 0.0, 1.0,
			0.0, 0.0, 1.0, 1.0,
		}) {}
	virtual void draw() {
		// glClear(GL_COLOR_BUFFER_BIT);
		static float x;
		glPushMatrix();
		glRotated(x, 0, 0, 1);
		glScaled(5, 5, 1);
		x += 0.1;
		EPainter painter;
		painter.draw(EPainter::Triangles, vertexs, colors);
		// glBegin(GL_TRIANGLES);
		// glColor3d(1, 0, 0);
		// glVertex2d(-8.6, 5);
		// glColor3d(0, 1, 0);
		// glVertex2d(0, -10);
		// glColor3d(0, 0, 1);
		// glVertex2d(8.6, 5);
		// glEnd();
		glPopMatrix();
	}
};

int main() {
	EApp app([]() {
		// printf("%d.%d\n", eApp->majorVer(), eApp->minorVer());
		(new MyMain(eRootWindow))->move(160, 120)->resize(320, 240);
	});
	return app.exec();
}
