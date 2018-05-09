#include "global.h"
#include "EWindow.h"
#include "EApp.h"

namespace Eg {

	EWindow* eRootWindow;

	EWindow::EWindow(int x, int y, int w, int h) : windowPosx(x), windowPosy(y), windowWidth(w), windowHeight(h) {}

	EWindow::EWindow(EWindow* p, int x, int y, int w, int h) : EWindow(x, y, w, h) {
		parentWindow = p;
		p->subWindows.push_back(this);
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

	void EWindow::preDraw(int, int) {
		glPushMatrix();
		glTranslated(windowPosx, windowPosy, 0);
	}

	void EWindow::pstDraw(int, int) {
		glPopMatrix();
	}

	void EWindow::execDraw(int px, int py) {
		preDraw(px, py);
		draw();
		pstDraw(px, py);
		for (auto it = subWindows.rbegin(); it != subWindows.rend(); ++it) {
			(*it)->execDraw(px + (*it)->windowPosx, py - (*it)->windowPosy);
		}
	}

	void EWindow::draw() {}

	void EWindow::move(int x, int y) {
		windowPosx = x;
		windowPosy = y;
	}

	void EWindow::resize(int w, int h) {
		windowWidth = w;
		windowHeight = h;
	}

}