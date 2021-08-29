#pragma once

namespace derive {
	namespace display {

		/**
		 * @brief The display mode opf the player window
		 */
		class DisplayMode {
		public:
			// The contents should entirely cover the window (some clipping may occur)
			static const int Cover = 0;
			// The contents should be contained by the window (unwanted content may be visible)
			static const int Contain = 1;
			// The contents should be contained by the window and unwanted content obscured by the letterbox
			static const int Letterbox = 2;

			// the default value
			static const int Default = Cover;
			// The maximum value
			static const int Max = Letterbox;

			// Helper to check value is within bounds
			static const int Check( int mode ) {
				if ( mode < 0 || mode > Max ) mode = Default;
				return mode;
			}
		};

	} // ns:display
} // ns:derive