#pragma once

namespace derive {
	namespace display {

		/**
		 * @brief The method of scaling the content to fit the window
		 */
		class ScaleMode {
		public:
			// Scale the content to exactly fit the window
			static const int Exact = 0;
			// Scale so that pixels are whole numbers (pixel art will remain crisp)
			static const int Pixel = 1;
			// Do not scale the content
			static const int None = 2;

			// the default value
			static const int Default = Exact;
			// The maximum value
			static const int Max = Pixel;

			// Helper to check value is within bounds
			static const int Check( int mode ) {
				if ( mode < 0 || mode > Max ) mode = Default;
				return mode;
			}
		};

	} // ns:display
} // ns:derive