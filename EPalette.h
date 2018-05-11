#ifndef _E_PALETTE_H_
#define _E_PALETTE_H_

#include "ETypes.h"

#include <initializer_list>

namespace Eg {

	struct EPalette {
		enum EPaletteGroup {
			ACTIVE,
			INACTIVE,
			DISABLE
		};
		enum EPaletteRole {
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
			NUMBER_OF_ROLES
		};
		struct PaletteData {
			EColor colors[NUMBER_OF_ROLES];
			int ref;
			PaletteData(std::initializer_list<EColor> c, int r) : ref(r) {
				EColor* p = colors;
				for (auto& cl : c) {
					*p++ = cl;
				}
			}
		};
		EPalette();
		EPalette(const EPalette& p);
		~EPalette();
		EPalette& operator=(const EPalette& p);

		void setColor(EPaletteGroup group, EPaletteRole role, const EColor& c);

		void setColor(EPaletteRole role, const EColor& c) {
			setColor(currentGroup, role, c);
		}

		EColor color(EPaletteGroup group, EPaletteRole role) const {
			return data[group]->colors[role];
		}

		EColor color(EPaletteRole role) const {
			return color(currentGroup, role);
		}

		EPaletteGroup currentColorGroup() const {
			return currentGroup;
		}

		void setCurrentColorGroup(EPaletteGroup group) {
			currentGroup = group;
		}
	private:
		static PaletteData defaultPalette[3];
		EPaletteGroup currentGroup;
		PaletteData* data[3];
	};

}

#endif