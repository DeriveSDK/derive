#pragma once

// Derive
#include "derive/events/Event.h"

namespace derive {
	namespace events {

		/**
		 * @brief Events that relate to the player
		 *
		 */
		class PlayerEvent : public Event {
		public:
			PlayerEvent() : Event() { }
			PlayerEvent( int type ) : Event( type ) { }
			PlayerEvent( int type, void* target ) : Event( type, target ) { }

			// Dispatched on every update cycle
			static const int Update = 10;

			// Dispatched on every render cycle
			static const int Render = 12;

			// Dispatched when the window is resized
			static const int Resize = 12;

			// The number of seconds since the last update or render
			// Available on Event::Update, Event::Render
			double dt = 0;

			// The window width
			// Available on Event::Resize
			int width = 0;

			// The window width
			// Available on Event::Resize
			int height = 0;
		};

	} // events
} // derive