// Derive
#include "../Event.h"

// Other
#include <algorithm>

namespace derive {
	namespace events {

		Event::Event() { }
		Event::Event( int type ) {
			this->type = type;
		}
		Event::Event( int type, void* target ) {
			this->type = type;
			this->target = target;
		}
		void Event::stopPropagation() {
			propogate = PropogationType::None;
		}

	} // events
} // derive