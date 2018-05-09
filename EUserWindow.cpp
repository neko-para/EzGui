#include "global.h"
#include "EUserWindow.h"

namespace Eg {

	void EUserWindow::preDraw(int px, int py) {
		EWindow::preDraw(px, py);
		glScissor(px, py - windowHeight, windowWidth, windowHeight);
		glPushAttrib(GL_ALL_ATTRIB_BITS);
	}

	void EUserWindow::pstDraw(int px, int py) {
		glPopAttrib();
		EWindow::pstDraw(px, py);
	}

}