#pragma once

#include "derive/geom/Point.h"

using namespace std;

namespace derive {
	namespace geom {

		/**
		 * @brief A class that describes a point in 2D space
		 * | a c tx|
		 * | b d ty|
		 * | u v w |
		 */
		class Matrix {
		public:
			/**
			 * @brief X scale/rotate factor
			 */
			double a = 1.0;

			/**
			 * @brief Y skew/rotate factor
			 */
			double b = 0.0;

			/**
			 * @brief X skew/rotate factor
			 */
			double c = 0.0;

			/**
			 * @brief Y scale/rotate factor
			 */
			double d = 1.0;

			/**
			 * @brief X translate amount
			 */
			double tx = 0.0;

			/**
			 * @brief Y translate amount
			 */
			double ty = 0.0;

			/**
			 * @brief Construct a new identity Matrix object
			 *
			 */
			Matrix();

			/**
			 * @brief Construct a new Matrix object with the specified transformations
			 *
			 * @param scaleX Scale along the X axis
			 * @param scaleY Scale along the Y axis
			 * @param rotation Rotation in radians
			 * @param tx Translation along the X axis
			 * @param ty Translation along the Y axis
			 * @param ox Origin X coordinate
			 * @param oy Origin Y coordinate
			 */
			Matrix( double scaleX, double scaleY, double rotation, double tx, double ty, double ox = 0.0, double oy = 0.0 );

			/**
			 * @brief Destroy the Point object
			 *
			 */
			virtual ~Matrix() {}

			/**
			 * @brief Apply the transformations to the current matrix
			 *
			 * @param scaleX Scale along the X axis
			 * @param scaleY Scale along the Y axis
			 * @param rotation Rotation in radians
			 * @param tx Translation along the X axis
			 * @param ty Translation along the Y axis
			 * @param ox Origin X coordinate
			 * @param oy Origin Y coordinate
			 */
			void apply( double scaleX, double scaleY, double rotation, double tx, double ty, double ox = 0.0, double oy = 0.0 );

			/**
			 * @brief Transform a point using the matrix
			 *
			 * @param p (out) The point to transform
			 */
			void transform( Point* p );

			/**
			 * @brief Transform an offset point using the matrix
			 *
			 * @param p (out) The point to transform
			 */
			void transform( Point* p, double originX, double originY );

			/**
			 * @brief Transform a point using the matrix
			 *
			 * @param from The point to transform
			 * @param to (out) The transformed point
			 */
			void transform( Point* from, Point* to );

			/**
			 * @brief Transform a point using the matrix and return a Point with the new values
			 *
			 * @param x The X coordinate
			 * @param x The Y coordinate
			 */
			Point* transform( double x, double y );

			/**
			 * @brief Transform a point using the inverse matrix
			 *
			 * @param p (out) The point to transform
			 */
			void inverseTransform( Point* p );

			/**
			 * @brief Transform an offset point using the inverse matrix
			 *
			 * @param p (out) The point to transform
			 */
			void inverseTransform( Point* p, double ox, double oy );

			/**
			 * @brief Transform a point using the inverse matrix
			 *
			 * @param from The point to transform
			 * @param to (out) The transformed point
			 */
			void inverseTransform( Point* from, Point* to );

			/**
			 * @brief Transform the point using the inverse matrix and return a Point with the new values
			 *
			 * @param x The X coordinate
			 * @param x The Y coordinate
			 */
			Point* inverseTransform( double x, double y );

			/**
			 * @brief Set the matrix to the identity matrix
			 *
			 */
			void identity();

			/**
			 * @brief Concatenate a matrix to this one (combine)
			 *
			 * @param m The matrix to concatenate
			 */
			void concat( Matrix* m );

			/**
			 * @brief Invert the matrix
			 *
			 */
			void invert();

			/**
			 * @brief Rotate the matrix
			 *
			 * @param angle The angle in radians
			 */
			void rotate( double angle );

			/**
			 * @brief Rotate the matrix about a point
			 *
			 * @param angle The angle in radians
			 * @param ox The rotation point X coordinate
			 * @param oy The rotation point Y coordinate
			 */
			void rotate( double angle, double ox, double oy );

			/**
			 * @brief Scale the matrix
			 *
			 * @param sx
			 * @param sy
			 */
			void scale( double sx, double sy );

			/**
			 * @brief Translatet the matrix
			 *
			 * @param dx The distance along the X axis
			 * @param dy The distance along the Y axis
			 */
			void translate( double dx, double dy );

			/**
			 * @brief Copy the details from the supplied matrix to this one
			 *
			 * @param from The matrix to copy from
			 */
			void copy( Matrix* from );

			/**
			 * @brief Return a clone of this matrix
			 *
			 * @return Matrix* The new matrix that clones this one
			 */
			Matrix* clone();

		};

	} // geom
} // derive