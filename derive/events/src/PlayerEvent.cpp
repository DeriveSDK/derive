#include "derive/events/PlayerEvent.h"

namespace derive {
	namespace events {

		// Allocate the pool
		list<MemoryPool*>* PlayerEvent::Pool = new list<MemoryPool*>();

	}
}
