// Derive
#include "../DisplayObject.h"
#include "derive/geom/Bounds.h"

// Skia
#include "core/SkScalar.h"

// Other
#include <algorithm>
#include <iostream>

using namespace derive::geom;

namespace derive {
	namespace display {
		DisplayObjectProps::~DisplayObjectProps() { }

		bool DisplayObjectProps::copy( DisplayObjectProps* from ) {
			bool changed = false;
			changed |= ( x != from->x );
			changed |= ( y != from->y );
			changed |= ( originX != from->originX );
			changed |= ( originY != from->originY );
			changed |= ( scaleX != from->scaleX );
			changed |= ( scaleY != from->scaleY );
			changed |= ( width != from->width );
			changed |= ( height != from->height );
			changed |= ( visible != from->visible );
			changed |= ( rotation != from->rotation );
			changed |= ( alpha != from->alpha );
			x = from->x;
			y = from->y;
			originX = from->originX;
			originY = from->originY;
			scaleX = from->scaleX;
			scaleY = from->scaleY;
			width = from->width;
			height = from->height;
			rotation = from->rotation;
			visible = from->visible;
			alpha = from->alpha;
			return changed;
		}

		DisplayObject::DisplayObject() {
			#ifdef DERIVE_SCRIPT
			// Get JS object ID of this object

			#endif
			_state = new DisplayObjectProps();
			_grid = new Grid();
			_cursor = new Point();
			_bounds = new Bounds();
			_transform = new SkMatrix();
		}

		DisplayObject::~DisplayObject() {
			removeAllChildren();
			delete _state;
			delete _grid;
			delete _cursor;
			delete _bounds;
			delete _transform;
		}

		Bounds* DisplayObject::bounds() {
			// Update the bounds and return it
			_bounds->set( this->x, this->y, this->width, this->height );
			return _bounds;
		}

		DisplayObject* DisplayObject::parent() {
			return _parent;
		}

		DisplayObject* DisplayObject::stage() {
			return _stage;
		}

		void DisplayObject::stage( DisplayObject* stage ) {
			_stage = stage;
			for ( auto child : _children ) child->stage( stage );
		}

		DisplayObject* DisplayObject::addChild( DisplayObject* child ) {
			_children.push_back( child );
			child->_added( this );
			return child;
		}

		DisplayObject* DisplayObject::addChildAt( DisplayObject* child, int index ) {
			if ( index <= 0 ) _children.insert( _children.begin(), child );
			else if ( index >= _children.size() ) _children.push_back( child );
			else _children.insert( _children.begin() + index, child );
			child->_added( this );
			return child;
		}

		DisplayObject* DisplayObject::removeChild( DisplayObject* child ) {
			const auto it = std::remove( _children.begin(), _children.end(), child );
			if ( it == _children.end() ) throw out_of_range( "Child not found" );
			_children.erase( it, _children.end() );
			child->_removed();
			return child;
		}

		DisplayObject* DisplayObject::removeChildAt( int index ) {
			DisplayObject* child = childAt( index );
			_children.erase( _children.begin() + index );
			child->_removed();
			return child;
		}

		void DisplayObject::removeAllChildren() {
			_children.clear();
		}

		int DisplayObject::numChildren() {
			return _children.size();
		}

		DisplayObject* DisplayObject::childAt( int index ) {
			if ( index < 0 ) throw out_of_range( "Child index out of range" );
			if ( index >= _children.size() ) throw out_of_range( "Child index out of range" );
			return _children.at( index );
		}

		int DisplayObject::indexOfChild( DisplayObject* child ) {
			auto it = find( _children.begin(), _children.end(), child );
			if ( it == _children.end() ) return -1;
			return it - _children.begin();
		}

		bool DisplayObject::hasChild( DisplayObject* child ) {
			return indexOfChild( child ) >= 0;
		}

		DisplayObject* DisplayObject::first() {
			if ( _children.size() == 0 ) throw out_of_range( "No children" );
			return childAt( 0 );
		}

		DisplayObject* DisplayObject::last() {
			if ( _children.size() == 0 ) throw out_of_range( "No children" );
			return childAt( _children.size() - 1 );
		}

		DisplayObject* DisplayObject::next() {
			if ( !_parent ) throw logic_error( "Parent not set" );
			return _parent->childAt( _parent->indexOfChild( this ) + 1 );
		}

		DisplayObject* DisplayObject::prev() {
			if ( !_parent ) throw logic_error( "Parent not set" );
			return _parent->childAt( _parent->indexOfChild( this ) - 1 );
		}

		DisplayObject* DisplayObject::addBefore( DisplayObject* sibling ) {
			if ( !_parent ) throw logic_error( "Parent not set" );
			_parent->addChildAt( sibling, _parent->indexOfChild( this ) );
			return sibling;
		}

