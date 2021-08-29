#pragma once

// Derive
#include "derive/events/Event.h"

using namespace std;

namespace derive {
	namespace events {

		/**
		 * @brief Events that relate to the keyboard and text entry
		 *
		 */
		class KeyEvent : public Event {
		public:
			KeyEvent() : Event() { }
			KeyEvent( int type ) : Event( type ) { }
			KeyEvent( int type, void* target ) : Event( type, target ) { }

			enum {
				// Key pressed and released
				press = 130,
				// Key press repeated (held down)
				repeat = 131,
				// Key down stroke
				down = 132,
				// Key up stroke (released)
				up = 133,
				// Text input is received 
				input = 134,
			};

			int keyCode = 0;
			int scanCode = 0;

			bool alt = false;
			bool shift = false;
			bool ctrl = false;
			bool super = false;
			bool capsLock = false;
			bool numLock = false;
		};

	} // events
} // derive