#ifndef _E_WINDOW_H_
#define _E_WINDOW_H_

#include "EEventLoop.h"
#include "EMsg.h"

namespace Eg {

	extern class EWindow* eRootWindow;

	class EWindow {
		friend class EEventLoop;
		EWindow* parentWindow;
	public:
		EWindow(EWindow* p);
		virtual ~EWindow() {}
		virtual void post(EMsgBase* msg) final;
		virtual void draw();

		EWindow* parent() const {
			return parentWindow;
		}
	};

}

#endif