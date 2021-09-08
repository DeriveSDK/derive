#pragma once

//Derive
#include "derive/events/Event.h"

// Other
#include <functional>
#include <vector>
#include <iostream>

namespace derive {
	namespace events {

		/**
		 * @brief The function signature for dispatches
		 */
		typedef std::function<bool(Event*)> Dispatch;

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
			virtual ~Dispatcher();

			/**
			 * @brief Remove all listeners
			 */
			virtual void unlistenAll();

			/**
			 * @brief Remove listener
			 *
			 * @param listener
			 */
			void unlisten( Listener* listener );

			/**
			 * @brief Remove listeners by event type
			 *
			 * @param listener
			 */
			void unlisten( int type );

			/**
			 * @brief Remove listeners by callback
			 *
			 * @param listener
			 */
			void unlisten( Dispatch callback );

			/**
			 * @brief Listen for a specific event type
			 * Example: listen( PlayerEvent::Update, [this](Event* event) -> bool { return this.onUpdate( (PlayerEvent*)event ); })
			 * @param type The event type
			 * @param callback The function listening for the event. The callback receives an Event and returns a boolean
			 * @return Listener* The listener object
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