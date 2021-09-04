#include "derive/events/MouseEvent.h"

namespace derive {
	namespace events {

		// Allocate the pool
		list<MemoryPool*>* MouseEvent::Pool = new list<MemoryPool*>();

	}
}
