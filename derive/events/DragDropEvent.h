#pragma once

// Derive
#include "derive/events/Event.h"

namespace derive {
	namespace events {

		/**
		 * @brief Events that relate to errors
		 *
		 */
		class DragDropEvent : public Event {
		public:

			// An object is being dragged
			static const int Start = 150;
			// An object has been released
			static const int Stop = 151;
			// An object is being dragged
			static const int Drag = 152;
			// An object has been dropped on a drop target
			static const int Drop = 153;
			// An object has been dropped outside a drop target or window
			static const int DropOutside = 154;
			// An object has been dragged over a drop target
			static const int Over = 155;
			// An object has been dragged out of a drop target
			static const int Out = 156;
		};

	} // events
} // derive