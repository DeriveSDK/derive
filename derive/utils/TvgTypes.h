#pragma once

// Derive
#include "derive/geom/Matrix.h"
// ThorVG
#include "thorvg.h"

using namespace derive::geom;

namespace derive {
	namespace utils {

		/**
		 * @brief A class for conversion to and from Rive types
		 *
		 */
		class TvgTypes {
		public:
			/**
			 * @brief Convert matrix to Rive matrix
			 * float xx() const { return m_Buffer[0]; }
			 * float xy() const { return m_Buffer[1]; }
			 * float yx() const { return m_Buffer[2]; }
			 * float yy() const { return m_Buffer[3]; }
			 * float tx() const { return m_Buffer[4]; }
			 * float ty() const { return m_Buffer[5]; }
			 * @param matrix The matrix to convert
			 * @return Mat2D* A new Rive matrix
			 */
			static tvg::Matrix* convert( Matrix* matrix ) {
				tvg::Matrix* mat = new tvg::Matrix { 1, 0, 0, 0, 1, 0, 0, 0, 1 };
				mat->e11 = matrix->a;
				mat->e12 = matrix->c;
				mat->e13 = matrix->tx;
				mat->e21 = matrix->b;
				mat->e22 = matrix->d;
				mat->e23 = matrix->ty;
				return mat;
			}

			/**
			 * @brief Convert matrix to Rive matrix
			 *
			 * @param from The matrix to convert from
			 * @param to (out) The matrix to copy values to
			 */
			static void convert( Matrix* from, tvg::Matrix* to ) {
				to->e11 = from->a;
				to->e12 = from->c;
				to->e13 = from->tx;
				to->e21 = from->b;
				to->e22 = from->d;
				to->e23 = from->ty;
			}

		};

	} // utils
} // derive