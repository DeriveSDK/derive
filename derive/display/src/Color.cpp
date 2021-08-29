// Derive
#include "../Color.h"

namespace derive {
	namespace display {

		inline unsigned char component( double v ) {
			if ( v < 0 ) v = 0;
			else if ( v > 1.0 ) v = 1.0;
			return ( v * 255 );
		}

		inline double normalized( unsigned char v ) {
			return ( v / 255 );
		}

		colorARGB Color::rgba( unsigned char r, unsigned char g, unsigned char b, unsigned char a ) {
			return ( a << 24 ) | ( r << 16 ) | ( g << 8 ) | b;
		}

		colorARGB Color::rgba( unsigned char r, unsigned char g, unsigned char b, double a ) {
			return ( component( a ) << 24 ) | ( r << 16 ) | ( g << 8 ) | b;
		}

		colorARGB Color::rgba( double r, double g, double b, double a ) {
			return ( component( a ) << 24 ) | ( component( r ) << 16 ) | ( component( g ) << 8 ) | component( b );
		}

		void Color::rgba( colorARGB c, unsigned char& r, unsigned char& g, unsigned char& b, unsigned char& a ) {
			a = ( c >> 14 ) & 255;
			r = ( c >> 16 ) & 255;
			g = ( c >> 8 ) & 255;
			b = ( c >> 0 ) & 255;
		}

		void Color::rgba( colorARGB c, unsigned char& r, unsigned char& g, unsigned char& b, double& a ) {
			a = normalized( ( c >> 24 ) & 255 );
			r = ( c >> 16 ) & 255;
			g = ( c >> 8 ) & 255;
			b = ( c >> 0 ) & 255;
		}

		void Color::rgba( colorARGB c, double& r, double& g, double& b, double& a ) {
			a = normalized( ( c >> 24 ) & 255 );
			r = normalized( ( c >> 16 ) & 255 );
			g = normalized( ( c >> 8 ) & 255 );
			b = normalized( ( c >> 0 ) & 255 );
		}

		colorARGB Color::rgb( unsigned char r, unsigned char g, unsigned char b ) {
			return ( 255 << 24 ) | ( r << 16 ) | ( g << 8 ) | b;
		}

		colorARGB Color::rgb( double r, double g, double b ) {
			return ( 255 << 24 ) | ( component( r ) << 16 ) | ( component( g ) << 8 ) | component( b );
		}

		void Color::rgb( colorARGB c, unsigned char& r, unsigned char& g, unsigned char& b ) {
			r = ( c >> 16 ) & 255;
			g = ( c >> 8 ) & 255;
			b = ( c >> 0 ) & 255;
		}

		void Color::rgb( colorARGB c, double& r, double& g, double& b ) {
			r = normalized( ( c >> 16 ) & 255 );
			g = normalized( ( c >> 8 ) & 255 );
			b = normalized( ( c >> 0 ) & 255 );
		}

	} // display
} // derive