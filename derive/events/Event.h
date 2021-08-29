#pragma once

namespace derive {
	namespace events {

		/**
		 * @brief How the event should propogate
		 *
		 */
		class PropogationType {
		public:
			// stop propogation has been called
			static const int None = 0;
			// event is fired once on an object and does not propogate
			static const int Once = 1;
			// event propogates from an object upwards (through children)
			static const int Upward = 2;
			// event propogates from an object downwards (through parent)
			static const int Downward = 3;
		};

		/**
		 * @brief Base class for all events
		 */
		class Event {
		public:
			Event();
			Event( int type );
			Event( int type, void* target );

			// The type of the event
			int type = 0;

			// How the event should propogate after firing
			int propogate = PropogationType::Once;

			// The object that triggered the event
			void* target = nullptr;

			/**
			 * @brief Stop the event from propopagtion
			 */
			void stopPropagation();
		};

	} // events
} // derive