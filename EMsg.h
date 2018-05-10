#ifndef _E_MSG_H_
#define _E_MSG_H_

#include <functional>

#include "ESignal.h"
#include "ETypes.h"

namespace Eg {

	enum EMsgType {
		EMSG_CLOSE,
		EMSG_RESIZE,
		EMSG_MOUSE
	};
	
	enum EMouseMsgType {
		EMSG_MOUSE_MOVE
	};
	
	struct ECloseMsg;
	struct EResizeMsg;
	struct EMouseMoveMsg;
	
	struct EWindowInterface {
		virtual ~EWindowInterface() {}
		virtual void windowClose(ECloseMsg* msg) = 0;
		virtual void windowResize(EResizeMsg* msg) = 0;
		virtual void mouseMove(EMouseMoveMsg* msg) = 0;
		virtual EPointi pos() const = 0;
	};

	struct EMsgBase {
		Signal<bool> answer;
		std::function<void(bool)> onAnswer;
		virtual ~EMsgBase() {}
		void setAnswer(std::function<void(bool)> f) {
			onAnswer = f;
		}
		void accept() {
			onAnswer(true);
			answer.emit(true);
		}
		void ignore() {
			onAnswer(false);
			answer.emit(false);
		}
		virtual void give(EWindowInterface*) = 0;
		virtual EMsgType type() const = 0;
	};

	struct ECloseMsg : public EMsgBase {
		virtual void give(EWindowInterface* w) {
			w->windowClose(this);
		}
		virtual EMsgType type() const override {
			return EMSG_CLOSE;
		}
	};

	struct EResizeMsg : public EMsgBase {
		EPointi size;
		EResizeMsg(int w, int h) : size(w, h) {}
		virtual void give(EWindowInterface* w) {
			w->windowResize(this);
		}
		virtual EMsgType type() const override {
			return EMSG_RESIZE;
		}
	};
	
	struct EMouseMsg : public EMsgBase {
		EPointi pos;
		EMouseMsg(int x, int y) : pos(x, y) {}
		virtual EMsgType type() const override {
			return EMSG_MOUSE;
		}
		virtual EMouseMsgType msgType() const = 0;
		void attach(EWindowInterface* w) {
			pos -= w->pos();
		}
		void detach(EWindowInterface* w) {
			pos += w->pos();
		}
	};

	struct EMouseMoveMsg : public EMouseMsg {
		EMouseMoveMsg(int x, int y) : EMouseMsg(x, y) {}
		virtual void give(EWindowInterface* w) {
			w->mouseMove(this);
		}
		virtual EMouseMsgType msgType() const override {
			return EMSG_MOUSE_MOVE;
		}
	};

}

#endif
