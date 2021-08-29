#pragma once

namespace derive {
	namespace display {

		/**
		 * @brief Alignment of content to the window
		 */
		class AlignMode {
		public:
			// Align to center, both vertically and horizontally
			static const int Center = 0;

			// Top center
			static const int Top = 1;

			// Bottom center
			static const int Bottom = 2;

			// Left center
			static const int Left = 4;

			// Right center
			static const int Right = 8;

			// Left top corner
			static const int LeftTop = Left | Top;

			// Left bottom corner
			static const int LeftBottom = Left | Bottom;

			// Right top corner
			static const int RightTop = Right | Top;

			// Right bottom corner
			static const int RightBottom = Right | Bottom;

			// the default value
			static const int Default = Center;
			// The maximum value
			static const int Max = 15;

			// Helper to check value is within bounds
			static const int Check( int mode ) {
				if ( mode < 0 || mode > Max ) mode = Default;
				return mode;
			}
		};

	} // ns:display
} // ns:derive