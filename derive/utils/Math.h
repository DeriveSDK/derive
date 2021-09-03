#pragma once

#include <math.h>

namespace derive {
	namespace utils {

		/**
		 * @brief Math helper functions
		 *
		 */
		class Math {
		public:
            /**
             * @brief Pi
             * 
             */
            static const double PI;

            /**
             * @brief Pi / 180
             * 
             */
            static const double PI_180;

			/**
             * @brief 1 / Pi
             * 
             */
            static const double INV_PI;

			/**
             * @brief 180 / Pi
             * 
             */
            static const double _180_PI;

			/**
			 * @brief Convert angle in radians to degrees
			 * 
			 * @param r The angle in radians
			 * @return double The angle in degrees
			 */
			static inline double radToDeg( double r ) {
				return r * _180_PI;
			}

            /**
			 * @brief Convert angle in degrees to radians
			 * 
			 * @param r The angle in degrees
			 * @return double The angle in radians
			 */
			static inline double degToRad( double r ) {
				return r * PI_180;
			}

		};

        const double Math::PI = 3.14159265358979323846;
		const double Math::INV_PI = 1 / Math::PI;
        const double Math::PI_180 = Math::PI / 180;
		const double Math::_180_PI = 180 / Math::PI;

	} // utils
} // derive