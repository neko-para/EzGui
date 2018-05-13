#ifndef _E_WINDOW_H_
#define _E_WINDOW_H_

#include <list>

#include "EEventLoop.h"
#include "EMsg.h"
#include "ETypes.h"
#include "EPalette.h"

namespace Eg {

	extern class EWindow* eRootWindow;

	class EWindow : public EWindowInterface {
		friend class EEventLoop;
		friend class EMainWindow;
		std::list<EWindow*> subWindows;
		void execDraw(int px, int py);
		EWindow();
	protected:
		EPalette windowPalette;
		EWindow* parentWindow;
		int windowPosx, windowPosy;
		int windowWidth, windowHeight;
		bool checkSubWindowsHit(EMouseMsg* m);
		virtual bool hitTest(EMouseMsg* m);
		virtual void preDraw(int px, int py);
		virtual void pstDraw(int px, int py);
		virtual void draw();
		virtual void windowClose(ECloseMsg* msg);
		virtual void windowResize(EResizeMsg* msg);
		virtual void mouseMove(EMouseMoveMsg* msg);
	public:
		EWindow(EWindow* p);
		virtual ~EWindow() {}

		void post(EMsgBase* msg);
		virtual EWindow* move(int x, int y);
		virtual EWindow* resize(int w, int h);
		EPalette palette() const {
			return windowPalette;
		}
		void setPalette(EPalette p) {
			windowPalette = p;
		}

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
