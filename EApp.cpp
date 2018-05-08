#include "global.h"
#include "EApp.h"
#include "EException.h"
#include "EWindow.h"
#include "EMsg.h"

#include <stdio.h>

namespace Eg {

	EApp* eApp;

	static void CloseCallback(GLFWwindow*) {
		auto p = new ECloseMsg();
		p->setAnswer([](bool f) {
			if (f) {
				eApp->s_quit.emit(0);
			}
		});
		eApp->put(p);
		glfwSetWindowShouldClose(eApp->getGlfwWindow(), 0);
	}

	static void CursorPosCallback(GLFWwindow*, double x, double y) {
		eApp->put(new EMouseMoveMsg(x, y));
	}

	EApp::EApp(std::function<void(void)> startUp, int w, int h) : end(false), close([&]() {
		end = true;
	}), quit(s_quit) {
		if (eApp) {
			throw Exceptions::AppAlreadyConstruct();
		} else {
			eApp = this;
			msgQueue = EMsgQueue::create();
			glfwInit();
			handle = glfwCreateWindow(w, h, "", 0, 0);
			glfwSetWindowCloseCallback(handle, CloseCallback);
			glfwSetCursorPosCallback(handle, CursorPosCallback);
			// TODO: add resize support.
			coreThread = new std::thread([&](std::function<void(void)> startUp, int w, int h) {
				glfwMakeContextCurrent(handle);
				glfwSwapInterval(0);
				glewInit();
				glEnable(GL_SCISSOR_TEST);

				glViewport(0, 0, w, h);
				glLoadIdentity();
				gluOrtho2D(0, w, 0, h);
				glTranslated(0, h, 0);
				glScaled(1, -1, 1);

				int px, py;
				glfwGetWindowPos(handle, &px, &py);
				eRootWindow = new EWindow(0, px, py, w, h);
				printf("%d %d\n", w, h);
				s_quit.connect(loop.quit);
				startUp();
				loop.exec();
				close();
			}, startUp, w, h);
		}
	}

	EApp::~EApp() {
		coreThread->join();
		delete coreThread;
		glfwTerminate();
		eApp = 0;
	}

	int EApp::exec() {
		while (!end) {
			glfwPollEvents();
		}
		return loop.code();
	}

}