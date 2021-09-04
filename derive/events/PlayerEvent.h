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
			PlayerEvent(int type) : Event(type) { }

			// Dispatched on every update cycle
			static const int Update = 10;

			// Dispatched on every render cycle
			static const int Render = 11;

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

			/**
			 * @brief Clear event to defaults
			 */
			virtual void reset() {
				Event::reset();
				dt = 0;
				width = 0;
				height = 0;
			}

			// ### MEMORY POOLING

			/**
			 * Create a new object or take one from the pool
			 * @return The new or recycled object
			 */
			static PlayerEvent* Create() {
				return (PlayerEvent*)MemoryPool::Create<PlayerEvent>();
			}
			static PlayerEvent* Create(int type) {
				PlayerEvent* event = Create();
				event->type = type;
				return event;
			}
		protected:
			/**
			 * Memory pool of recycled objects
			 */
			friend class MemoryPool;
			static list<MemoryPool*>* Pool;

			/**
			 * Pool getter
			 */
			virtual list<MemoryPool*>* _getPool() {
				return PlayerEvent::Pool;
			}
		};

	} // events
} // derive