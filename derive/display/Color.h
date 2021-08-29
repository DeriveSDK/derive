#pragma once

namespace derive {
	namespace display {

		/**
		 * @brief Packed color type with 8-bit R,G,B, A components
		 */
		typedef unsigned long colorARGB;

		class Color {
		public:
			/**
			 * @brief Return a colorARGB from r,g,b,a components
			 *
			 * @param r The red component (0-255)
			 * @param g The green component (0-255)
			 * @param b The blue component (0-255)
			 * @param a The alpha component (0-255)
			 * @return colorARGB The color
			 */
			inline static colorARGB rgba( unsigned char r, unsigned char g, unsigned char b, unsigned char a );

			/**
			 * @brief Return a colorARGB from r,g,b,a components
			 *
			 * @param r The red component (0-255)
			 * @param g The green component (0-255)
			 * @param b The blue component (0-255)
			 * @param a The alpha component (0.0 - 1.0)
			 * @return colorARGB The color
			 */
			inline static colorARGB rgba( unsigned char r, unsigned char g, unsigned char b, double a );

			/**
			 * @brief Return a colorARGB from r,g,b,a components
			 *
			 * @param r The red component (0.0 - 1.0)
			 * @param g The green component (0.0 - 1.0)
			 * @param b The blue component (0.0 - 1.0)
			 * @param a The alpha component (0.0 - 1.0)
			 * @return colorARGB The color
			 */
			inline static colorARGB rgba( double r, double g, double b, double a );

			/**
			 * @brief Convert a colorARGB to r,g,b,a components
			 *
			 * @param c The color to convert
			 * @param r (out) the red component (0-255)
			 * @param g (out) the green component (0-255)
			 * @param b (out) the blue component (0-255)
			 * @param a (out) the alpha component (0-255)
			 */
			inline static void rgba( colorARGB c, unsigned char& r, unsigned char& g, unsigned char& b, unsigned char& a );

			/**
			 * @brief Convert a colorARGB to r,g,b,a components
			 *
			 * @param c The color to convert
			 * @param r (out) the red component (0-255)
			 * @param g (out) the green component (0-255)
			 * @param b (out) the blue component (0-255)
			 * @param a (out) the alpha component (0.0-1.0)
			 */
			inline static void rgba( colorARGB c, unsigned char& r, unsigned char& g, unsigned char& b, double& a );

			/**
			 * @brief Convert a colorARGB to r,g,b,a components
			 *
			 * @param c The color to convert
			 * @param r (out) the red component (0.0-1.0)
			 * @param g (out) the green component (0.0-1.0)
			 * @param b (out) the blue component (0.0-1.0)
			 * @param a (out) the alpha component (0.0-1.0)
			 */
			inline static void rgba( colorARGB c, double& r, double& g, double& b, double& a );

			/**
			 * @brief Return a solid colorARGB from r,g,b components
			 *
			 * @param r The red component (0-255)
			 * @param g The green component (0-255)
			 * @param b The blue component (0-255)
			 * @return colorARGB The color
			 */
			inline static colorARGB rgb( unsigned char r, unsigned char g, unsigned char b );

			/**
			 * @brief Return a solid colorARGB from r,g,b components
			 *
			 * @param r The red component (0.0 - 1.0)
			 * @param g The green component (0.0 - 1.0)
			 * @param b The blue component (0.0 - 1.0)
			 * @return colorARGB The color
			 */
			inline static colorARGB rgb( double r, double g, double b );

			/**
			 * @brief Convert a colorARGB to r,g,b components
			 *
			 * @param c The color to convert
			 * @param r (out) the red component (0-255)
			 * @param g (out) the green component (0-255)
			 * @param b (out) the blue component (0-255)
			 */
			inline static void rgb( colorARGB c, unsigned char& r, unsigned char& g, unsigned char& b );

			/**
			 * @brief Convert a colorARGB to r,g,b components
			 *
			 * @param c The color to convert
			 * @param r (out) the red component (0.0 - 1.0)
			 * @param g (out) the green component (0.0 - 1.0)
			 * @param b (out) the blue component (0.0 - 1.0)
			 */
			inline static void rgb( colorARGB c, double& r, double& g, double& b );

		};

	} // display
} // derive