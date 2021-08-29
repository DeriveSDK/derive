// Derive
#include "../Point.h"

// Other
#include <cmath>

namespace derive {
	namespace geom {

		Point::Point( double x, double y ) {
			set( x, y );
		}
		Point::Point( Point* p ) {
			set( p );
		}
		Point::~Point() { }

		double Point::x() const { return _x; }
		void Point::x( double x ) {
			_x = move( x );
		}

		double Point::y() const { return _y; }
		void Point::y( double y ) {
			_y = move( y );
		}

		void Point::set( double x, double y ) {
			_x = x;
			_y = y;
		}

		void Point::set( Point* p ) {
			_x = p->_x;
			_y = p->_y;
		}

		void Point::clear() {
			_x = 0;
			_y = 0;
		}

		bool Point::equals( double x, double y ) {
			return ( x == _x ) && ( y == _y );
		}

		bool Point::equals( Point* p ) {
			return ( p->_x == _x ) && ( p->_y == _y );
		}

		void Point::translate( Point* p ) {
			_x += p->_x;
			_y += p->_y;
		}

		void Point::translate( double x, double y ) {
			_x += x;
			_y += y;
		}

		void Point::add( Point* p ) {
			_x += p->_x;
			_y += p->_y;
		}

		void Point::add( double x, double y ) {
			_x += x;
			_y += y;
		}

		void Point::subtract( Point* p ) {
			_x -= p->_x;
			_y -= p->_y;
		}

		void Point::subtract( double x, double y ) {
			_x -= x;
			_y -= y;
		}

		void Point::rotate( double angle ) {
			double s = sin( angle );
			double c = cos( angle );

			double x = _x * c - _y * s;
			double y = _x * s + _y * c;

			_x = x;
			_y = y;
		}

		void Point::rotate( double angle, Point* p ) {
			subtract( p );
			rotate( angle );
			add( p );
		}

		void Point::rotate( double angle, double x, double y ) {
			subtract( x, y );
			rotate( angle );
			add( x, y );
		}

		void Point::copy( Point* from ) {
			_x = from->_x;
			_y = from->_y;
		}

		Point* Point::clone() {
			return new Point( _x, _y );
		}

	} // geom
} // derive