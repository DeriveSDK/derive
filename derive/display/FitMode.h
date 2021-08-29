#pragma once

namespace derive {
	namespace display {

		/**
		 * @brief How to fit an object within an area
		 *
		 */
		class FitMode {
		public:
			// The entire object is contained within the area, maintaining aspect ratio
			static const int Contain = 0;

			// The object completely covers the area with clipping, maintaining aspect ratio
			static const int Cover = 1;

			// The object is stretched to fill the area. Aspect ratio may not be maintained.
			static const int Stretch = 2;

			// The object width is completely contained, maintaining aspect ratio. The height may clip. 
			static const int Width = 3;

			// The object height is completely contained, maintaining aspect ratio. The width may clip. 
			static const int Height = 4;

			// Like Contain, but only allow the object to get bigger. If it already larger it will clip
			static const int Grow = 5;

			// Like Contain, but only allow the object to get smaller. If it is already smaller there will be no change
			static const int Shrink = 6;

			// The default mode
			static const int Default = Contain;
			// The maximum mode
			static const int Max = Shrink;

			// Helper to check value is within bounds
			static const int Check( int mode ) {
				if ( mode < 0 || mode > Max ) mode = Default;
				return mode;
			}
		};

	} // ns:display
} // ns:derive