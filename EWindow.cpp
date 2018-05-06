#include "global.h"
#include "EWindow.h"
#include "EApp.h"

namespace Eg {

	EWindow* eRootWindow;

	EWindow::EWindow(EWindow* p, int x, int y, int w, int h) : parentWindow(p), windowPosx(x), windowPosy(y), windowWidth(w), windowHeight(h) {
		GLint pre;
		glGenFramebuffers(1, &frameBuffer);
		// glGenRenderbuffers(1, &renderBuffer);
		glGenTextures(1, &texture);
		glGetIntegerv(GL_FRAMEBUFFER_BINDING, &pre);
		glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);  
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);  
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);  
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture, 0);
		glBindFramebuffer(GL_FRAMEBUFFER, pre);
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

	void EWindow::execDraw() {
		glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);
		draw();
		for (auto p : subWindows) {
			p->execDraw();
		}
		drawTexture();
	}

	void EWindow::drawTexture() {
		int pw, ph, x, y;
		if (parentWindow) {
			glBindFramebuffer(GL_FRAMEBUFFER, parentWindow->frameBuffer);
			pw = parentWindow->width();
			ph = parentWindow->height();
			x = windowPosx;
			y = ph - windowPosy - windowHeight;
		} else {
			glBindFramebuffer(GL_FRAMEBUFFER, 0);
			glfwGetWindowSize(eApp->getGlfwWindow(), &pw, &ph);
			x = 0;
			y = ph;
		}
		glBindTexture(GL_TEXTURE_2D, texture);
		glBegin(GL_QUADS);
		glTexCoord2i(0, 0);
		glVertex2i(x, y);
		glTexCoord2i(1, 0);
		glVertex2i(x + windowWidth, y);
		glTexCoord2i(1, 1);
		glVertex2i(x + windowWidth, y + windowHeight);
		glTexCoord2i(0, 1);
		glVertex2i(x, y + windowHeight);
		glEnd();
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
		GLint pre;
		glGetIntegerv(GL_TEXTURE_BINDING_2D, &pre);
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);
		glBindTexture(GL_TEXTURE_2D, pre);
	}

}