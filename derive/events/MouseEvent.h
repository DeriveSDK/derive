#pragma once

// Derive
#include "derive/events/KeyEvent.h"

namespace derive {
	namespace events {

		/**
		 * @brief Events that relate to mouse actions
		 *
		 */
		class MouseEvent : public KeyEvent {
		public:
			MouseEvent() : KeyEvent() { }
			MouseEvent( int type ) : KeyEvent( type ) { }
			MouseEvent( int type, void* target ) : KeyEvent( type, target ) { }

			enum {
				// Mouse moves over an object
				over = 100,
				// Mouse moves out of an object
				out = 101,
				// Mouse changes position
				move = 102,

				// Left button clicked
				click = 103,
				// Left button double clicked
				dblClick = 104,
				// Left button pressed down
				down = 105,
				// Left button released
				up = 106,
				// Left button released outside of the window
				releaseOutside = 107,

				// Right button clicked
				rightClick = 108,
				// Right button double clicked
				rightDblClick = 109,
				// Right button pressed down
				rightDown = 110,
				// Right button released
				rightUp = 111,
				// Right button released outside of the window
				rightReleaseOutside = 112,

				// Middle button clicked
				middleClick = 113,
				// Middle button double clicked
				middleDblClick = 114,
				// Middle button pressed down
				middleDown = 115,
				// Middle button released
				middleUp = 116,
				// Middle button released outside of the window
				middleReleaseOutside = 117,

				// Scroll wheel is used (can be X and/or Y)
				scroll = 118,
			};

			// The X coordinate of the mouse cursor within the object
			double localX = 0;

			// The Y coordinate of the mouse cursor within the object
			double localY = 0;

			// The X coordinate of the mouse cursor in global space
			double stageX = 0;

			// The Y coordinate of the mouse cursor in global space
			double stageY = 0;

			// For move event, the amount of movement in the X direction in global space
			double moveX = 0;

			// For move event, the amount of movement in the Y direction in global space
			double moveY = 0;

			// For a scroll event, the amount of scroll in the X direction
			double scrollX = 0;

			// For a scroll event, the amount of scroll in the Y direction
			double scrollY = 0;
		};

	} // events
} // derive