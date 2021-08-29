#pragma once

// Derive
#include "derive/geom/Point.h"

// Other
#include <algorithm>
#include <utility>

using namespace std;

namespace derive {
	namespace geom {

		/**
		 * @brief A class that describes a bounded area
		 *
		 */
		class Bounds {
		private:
			double _x1 = 0;
			double _y1 = 0;
			double _x2 = 0;
			double _y2 = 0;
			double _width = 0;
			double _height = 0;

			inline void recalc();
			inline void recalc2();
		public:

			/**
			 * @brief Construct a new Bounds object with e supplied position and size
			 *
			 * @param x The X coordinate of the top-left corner
			 * @param y The Y coordinate of the top-left corner
			 * @param width The width of the bounds
			 * @param height The height of the bounds
			 */
			Bounds( double x = 0, double y = 0, double width = 0, double height = 0 );

			/**
			 * @brief Destroy the Bounds object
			 *
			 */
			virtual ~Bounds();

			/**
			 * @brief Get the X coordinate of the top-left corner
			 *
			 * @return double The X coordinate of the top-left corner
			 */
			double x() const;

			/**
			 * @brief Set the X coordinate of the top-left corner
			 * The width  remains the same, and the bottom-right corner is recalculated
			 * @param x The X coordinate of the top-left corner
			 */
			void x( double x );

			/**
			 * @brief Get the Y coordinate of the top-left corner
			 *
			 * @return double The Y coordinate of the top-left corner
			 */
			double y() const;

			/**
			 * @brief Set the Y coordinate of the top-left corner
			 * The height remains the same, and the bottom-right corner is recalculated
			 * @param x The Y coordinate of the top-left corner
			 */
			void y( double y );

			/**
			 * @brief Get the X coordinate of the bottom-right corner
			 *
			 * @return double The X coordinate of the bottom-right corner
			 */
			double x2() const;

			/**
			 * @brief Set the X coordinate of the bottom-right corner
			 * The top-left corner is not affected and the width is recalculated
			 * @param x The X coordinate of the bottom-right corner
			 */
			void x2( double x );

			/**
			 * @brief Get the Y coordinate of the bottom-right corner
			 *
			 * @return double The Y coordinate of the bottom-right corner
			 */
			double y2() const;

			/**
			 * @brief Set the Y coordinate of the bottom-right corner
			 * The top-left corner is not affected and the height is recalculated
			 * @param x The Y coordinate of the bottom-right corner
			 */
			void y2( double y );

			/**
			 * @brief Get the width
			 *
			 * @return double The width
			 */
			double width() const;

			/**
			 * @brief Set the width
			 * The bottom-right corner is recalculated
			 * @param w The width
			 */
			void width( double w );

			/**
			 * @brief Get the height
			 *
			 * @return double The height
			 */
			double height() const;

			/**
			 * @brief Set the height
			 * The bottom-right corner is recalculated
			 * @param w The height
			 */
			void height( double h );

			/**
			 * @brief Check if the bounds area is empty
			 *
			 * @return true If the area is empty
			 * @return false If the area is not empty
			 */
			bool empty();

			/**
			 * @brief Clear the bounds
			 * All coordinates and width and height are reset to 0.0. The bounds are empty
			 */
			void clear();

			/**
			 * @brief Set the top-left corner of the bounds
			 * The width and height are not affected, and the bottom-right corner is recalculated
			 * @param x The X coordinate of the top-left corner
			 * @param y The Y coordinate of the top-left corner
			 */
			void setPos( Point* p );

			/**
			 * @brief Set the top-left corner of the bounds
			 * The width and height are not affected, and the bottom-right corner is recalculated
			 * @param x The X coordinate of the top-left corner
			 * @param y The Y coordinate of the top-left corner
			 */
			void setPos( double x, double y );

