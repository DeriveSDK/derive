#pragma once

// Derive
#include "derive/geom/Matrix.h"
// Rive
#include "rive/math/mat2d.hpp"

using namespace derive::geom;

namespace derive {
	namespace utils {

		/**
		 * @brief A class for conversion to and from Rive types
		 *
		 */
		class RiveTypes {
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
			static rive::Mat2D* convert( derive::geom::Matrix* matrix ) {
				rive::Mat2D* mat = new rive::Mat2D();
				float* val = (float*)mat->values();
				val[0] = (float)matrix->a;
				val[1] = (float)matrix->b;
				val[2] = (float)matrix->c;
				val[3] = (float)matrix->d;
				val[4] = (float)matrix->tx;
				val[5] = (float)matrix->ty;
				return mat;
			}

			/**
			 * @brief Convert matrix to Rive matrix
			 *
			 * @param from The matrix to convert from
			 * @param to (out) The matrix to copy values to
			 */
			static void convert(derive::geom::Matrix* from, rive::Mat2D* to ) {
				float* val = (float*)to->values();
				val[0] = (float)from->a;
				val[1] = (float)from->b;
				val[2] = (float)from->c;
				val[3] = (float)from->d;
				val[4] = (float)from->tx;
				val[5] = (float)from->ty;
			}

		};

	} // utils
} // derive