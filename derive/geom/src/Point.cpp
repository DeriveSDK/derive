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

		void Point::set( double x, double y ) {
			this->x = x;
			this->y = y;
		}

		void Point::set( Point* p ) {
			this->x = p->x;
			this->y = p->y;
		}

		void Point::clear() {
			x = 0;
			y = 0;
		}

		bool Point::equals( double x, double y ) {
			return ( this->x == x ) && ( this->y == y );
		}

		bool Point::equals( Point* p ) {
			return ( p->x == x ) && ( p->y == y );
		}

		void Point::translate( Point* p ) {
			x += p->x;
			y += p->y;
		}

		void Point::translate( double x, double y ) {
			this->x += x;
			this->y += y;
		}

		void Point::add( Point* p ) {
			x += p->x;
			y += p->y;
		}

		void Point::add( double x, double y ) {
			this->x += x;
			this->y += y;
		}

		void Point::subtract( Point* p ) {
			x -= p->x;
			y -= p->y;
		}

		void Point::subtract( double x, double y ) {
			this->x -= x;
			this->y -= y;
		}

		void Point::rotate( double angle ) {
			double s = sin( angle );
			double c = cos( angle );

			double tx = x * c - y * s;
			double ty = x * s + y * c;

			x = tx;
			y = ty;
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
			x = from->x;
			y = from->y;
		}

		Point* Point::clone() {
			return new Point( x, y );
		}

	} // geom
} // derive