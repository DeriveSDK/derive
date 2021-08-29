#pragma once

// Derive
#include "derive/events/Event.h"

// Other
#include <string>

using namespace std;

namespace derive {
	namespace events {

		/**
		 * @brief Events that relate to errors
		 *
		 */
		class ErrorEvent : public Event {
		public:
			// unknown error
			static const int Unknown = 0;

			string name = "";
			string message = "";
		};

	} // events
} // derive