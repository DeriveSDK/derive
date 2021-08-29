#pragma once

// Derive
#include "derive/display/Color.h"

namespace derive {
	namespace display {

		typedef struct BitmapDataS {
			colorARGB* data = nullptr;
			unsigned short width = 0;
			unsigned short height = 0;
		} BitmapData;

	} // display
} // derive