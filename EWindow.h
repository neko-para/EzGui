#ifndef _E_WINDOW_H_
#define _E_WINDOW_H_

#include <list>

#include "EEventLoop.h"
#include "EMsg.h"

namespace Eg {

	extern class EWindow* eRootWindow;

	class EWindow {
		friend class EEventLoop;
		std::list<EWindow*> subWindows;
		EWindow* parentWindow;
		unsigned frameBuffer;
		// unsigned renderBuffer;
		unsigned texture;
		int windowPosx, windowPosy;
		int windowWidth, windowHeight;
		void execDraw();
	public:
		EWindow(EWindow* p, int x, int y, int w, int h);
		virtual ~EWindow() {}

		virtual void post(EMsgBase* msg) final;
		virtual void drawTexture() final;
		virtual void draw();
		void move(int x, int y);
		void resize(int w, int h);

		int width() const {
			return windowWidth;
		}

		int height() const {
			return windowHeight;
		}

		EWindow* parent() const {
			return parentWindow;
		}
	};

}

#endif