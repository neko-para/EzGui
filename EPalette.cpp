#include "EPalette.h"

namespace Eg {

	EPalette::PaletteData EPalette::defaultPalette[3] = {
		EPalette::PaletteData({
			EColor(0, 0, 0, 255),
			EColor(255, 255, 255, 255),
			EColor(0, 0, 0, 255),
			EColor(255, 255, 220, 255),
			EColor(0, 0, 0, 255),
			EColor(255, 255, 255, 255),
			EColor(0, 0, 0, 255),
			EColor(255, 255, 255, 255),
			EColor(0, 0, 0, 255),
			EColor(0, 0, 0, 255),
			EColor(0, 0, 0, 255),
			EColor(0, 0, 0, 255),
			EColor(0, 0, 0, 255),
			EColor(0, 0, 128, 255),
			EColor(255, 255, 255, 255),
			EColor(0, 0, 255, 255),
			EColor(255, 0, 255, 255),
		}, 1),
		EPalette::PaletteData({
			EColor(0, 0, 0, 255),
			EColor(255, 255, 255, 255),
			EColor(0, 0, 0, 255),
			EColor(255, 255, 220, 255),
			EColor(0, 0, 0, 255),
			EColor(255, 255, 255, 255),
			EColor(0, 0, 0, 255),
			EColor(255, 255, 255, 255),
			EColor(0, 0, 0, 255),
			EColor(0, 0, 0, 255),
			EColor(0, 0, 0, 255),
			EColor(0, 0, 0, 255),
			EColor(0, 0, 0, 255),
			EColor(0, 0, 128, 255),
			EColor(255, 255, 255, 255),
			EColor(0, 0, 255, 255),
			EColor(255, 0, 255, 255),
		}, 1),
		EPalette::PaletteData({
			EColor(0, 0, 0, 255),
			EColor(0, 0, 0, 255),
			EColor(0, 0, 0, 255),
			EColor(255, 255, 220, 255),
			EColor(0, 0, 0, 255),
			EColor(0, 0, 0, 255),
			EColor(0, 0, 0, 255),
			EColor(0, 0, 0, 255),
			EColor(0, 0, 0, 255),
			EColor(0, 0, 0, 255),
			EColor(0, 0, 0, 255),
			EColor(0, 0, 0, 255),
			EColor(0, 0, 0, 255),
			EColor(0, 0, 128, 255),
			EColor(255, 255, 255, 255),
			EColor(0, 0, 255, 255),
			EColor(255, 0, 255, 255),
		}, 1),
	};

	EPalette::EPalette() {
		for (int i = 0; i < 3; ++i) {
			data[i] = defaultPalette + i;
			++data[i]->ref;
		}
	}

	EPalette::EPalette(const EPalette& p) {
		for (int i = 0; i < 3; ++i) {
			data[i] = p.data[i];
			++data[i]->ref;
		}
	}

	EPalette::~EPalette() {
		for (int i = 0; i < 3; ++i) {
			if (!--data[i]->ref) {
				delete data[i];
			}
		}
	}

	EPalette& EPalette::operator=(const EPalette& p) {
		for (int i = 0; i < 3; ++i) {
			++p.data[i]->ref;
			if (!--data[i]->ref) {
				delete data[i];
			}
			data[i] = p.data[i];
		}
		return *this;
	}

	void EPalette::setColor(EPaletteGroup group, EPaletteRole role, const EColor& c) {
		if (data[group]->ref > 1) {
			PaletteData* p = new PaletteData(*data[group]);
			--data[group]->ref;
			p->ref = 1;
			data[group] = p;
		}
		data[group]->colors[role] = c;
	}

}