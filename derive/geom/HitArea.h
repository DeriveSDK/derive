#pragma once

// Derive
#include "derive/geom/Point.h"

using namespace derive::geom;

namespace derive {
	namespace geom {

		/**
		 * @brief A class that describes a hit area
		 *
		 */
		class HitArea {
		public:
            /**
             * @brief Construct a new empty Hit Area object
             * 
             */
            HitArea() {}

			/**
			 * @brief Construct a new Hit Area object with given shape
			 * Note that the shape is managed by the hit area, so the hit area will
             * destroy it when the hit area is destroyed.
			 * @param shape The shape of the hit area
			 */
			HitArea( double x, double y ){
				this->x = x;
				this->y = y;
			}

			/**
			 * @brief Destroy the Grid object
			 */
			virtual ~HitArea() {}

			/**
			 * @brief Check if the point is within the hitarea
			 * @param p The point to check
			 */
			virtual bool hit( Point* p ){ return false; }

			/**
			 * @brief X coordinate
			 */
			double x = 0;

			/**
			 * @brief Y coordinate
			 */
			double y = 0;

			/**
			 * @brief Flag to indicate if the cursor is over the hit area 
			 * Set internally
			 */
			bool over = false;

			/**
			 * @brief Flag to indicate if mouse events are enabled
			 */
			bool enabled = true;

		};

	} // geom
} // derive