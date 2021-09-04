#pragma once

// Derive
#include "derive/mem/MemoryPool.h"

using namespace derive::mem;

namespace derive {
	namespace events {

		/**
		 * @brief Base class for all events
		 */
		class Event: public MemoryPool {
		public:
			Event() {}
			Event( int type ) : type( type ) {}
			Event( int type, void* target ) : type( type ), target( target ) {}
			virtual ~Event(){}

			// The type of the event
			int type = 0;

			// How the event should propogate after firing
			bool cancelled = false;

			// The object that triggered the event
			void* target = nullptr;

			/**
			 * @brief Reset all event properties back to defaults
			 */
			virtual void reset() {
				type = 0;
				cancelled = false;
				target = nullptr;
			}

			/**
			 * @brief Stop the event from propogation
			 * Same as setting cancelled to true
			 */
			virtual void stopPropagation() {
				cancelled = true;
			}
		};

	} // events
} // derive