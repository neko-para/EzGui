#ifndef _E_USER_WINDOW_H_
#define _E_USER_WINDOW_H_

#include "EWindow.h"

namespace Eg {

	class EUserWindow : public EWindow {
	protected:
		virtual void preDraw(int px, int py) override;
		virtual void pstDraw(int px, int py) override;
	public:
		using EWindow::EWindow;
	};

}

#endif