			/**
			 * @brief Set both the top-left and bottom-right corners of the bounds
			 * The width and height are recalculated
			 * @param x The X coordinate of the top-left corner
			 * @param y The Y coordinate of the top-left corner
			 * @param x2 The X coordinate of the bottom-right corner
			 * @param y2 The Y coordinate of the bottom-right corner
			 */
			void setPos( double x, double y, double x2, double y2 );

			/**
			 * @brief Set the bottom-right corner of the bounds
			 * The top-left corner is not affected, and the width and height are recalculated
			 * @param x The X coordinate of the bottom-right corner
			 * @param y The Y coordinate of the bottom-right corner
			 */
			void setPos2( Point* p );

			/**
			 * @brief Set the bottom-right corner of the bounds
			 * The top-left corner is not affected, and the width and height are recalculated
			 * @param x The X coordinate of the bottom-right corner
			 * @param y The Y coordinate of the bottom-right corner
			 */
			void setPos2( double x, double y );

			/**
			 * @brief Set both the top-left and the size of the bounds
			 * The bottom-right corner is recalculated
			 * @param p The point for top-left corner
			 * @param width The width
			 * @param height The height
			 */
			void set( Point* p, double width, double height );

			/**
			 * @brief Set both the top-left and the size of the bounds
			 * The bottom-right corner is recalculated
			 * @param x The X coordinate of the top-left corner
			 * @param y The Y coordinate of the top-left corner
			 * @param width The width
			 * @param height The height
			 */
			void set( double x, double y, double width, double height );

			/**
			 * @brief Check if the supplied bounds is contained completely within this one
			 * @see overlaps To check for partial overlap
			 * @param bounds The bounds to check
			 * @return true If the supplied bounds are completely contained within this one
			 * @return false If the supplied bounds are not completed contained within this one
			 */
			bool contains( Bounds* bounds );

			/**
			 * @brief Check if the supplied point is within these bounds
			 *
			 * @param p The point
			 * @return true If the point is within the bounds
			 * @return false If the point is outside the bounds
			 */
			bool contains( Point* p );

			/**
			 * @brief Check if the supplied point is within these bounds
			 *
			 * @param x The X coordinate to check
			 * @param y The Y coordinate to check
			 * @return true If the point is within the bounds
			 * @return false If the point is outside the bounds
			 */
			bool contains( double x, double y );

			/**
			 * @brief Check if the supplied X coordinate is within the bounds
			 *
			 * @param x The X coordinate to check
			 * @return true If the supplied coordinate is within the bounds
			 * @return false If the supplied coordinate is outside the bounds
			 */
			bool containsX( double x );

			/**
			 * @brief Check if the supplied Y coordinate is within the bounds
			 *
			 * @param x The Y coordinate to check
			 * @return true If the supplied coordinate is within the bounds
			 * @return false If the supplied coordinate is outside the bounds
			 */
			bool containsY( double y );

			/**
			 * @brief Check if any area of the supplied bounds overlaps with this one
			 *
			 * @param bounds The bounds to check for overlap
			 * @return true If the bounds partially of fully overlap
			 * @return false If the bounds do not overlap
			 */
			bool overlaps( Bounds* bounds );

			/**
			 * @brief Move the bounds by the point
			 *
			 * @param p The point
			 */
			void translate( Point* p );

			/**
			 * @brief Move the bounds by the supplied X and Y distance
			 *
			 * @param x The distance to move in the X direction
			 * @param y The distance to move in the Y direction
			 */
			void translate( double x, double y );

			/**
			 * @brief Grow to include the supplied bounds (Union)
			 *
			 * @param bounds The bounds to include
			 */
			void grow( Bounds* bounds );

			/**
			 * @Brief Clip to the supplied bounds (intersection)
			 *
			 * @param bounds The bounds to clip to
			 */
			void clip( Bounds* bounds );

			/**
			 * @brief Copy the details from the supplied bounds to this one
			 *
			 * @param from The bounds to copy from
			 */
			void copy( Bounds* from );

			/**
			 * @brief Return a clone of this bounds
			 *
			 * @return Bounds* The new bounds that clone this one
			 */
			Bounds* clone();

		};

	} // geom
} // derive