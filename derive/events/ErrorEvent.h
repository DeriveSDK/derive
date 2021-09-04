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

			// The error name
			string name = "";

			// The error message
			string message = "";

			// The stack trace
			string stack = "";

			/**
			 * @brief Clear event to defaults
			 */
			virtual void reset() {
				Event::reset();
				name = "";
				message = "";
				stack = "";
			}
		};

	} // events
} // derive