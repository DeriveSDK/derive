// Derive
#include "../Grid.h"

namespace derive {
	namespace geom {

		Grid::Grid( double width, double height ) {
			_cell = new Point( width, height );
		}

		Grid::~Grid() {
			delete _cell;
			delete _origin;
			delete _limit;
		}

		void Grid::snap( Point* p ) {
			double x = p->x();
			double y = p->y();
			if ( _origin ) {
				if ( x < _origin->x() ) x = _origin->x();
				if ( y < _origin->y() ) y = _origin->y();
			}
			if ( _limit ) {
				if ( x > _limit->x() ) x = _limit->x();
				if ( y > _limit->y() ) y = _limit->y();
			}
			p->x( floor( x / _cell->x() ) * _cell->x() );
			p->y( floor( y / _cell->y() ) * _cell->y() );
		}

		void Grid::cell( Point* p ) {
			if ( p ) _cell->copy( p );
			else _cell->clear();
		}

		Point* Grid::cell() {
			return _cell->clone();
		}

		void Grid::origin( Point* p ) {
			if ( p ) {
				if ( _origin ) _origin->copy( p );
				else _origin = new Point( p );

				if ( _limit ) {
					if ( _limit->x() < _origin->x() ) {
						auto t = _limit->x();
						_limit->x( _origin->x() );
						_origin->x( t );
					}
					if ( _limit->y() < _origin->y() ) {
						auto t = _limit->y();
						_limit->y( _origin->y() );
						_origin->y( t );
					}
				}
			}
			else {
				delete _origin;
				_origin = nullptr;
			}
		}

		Point* Grid::origin() {
			if ( !_origin ) return nullptr;
			return _origin->clone();
		}

		void Grid::limit( Point* p ) {
			if ( p ) {
				if ( _limit ) _limit->copy( p );
				else _limit = new Point( p );

				if ( _origin ) {
					if ( _limit->x() < _origin->x() ) {
						auto t = _limit->x();
						_limit->x( _origin->x() );
						_origin->x( t );
					}
					if ( _limit->y() < _origin->y() ) {
						auto t = _limit->y();
						_limit->y( _origin->y() );
						_origin->y( t );
					}
				}
			}
			else {
				delete _limit;
				_limit = nullptr;
			}
		}

		Point* Grid::limit() {
			if ( !_limit ) return nullptr;
			return _limit->clone();
		}

		void Grid::clear() {
			_cell->clear();
			delete _limit;
			_limit = nullptr;
			delete _origin;
			_origin = nullptr;
		}

		void Grid::copy( Grid* from ) {
			clear();
			_cell->copy( from->cell() );
			if ( from->origin() ) _origin = new Point( from->origin() );
			if ( from->limit() ) _limit = new Point( from->limit() );
		}

	} // geom
} // derive