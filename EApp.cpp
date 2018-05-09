#include "global.h"
#include "EApp.h"
#include "EException.h"
#include "EWindow.h"
#include "EMsg.h"

namespace Eg {

	class EMainWindow : public EWindow {
	protected:
		virtual void preDraw(int, int) override {}
		virtual void pstDraw(int, int) override {}
	public:
		EMainWindow(int x, int y, int w, int h) : EWindow(x, y, w, h)  {}
		virtual void move(int x, int y) override {
			windowPosx = x;
			windowPosy = y;
			glfwSetWindowPos(eApp->getGlfwWindow(), windowPosx, windowPosy);
		}
		virtual void resize(int w, int h) override {
			windowWidth = w;
			windowHeight = h;
			glfwSetWindowSize(eApp->getGlfwWindow(), windowWidth, windowHeight);
		}
	};

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
				glEnable(GL_BLEND);
				glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

				glViewport(0, 0, w, h);
				glLoadIdentity();
				gluOrtho2D(0, w, 0, h);
				glTranslated(0, h, 0);
				glScaled(1, -1, 1);

				int px, py;
				glfwGetWindowPos(handle, &px, &py);
				eRootWindow = new EMainWindow(px, py, w, h);
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