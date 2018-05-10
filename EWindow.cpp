#include "global.h"
#include "EWindow.h"
#include "EApp.h"
#include <stdio.h>

namespace Eg {

	EWindow* eRootWindow;

	EWindow::EWindow() : windowPosx(0), windowPosy(0), windowWidth(1), windowHeight(1) {}

	EWindow::EWindow(EWindow* p) : EWindow() {
		parentWindow = p;
		p->subWindows.push_back(this);
	}

	void EWindow::post(EMsgBase* msg) {
		switch (msg->type()) {
		case EMSG_CLOSE:
			msg->accept();
			break;
		case EMSG_MOUSE:
			hitTest(dynamic_cast<EMouseMsg*>(msg));
			break;
		default:
			;
		}
	}
	
	bool EWindow::checkSubWindowsHit(EMouseMsg* m) {
		for (auto p : subWindows) {
			m->attach(p);
			if (p->hitTest(m)) {
				return true;
			}
			m->detach(p);
		}
		return false;
	}

	bool EWindow::hitTest(EMouseMsg* m) {
		if (checkSubWindowsHit(m)) {
			return true;
		} else {
			if (m->pos.x >= 0 && m->pos.y >= 0 && m->pos.x < windowWidth && m->pos.y < windowHeight) {
				m->give(this);
				return true;
			} else {
				return false;
			}
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
	
	void EWindow::windowClose(ECloseMsg*) {}
	void EWindow::windowResize(EResizeMsg*) {}
	void EWindow::mouseMove(EMouseMoveMsg*) {}

	void EWindow::draw() {}

	EWindow* EWindow::move(int x, int y) {
		windowPosx = x;
		windowPosy = y;
		return this;
	}

	EWindow* EWindow::resize(int w, int h) {
		windowWidth = w;
		windowHeight = h;
		return this;
	}

}
