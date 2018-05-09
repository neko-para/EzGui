#ifndef _E_WINDOW_H_
#define _E_WINDOW_H_

#include <list>

#include "EEventLoop.h"
#include "EMsg.h"
#include "ETypes.h"

namespace Eg {

	extern class EWindow* eRootWindow;

	class EWindow {
		friend class EEventLoop;
		friend class EMainWindow;
		std::list<EWindow*> subWindows;
		void execDraw(int px, int py);
		EWindow(int x, int y, int w, int h);
	protected:
		EWindow* parentWindow;
		int windowPosx, windowPosy;
		int windowWidth, windowHeight;
		virtual void preDraw(int px, int py);
		virtual void pstDraw(int px, int py);
	public:
		EWindow(EWindow* p, int x, int y, int w, int h);
		virtual ~EWindow() {}

		void post(EMsgBase* msg);
		virtual void draw();
		virtual void move(int x, int y);
		virtual void resize(int w, int h);


		EPointi pos() const {
			return EPointi(windowPosx, windowPosy);
		}

		EPointi size() const {
			return EPointi(windowWidth, windowHeight);
		}

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