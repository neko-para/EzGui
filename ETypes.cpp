#include "ETypes.h"

namespace Eg {

	static EColor globalColors[NUMBER_OF_GLOBAL_COLORS] = {
		{1.0, 1.0, 1.0},
		{0.0, 0.0, 0.0},
		{1.0, 0.0, 0.0},
		{0.5, 0.0, 0.0},
		{0.0, 1.0, 0.0},
		{0.0, 0.5, 0.0},
		{0.0, 0.0, 1.0},
		{0.0, 0.0, 0.5},
		{0.0, 1.0, 1.0},
		{0.0, 0.5, 0.5},
		{1.0, 0.0, 1.0},
		{0.5, 0.0, 0.5},
		{1.0, 1.0, 0.0},
		{0.5, 0.5, 0.0},
		{0xa0, 0xa0, 0xa4},
		{0.5, 0.5, 0.5},
		{0xc0, 0xc0, 0xc0},
		{0.0, 0.0, 0.0, 0.0}
	};

	EColor::EColor(EGlobalColor g) {
		*this = globalColors[g];
	}

}