#include "global.h"
#include "EWindow.h"
#include "EApp.h"

namespace Eg {

	EWindow* eRootWindow;

	EWindow::EWindow(EWindow* p, int x, int y, int w, int h) : parentWindow(p), windowPosx(x), windowPosy(y), windowWidth(w), windowHeight(h) {
		if (p) {
			p->subWindows.push_back(this);
		}
	}

	void EWindow::post(EMsgBase* msg) {
		switch (msg->type()) {
		case EMSG_CLOSE:
			msg->accept();
			break;
		default:
			;
		}
	}

	void EWindow::execDraw(int px, int py) {
		// glPushAttrib(GL_ALL_ATTRIB_BITS);
		glPushMatrix();
		if (parentWindow) {
			glTranslated(windowPosx, windowPosy, 0);
		}
		glScissor(px, py - windowHeight, windowWidth, windowHeight);
		draw();
		glPopMatrix();
		// glPopAttrib();
		for (auto it = subWindows.rbegin(); it != subWindows.rend(); ++it) {
			(*it)->execDraw(px + (*it)->windowPosx, py - (*it)->windowPosy);
		}
	}

	void EWindow::draw() {}

	void EWindow::move(int x, int y) {
		windowPosx = x;
		windowPosy = y;
		if (!parentWindow) {
			glfwSetWindowPos(eApp->getGlfwWindow(), windowPosx, windowPosy);
		}
	}

	void EWindow::resize(int w, int h) {
		windowWidth = w;
		windowHeight = h;
		if (!parentWindow) {
			glfwSetWindowSize(eApp->getGlfwWindow(), windowWidth, windowHeight);
		}
	}

}