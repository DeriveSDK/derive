#pragma once

// Derive
#include "derive/geom/Matrix.h"
// Skia
#include "core/SkMatrix.h"

namespace derive {
	namespace utils {

		/**
		 * @brief A class for conversion to and from Skia types
		 *
		 */
		class SkiaTypes {
		public:
			/**
			 * @brief Convert matrix to Skia matrix
			 * 
			 * @param matrix The matrix to convert
			 * @return SkMatrix* A new Skia matrix
			 */
			static SkMatrix* convert( derive::geom::Matrix* matrix ){
				SkMatrix* m = new SkMatrix();
				m->setAll(
					matrix->a,
					matrix->c,
					matrix->tx,
					matrix->b,
					matrix->d,
					matrix->ty,
					0.0,
					0.0,
					1.0
				);
				return m;
			}

			/**
			 * @brief Convert matrix to Skia matrix
			 * 
			 * @param from The matrix to convert from
			 * @param to (out) The matrix to copy values to
			 */
			static void convert( derive::geom::Matrix* from, SkMatrix* to ){
				to->setAll(
					from->a,
					from->c,
					from->tx,
					from->b,
					from->d,
					from->ty,
					0.0,
					0.0,
					1.0
				);
			}

		};

	} // utils
} // derive