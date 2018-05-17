#include "EApp.h"
#include "EUserWindow.h"
#include "EMsg.h"
#include "EImage.h"
#include <GL/glew.h>
#include "EPainter.h"
#include <stdio.h>
#include <assert.h>

using namespace Eg;

class MyMain : public EUserWindow {
protected:
	virtual void mouseMove(EMouseMoveMsg*) override {
		// printf("msg: %+04d    %+04d\n", m->pos.x, m->pos.y);
		// fflush(stdout);
	}

	EPainter::PointData vertexs;
	EPainter::PointData texcoords;
	EImage texture;
public:
	MyMain(EWindow* p) : EUserWindow(p), vertexs({
			10, 10,
			10, 42,
			42, 42,
			42, 10,
		}), texcoords({
			0, 0,
			0, 1,
			1, 1,
			1, 0,
		}) {
		assert(texture.load("../commandblock.png"));
	}
	virtual void draw() {
		EPainter painter;
		texture.bind();
		painter.draw(EPainter::Quads, vertexs, texcoords);
		assert(0);
	}
};

int main() {
	EApp app([]() {
		glEnable(GL_TEXTURE);
		(new MyMain(eRootWindow))->move(160, 120)->resize(320, 240);
	});
	return app.exec();
}