		DisplayObject* DisplayObject::addAfter( DisplayObject* sibling ) {
			if ( !_parent ) throw logic_error( "Parent not set" );
			_parent->addChildAt( sibling, _parent->indexOfChild( this ) + 1 );
			return sibling;
		}

		DisplayObject* DisplayObject::remove() {
			if ( !_parent ) throw logic_error( "Parent not set" );
			_parent->removeChild( this );
			return this;
		}

		void DisplayObject::_removed() {
			_parent = nullptr;
			stage( nullptr );
			_transform->setIdentity();
			_cursor->clear();
		}

		void DisplayObject::_added( DisplayObject* parent ) {
			_parent = parent;
			stage( _parent->stage() );
		}

		void DisplayObject::cursor( double x, double y ) {
			_cursor->set( x, y );
			_cursor->rotate( rotation, originX, originY );
			_cursor->subtract( x, y );
			// Step children
			for ( auto& child : _children ) {
				child->cursor( _cursor->x(), _cursor->y() );
			}
		}

		Point* DisplayObject::cursor() {
			return _cursor;
		}

		Grid* DisplayObject::snap() {
			return _grid;
		}

		void DisplayObject::fit( Bounds* bounds, int fitMode, int alignMode ) {
			scaleX = bounds->width() / width;
			scaleY = bounds->height() / height;

			switch ( fitMode ) {
				case FitMode::Contain: {
					if ( scaleX > scaleY ) scaleY = scaleX;
					else scaleX = scaleY;
					break;
				}
				case FitMode::Cover: {
					if ( scaleX < scaleY ) scaleY = scaleX;
					else scaleX = scaleY;
					break;
				}
				case FitMode::Width: {
					scaleY = scaleX;
					break;
				}
				case FitMode::Height: {
					scaleX = scaleY;
					break;
				}
				case FitMode::Grow: {
					if ( scaleX > scaleY ) scaleY = scaleX;
					else scaleX = scaleY;
					if ( scaleX < 1.0 ) {
						scaleX = 1.0;
						scaleY = 1.0;
					}
					break;
				}
				case FitMode::Shrink: {
					if ( scaleX > scaleY ) scaleY = scaleX;
					else scaleX = scaleY;
					if ( scaleX > 1.0 ) {
						scaleX = 1.0;
						scaleY = 1.0;
					}
					break;
				}
			}

			double w = width * scaleX;
			double h = height * scaleY;
			// Position horizontally
			if ( alignMode == 0 || ( alignMode & AlignMode::Left && alignMode & AlignMode::Right ) ) {
				x = ( bounds->width() - w ) / 2;
			}
			else if ( alignMode & AlignMode::Left ) {
				x = 0;
			}
			else if ( alignMode & AlignMode::Right ) {
				x = bounds->width() - w;
			}
			// Position vertically
			if ( alignMode == 0 || ( alignMode & AlignMode::Top && alignMode & AlignMode::Bottom ) ) {
				y = ( bounds->height() - h ) / 2;
			}
			else if ( alignMode & AlignMode::Top ) {
				y = 0;
			}
			else if ( alignMode & AlignMode::Bottom ) {
				y = bounds->height() - h;
			}
		}

		void DisplayObject::localToGlobal( Point* p ) {

		}

		void DisplayObject::globalToLocal( Point* p ) {

		}

		void DisplayObject::preUpdate( double dt ) {
			#ifdef DERIVE_SCRIPT
			// Call JS update

			#endif
		}

		void DisplayObject::postUpdate( double dt ) {
			// Step children
			for ( auto child : _children ) {
				child->preUpdate( dt );
				child->update( dt );
				child->postUpdate( dt );
			}
		}

		void DisplayObject::preRender( SkSurface* surface, SkMatrix* transform, bool forceTransformUpdate, double dt ) {
			// XXX: Get dirty rect from old state before copy
			bool changed = _state->copy( this );
			if ( changed || forceTransformUpdate ) {
				_dirty = true;

				_transform->setIdentity();
				_transform = &_transform->postConcat( *transform );

				double ox = originX * scaleX;
				double oy = originY * scaleY;
				_transform = &_transform->preConcat( SkMatrix::Translate( x - ox, y - oy ) );
				_transform = &_transform->preConcat( SkMatrix::RotateDeg( rotation, SkPoint::Make( ox, oy ) ) );
				_transform = &_transform->preConcat( SkMatrix::Scale( scaleX, scaleY ) );
			}
		}

		void DisplayObject::postRender( SkSurface* surface, SkMatrix* transform, double dt ) {
			// Step children
			for ( auto child : _children ) {
				if ( !child->visible ) continue;
				child->preRender( surface, _transform, _dirty, dt );
				child->render( surface, dt );
				child->postRender( surface, _transform, dt );
			}

			_dirty = false;
		}



	} // display
} // derive