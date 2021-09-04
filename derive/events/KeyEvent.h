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

			// Key pressed and released
			static const int Press = 130;

			// Key press repeated (held down)
			static const int Repeat = 131;

			// Key down stroke
			static const int Down = 132;

			// Key up stroke
			static const int Up = 133;

			// Text input is received
			static const int Input = 134;

			// the code of the key
			int keyCode = 0;

			// The keyboard scancode for the key
			int scanCode = 0;

			// ALT modifier key is down
			bool alt = false;

			// SHFT modifier key is down
			bool shift = false;

			// CTRL modifier key is down
			bool ctrl = false;

			// SUPER modifier key is down
			bool super = false;

			// CAPS modifier key is down
			bool capsLock = false;

			// NUMLCK modifier key is down
			bool numLock = false;

			/**
			 * @brief Clear event to defaults
			 */
			virtual void reset() {
				Event::reset();
				keyCode = 0;
				scanCode = 0;
				alt = false;
				shift = false;
				ctrl = false;
				super = false;
				capsLock = false;
				numLock = false;
			}
		};

	} // events
} // derive