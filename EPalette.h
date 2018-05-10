#ifndef _E_PALETTE_H_
#define _E_PALETTE_H_

#include "ETypes.h"

namespace Eg {

	struct EPalette {
		enum EPaletteGroup {
			ACTIVE,
			INACTIVE,
			DISABLE
		};
		enum EPaletteIndex {
			WINDOW,
			WINDOWTEXT,
			BASE,
			TOOLTIPBASE,
			TOOLTIPTEXT,
			TEXT,
			BUTTON,
			BUTTONTEXT,
			LIGHT,
			MIDLIGHT,
			DARK,
			MID,
			SHADOW,
			HIGHLIGHT,
			HIGHLIGHTTEXT,
			LINK,
			LINKVISITED,
			NUMBER_OF_INDEXES
		};
		struct PaletteData {
			EColor colors[NUMBER_OF_INDEXES];
			int ref;
		};
		EPalette();
	private:
		static PaletteData defaultPalette[3];
		PaletteData* data[3];
	};

}

#endif