#include "global.h"
#include "EPushButton.h"

namespace Eg {

	EPushButton::EPushButton(EWindow* p) : EWindow(p) {
		curState = false;
	}
	
	void EPushButton::mouseMove(EMouseMoveMsg*) {
		
	}
	
}
