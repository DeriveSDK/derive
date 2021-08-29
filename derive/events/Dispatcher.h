#pragma once

//Derive
#include "derive/events/Event.h"

// Other
#include <functional>
#include <vector>

namespace derive {
	namespace events {

		/**
		 * @brief The function signature for dispatches
		 */
		typedef std::function<bool( Event* event )> Dispatch;

		/**
		 * @brief A dispatch listener
		 */
		class Listener {
		public:
			Listener( int type, Dispatch callback ) : type( type ), callback( callback ) { }
			int type;
			Dispatch callback;
		};

		/**
		 * @brief How the event should propogate
		 *
		 */
		class Dispatcher {
		protected:
			std::vector<Listener*> listeners;
		public:
			/**
			 * @brief Construct a new Dispatcher object
			 */
			Dispatcher();

			/**
			 * @brief Destroy the Dispatcher object
			 */
			~Dispatcher();

			/**
			 * @brief Remove all listeners
			 */
			void clear();

			/**
			 * @brief Remove a specific listener
			 *
			 * @param listener
			 */
			void remove( Listener* listener );

			/**
			 * @brief Listen for a specific event type
			 * Example: listen( Event::Update, [this](Event* event) -> bool { return this.onUpdate(event); })
			 * @param type The event type
			 * @param callback The function listening for the event. The callback receives an Event and returns a boolean
			 */
			Listener* listen( int type, Dispatch callback );

			/**
			 * @brief Dispatch an event to all listeners of that event
			 * @param event The event to dispatch
			 */
			void dispatch( Event* event );
		};

	} // events
} // derive