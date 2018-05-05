#include "EApp.h"
#include "EEventLoop.h"
#include "EWindow.h"

namespace Eg {

	EEventLoop::EEventLoop() : end(false), exitCode(0), quit([&](int c) {
		exitCode = c;
		end = true;
	}) {}

	int EEventLoop::exec() {
		while (!end) {
			std::list<EMsgBase*> msgs;
			eApp->get(msgs);
			for (auto p : msgs) {
				eRootWindow->post(p);
				delete p;
			}
		}
		return exitCode;
	}

}