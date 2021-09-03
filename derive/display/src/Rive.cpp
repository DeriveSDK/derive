// Derive
#include "../Rive.h"
#include "derive/utils/SkiaTypes.h"
// Rive
#include "rive/core/binary_reader.hpp"
#include "skia_renderer.hpp"
// Other
#include <iostream>

using namespace rive;
using namespace derive::utils;

namespace derive {
	namespace display {

		Rive::Rive() {
			_renderer = new RiveSkiaRenderer( nullptr );
		}

		Rive::Rive( string filename ): Rive() {
			load( filename );
		}

		Rive::~Rive() {
			delete _renderer;
			delete _animation;
			delete _file;
		}

		bool Rive::load( string filename ) {
			cout << "new Rive " << filename << endl;
			EmbeddedAssets assetLib;
			auto it = assetLib.items.find( filename );
			if ( it != assetLib.items.end() ) {
				loadFromAsset( it->second );
			}
			return loaded();
		}

		void Rive::loadFromAsset( EmbeddedAssetData asset ) {
			cout << "  load from asset" << endl;
			auto reader = BinaryReader( (uint8_t*)asset.data, asset.length );
			delete _file;
			_file = nullptr;
			auto result = File::import( reader, &_file );
			if ( result != ImportResult::success ) {
				fprintf( stderr, "failed to import file\n" );
				return;
			}
			_artboard = _file->artboard();
			width = _artboard->width();
			height = _artboard->height();
			_artboard->advance( 0.0f );

			play();
		}

		bool Rive::loaded() {
			return !!_artboard;
		}

		void Rive::play( int index ) {
			delete _animation;
			if ( index > _artboard->animationCount() ) index = _artboard->animationCount() - 1;
			if ( index < 0 ) index = 0;

			_animation = new LinearAnimationInstance( _artboard->animation( index ) );
		}

		void Rive::update( double dt ) {
			if ( _artboard ) {
				if ( _animation ) {
					_animation->advance( dt );
					_animation->apply( _artboard );
				}
				_artboard->advance( dt );
			}
			DisplayObject::update( dt );
		}

		void Rive::render( SkSurface* surface, double dt ) {
			if ( _artboard ) {
				_renderer->canvas = surface->getCanvas();
				_renderer->save();
				_renderer->transform( _transform );
				_artboard->draw( _renderer );
				_renderer->restore();
			}
			DisplayObject::render( surface, dt );
		}

	} // display
} // derive