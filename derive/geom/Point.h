#pragma once

// Other
#include <algorithm>
#include <utility>

using namespace std;

namespace derive {
	namespace geom {

		/**
		 * @brief A class that describes a point in 2D space
		 *
		 */
		class Point {
		public:
			/**
			 * @brief The X coordinate
			 * 
			 */
			double x;

			/**
			 * @brief The Y coordinate
			 * 
			 */
			double y;

			/**
			 * @brief Construct a new Point object with e supplied position
			 *
			 * @param x The X coordinate of the top-left corner
			 * @param y The Y coordinate of the top-left corner
			 */
			Point( double x = 0, double y = 0 );

			/**
			 * @brief Construct a new Point object with the same position as the supplied point
			 * @see clone
			 * @param p The point
			 */
			Point( Point* p );

			/**
			 * @brief Destroy the Point object
			 *
			 */
			virtual ~Point();

			/**
			 * @brief Clear the point
			 * Point is set to (0,0)
			 */
			void clear();

			/**
			 * @brief Sets both x and y coordinates
			 *
			 * @param x The X coordinate
			 * @param y The Y coordinate
			 */
			void set( double x, double y );

			/**
			 * @brief Sets both x and y coordinates from another point
			 * @see copy
			 * @param p The point
			 */
			void set( Point* p );

			/**
			 * @brief Check if the oint is equal to a coordinate
			 *
			 * @param x The X coordinate
			 * @param y The Y coordinate
			 * @return true If the supplied point is the same as this one
			 * @return false If the supplied point is different
			 */
			bool equals( double x, double y );

			/**
			 * @brief Check if the oint is equal to a coordinate
			 *
			 * @param x The X coordinate
			 * @param y The Y coordinate
			 * @return true If the supplied point is the same as this one
			 * @return false If the supplied point is different
			 */
			bool equals( Point* p );

			/**
			 * @brief Move the point by the specified amount
			 * @see add
			 * @param p The point that represents the amount to translate
			 */
			void translate( Point* p );

			/**
			 * @brief Move the point by the specified amount
			 * @see add
			 * @param x The distance to translate in the x direction
			 * @param y The distance to translate in the y direction
			 */
			void translate( double x, double y );

			/**
			 * @brief Add another point to this
			 * @see translate
			 * @param p The point to add
			 */
			void add( Point* p );
			void add( double x, double y );

			/**
			 * @brief Subtract another point from this
			 * @see translate
			 * @see add
			 * @param p The point to subtract
			 */
			void subtract( Point* p );
			void subtract( double x, double y );

			/**
			 * @brief Rotate the point about the origin
			 *
			 * @param angle The angle to rotate in radians
			 */
			void rotate( double angle );

			/**
			 * @brief Rotate the point about another point
			 *
			 * @param angle The angle to rotate in radians
			 * @param p The point to rotate about
			 */
			void rotate( double angle, Point* p );
			void rotate( double angle, double x, double y );

			/**
			 * @brief Copy the details from the supplied point to this one
			 *
			 * @param from The point to copy from
			 */
			void copy( Point* from );

			/**
			 * @brief Return a clone of this point
			 *
			 * @return Point* The new point that clones this one
			 */
			Point* clone();

		};

	} // geom
} // derive