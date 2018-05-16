#ifndef _E_APP_H_
#define _E_APP_H_

#include <thread>
#include <functional>

#include "EMsgQueue.h"
#include "EEventLoop.h"
#include "ESignal.h"

struct GLFWwindow;

namespace Eg {

	extern class EApp* eApp;

	class EApp {
		bool end;
		EMsgQueuePtr msgQueue;
		EEventLoop loop;
		std::thread* coreThread;
		GLFWwindow* handle;

		EApp(const EApp&);
		EApp& operator=(const EApp&);
		Slot<void> close;
	public:
		Signal<int> s_quit;
		TransferSlot<int> quit;

		EApp(std::function<void(void)> startUp, int w = 640, int h = 480);
		~EApp();

		int exec();

		void put(EMsgBase* m) {
			msgQueue->put(m);
		}
		void get(std::list<EMsgBase*>& lst) {
			msgQueue->get(lst);
		}
		GLFWwindow* getGlfwWindow() const {
			return handle;
		}
	};

}

#endif
