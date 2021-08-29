// Derive
#include "../Bounds.h"

namespace derive {
	namespace geom {

		void Bounds::recalc() {
			_width = _x2 - _x1;
			_height = _y2 - _y1;
		}
		void Bounds::recalc2() {
			_x2 = _x1 + _width;
			_y2 = _y1 + _height;
		}

		Bounds::Bounds( double x, double y, double width, double height ) {
			set( x, y, width, height );
		}
		Bounds::~Bounds() { }

		double Bounds::x() const { return _x1; }
		void Bounds::x( double x ) {
			_x1 = move( x );
			recalc2();
		}

		double Bounds::y() const { return _y1; }
		void Bounds::y( double y ) {
			_y1 = move( y );
			recalc2();
		}

		double Bounds::x2() const { return _x2; }
		void Bounds::x2( double x ) {
			_x2 = move( x );
			recalc();
		}

		double Bounds::y2() const { return _y2; }
		void Bounds::y2( double y ) {
			_y2 = move( y );
			recalc();
		}

		double Bounds::width() const { return _width; }
		void Bounds::width( double w ) {
			if ( w < 0 ) {
				_width = -move( w );
				_x1 -= _width;
			}
			else {
				_width = move( w );
			}
			recalc2();
		}

		double Bounds::height() const { return _height; }
		void Bounds::height( double h ) {
			if ( h < 0 ) {
				_height = -move( h );
				_y1 -= _height;
			}
			else {
				_height = move( h );
			}
			recalc2();
		}

		bool Bounds::empty() {
			return ( _width <= 0 ) || ( _height <= 0 );
		}

		void Bounds::clear() {
			_x1 = 0;
			_y1 = 0;
			_x2 = 0;
			_y2 = 0;
			_width = 0;
			_height = 0;
		}

		void Bounds::setPos( Point* p ) {
			_x1 = p->x();
			_y1 = p->y();
			recalc2();
		}
		void Bounds::setPos( double x, double y ) {
			_x1 = x;
			_y1 = y;
			recalc2();
		}
		void Bounds::setPos( double x, double y, double x2, double y2 ) {
			_x1 = x;
			_y1 = y;
			_x2 = x2;
			_y2 = y2;
			recalc();
		}

		void Bounds::setPos2( Point* p ) {
			_x2 = p->x();
			_y2 = p->y();
			recalc();
		}
		void Bounds::setPos2( double x, double y ) {
			_x2 = x;
			_y2 = y;
			recalc();
		}

		void Bounds::set( Point* p, double width, double height ) {
			set( p->x(), p->y(), width, height );
		}
		void Bounds::set( double x, double y, double width, double height ) {
			_x1 = x;
			_y1 = y;
			if ( width < 0 ) {
				_width = -width;
				_x1 -= _width;
			}
			else {
				_width = width;
			}
			if ( height < 0 ) {
				_height = -height;
				_y1 -= _height;
			}
			else {
				_height = height;
			}
			recalc2();
		}

		bool Bounds::contains( Bounds* bounds ) {
			return ( bounds->_x1 >= _x1 ) && ( bounds->_x2 <= _x2 ) && ( bounds->_y1 >= _y1 ) && ( bounds->_y2 <= _y2 );
		}

		bool Bounds::contains( Point* p ) {
			return ( p->x() >= _x1 ) && ( p->x() <= _x2 ) && ( p->y() >= _y1 ) && ( p->y() <= _y2 );
		}

		bool Bounds::contains( double x, double y ) {
			return ( x >= _x1 ) && ( x <= _x2 ) && ( y >= _y1 ) && ( y <= _y2 );
		}

		bool Bounds::containsX( double x ) {
			return ( x >= _x1 ) && ( x <= _x2 );
		}

		bool Bounds::containsY( double y ) {
			return ( y >= _y1 ) && ( y <= _y2 );
		}

		bool Bounds::overlaps( Bounds* bounds ) {
			if ( empty() || bounds->empty() ) return false;
			if ( bounds->_x2 < _x1 ) return false;
			if ( bounds->_x1 > _x2 ) return false;
			if ( bounds->_y2 < _y1 ) return false;
			if ( bounds->_y1 > _y2 ) return false;
			return true;
		}

		void Bounds::translate( Point* p ) {
			_x1 += p->x();
			_y1 += p->y();
			recalc2();
		}

		void Bounds::translate( double x, double y ) {
			_x1 += x;
			_y1 += y;
			recalc2();
		}

		void Bounds::grow( Bounds* bounds ) {

			_x1 = min( _x1, bounds->_x1 );
			_y1 = min( _y1, bounds->_y1 );
			_x2 = min( _x2, bounds->_x2 );
			_y2 = min( _y2, bounds->_y2 );
			recalc();
		}

		void Bounds::clip( Bounds* bounds ) {
			if ( _x1 < bounds->_x1 ) _x1 = bounds->_x1;
			if ( _x2 > bounds->_x2 ) _x2 = bounds->_x2;
			if ( _y1 < bounds->_y1 ) _y1 = bounds->_y1;
			if ( _y2 > bounds->_y2 ) _y2 = bounds->_y2;
			if ( _x1 > _x2 ) _x2 = _x1;
			if ( _y1 > _y2 ) _y2 = _y1;
			recalc();
		}

		void Bounds::copy( Bounds* from ) {
			_x1 = from->_x1;
			_y1 = from->_y1;
			_x2 = from->_x2;
			_y2 = from->_y2;
			_width = from->_width;
			_height = from->_height;
		}

		Bounds* Bounds::clone() {
			return new Bounds( _x1, _y1, _width, _height );
		}

	} // geom
} // derive