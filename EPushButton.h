#ifndef _E_PUSH_BUTTON_H_
#define _E_PUSH_BUTTON_H_

#include "EWindow.h"
#include "EMsg.h"

namespace Eg {

	class EPushButton : public EWindow {
		bool curState;
	protected:
		virtual void mouseMove(EMouseMoveMsg*);
	public:
		EPushButton(EWindow* p);
		bool state() const {
			return curState;
		}
	};
	
}

#endif
