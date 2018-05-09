#ifndef _E_PAINTER_H_
#define _E_PAINTER_H_

#include "ETypes.h"

namespace Eg {

	class EPainter {
		EColor coordColor;
	public:
		EPainter();
		void point(EPointf p);
		void line(EPointf s, EPointf e);
	};

}

#endif