#include "global.h"
#include "EApp.h"
#include "EException.h"
#include "EWindow.h"
#include "EMsg.h"

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

	EApp::EApp() : end(false), close([&]() {
		end = true;
	}), quit(s_quit) {
		if (eApp) {
			throw Exceptions::AppAlreadyConstruct();
		} else {
			eApp = this;
			msgQueue = EMsgQueue::create();
			glfwInit();
			handle = glfwCreateWindow(100, 100, "", 0, 0);
			glfwSetWindowCloseCallback(handle, CloseCallback);
			glfwSetCursorPosCallback(handle, CursorPosCallback);
			coreThread = new std::thread([&]() {
				glfwMakeContextCurrent(handle);
				eRootWindow = new EWindow(0);
				s_quit.connect(loop.quit);
				loop.exec();
				close();
			});
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