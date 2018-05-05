#ifndef _E_EVENT_LOOP_H_
#define _E_EVENT_LOOP_H_

#include "ESignal.h"

namespace Eg {

	class EEventLoop {
		bool end;
		int exitCode;
	public:
		Slot<int> quit;

		EEventLoop();
		int exec();
		int code() const {
			return exitCode;
		}
	};

}

#endif