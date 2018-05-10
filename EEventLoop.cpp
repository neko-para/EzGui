#include "global.h"
#include "EApp.h"
#include "EEventLoop.h"
#include "EWindow.h"

#include <stdio.h>
#include <time.h>

namespace Eg {

	EEventLoop::EEventLoop() : end(false), exitCode(0), quit([&](int c) {
		exitCode = c;
		end = true;
	}) {}

	int EEventLoop::exec() {
//		clock_t base = clock();
//		unsigned long cnt = 0;
		while (!end) {
			std::list<EMsgBase*> msgs;
			eApp->get(msgs);
			for (auto p : msgs) {
				eRootWindow->post(p);
				delete p;
			}
			glClear(GL_COLOR_BUFFER_BIT);
			eRootWindow->execDraw(0, eRootWindow->windowHeight);
			glfwSwapBuffers(eApp->getGlfwWindow());
//			printf("%.4lf\r", (double)cnt++ / (clock() - base) * CLOCKS_PER_SEC);
//			if (cnt > 10000) {
//				base = clock();
//				cnt = 0;
//			}
		}
		return exitCode;
	}

}
