// Derive
#include "../Dispatcher.h"

// Other
#include <algorithm>

namespace derive {
	namespace events {

		Dispatcher::Dispatcher() { }

		Dispatcher::~Dispatcher() {
			clear();
		}

		void Dispatcher::clear() {
			for (auto listener : listeners) delete listener;
			listeners.clear();
		}

		void Dispatcher::remove( Listener* listener ) {
			listeners.erase( std::remove( listeners.begin(), listeners.end(), listener ), listeners.end() );
		}

		Listener* Dispatcher::listen( int type, Dispatch callback ) {
			Listener* listener = new Listener( type, callback );
			listeners.push_back( listener );
			return listener;
		}

		void Dispatcher::dispatch( Event* event ) {
			auto it = listeners.begin();
			while ( it != listeners.end() ) {
				if ( (( *it )->type == event->type ) && (!(*it)->callback(event))) {
					delete *it;
					it = listeners.erase( it );
				}
				else {
					++it;
				}
			}
		}

	} // events
} // derive