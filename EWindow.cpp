#include "EWindow.h"

namespace Eg {

	EWindow* eRootWindow;

	EWindow::EWindow(EWindow* p) : parentWindow(p) {

	}

	void EWindow::post(EMsgBase* msg) {
		switch (msg->type()) {
		case EMSG_CLOSE:
			msg->accept();
			break;
		default:
			;
		}
	}

	void EWindow::draw() {}

}