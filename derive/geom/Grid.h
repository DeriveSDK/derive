#pragma once

// Derive
#include "derive/geom/Point.h"

using namespace derive::geom;

namespace derive {
	namespace geom {

		/**
		 * @brief A class that describes a grid
		 *
		 */
		class Grid {
		private:
			Point* _origin = nullptr;
			Point* _cell;
			Point* _limit = nullptr;
		public:

			/**
			 * @brief Construct a new Grid with the supplied size
			 * @param width The width of each cell
			 * @param height The height of each cell
			 */
			Grid( double width = 0, double height = 0 );

			/**
			 * @brief Destroy the Grid object
			 */
			virtual ~Grid();

			/**
			 * @brief Snap a point to the grid
			 * @param p The point to snap. Most be in same coordinate space as the grid
			 */
			void snap( Point* p );

			/**
			 * @brief Set the cell size
			 * @param p The point that describes the cell size
			 */
			void cell( Point* p );

			/**
			 * @brief Return the cell size
			 * The method returns a copy of the Point
			 * @return Point* A point describing the cell size
			 */
			Point* cell();

			/**
			 * @brief Set the grid origin
			 * Pass in null to clear the origin
			 * @param p The grid origin (top,left corner)
			 */
			void origin( Point* p );

			/**
			 * @brief Return the origin
			 * The method returns a copy of the Point
			 * @return Point* The origin
			 */
			Point* origin();

			/**
			 * @brief Set the grid limit
			 * Pass in null to clear the limit
			 * @param p The grid limit (bottom,right corner)
			 */
			void limit( Point* p );

			/**
			 * @brief Return the limit
			 * The method returns a copy of the Point
			 * @return Point* The limit
			 */
			Point* limit();

			/**
			 * @brief Clear the grid
			 */
			void clear();

			/**
			 * @brief Copy grid from another
			 *
			 * @param from The grid to copy values from
			 */
			void copy( Grid* from );

		};

	} // geom
} // derive