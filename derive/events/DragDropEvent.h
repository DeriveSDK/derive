#pragma once

namespace derive {
	namespace events {

		/**
		 * @brief Events that relate to drag and drop
		 *
		 */
		enum class DragDropEvent : int {
			// An object is being dragged
			start = 150,
			// An object has been released
			stop = 151,
			// An object is being dragged
			drag = 152,
			// An object has been dropped on a drop target
			drop = 153,
			// An object has been dropped outside a drop target or window
			dropOutside = 154,
			// An object has been dragged over a drop target
			over = 155,
			// An object has been dragged out of a drop target
			out = 156,
		};

	} // events
} // derive