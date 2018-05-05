#ifndef _E_MSG_H_
#define _E_MSG_H_

#include <functional>

#include "ESignal.h"

namespace Eg {

	enum EMsgType {
		EMSG_CLOSE,
		EMSG_MOUSE_MOVE
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
		virtual EMsgType type() const = 0;
	};

	struct ECloseMsg : public EMsgBase {
		virtual EMsgType type() const {
			return EMSG_CLOSE;
		}
	};

	struct EMouseMoveMsg : public EMsgBase {
		double x, y;
		EMouseMoveMsg(double xx, double yy) : x(xx), y(yy) {}
		virtual EMsgType type() const {
			return EMSG_MOUSE_MOVE;
		}
	};

}

#endif