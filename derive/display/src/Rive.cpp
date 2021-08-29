// Derive
#include "../Rive.h"

// Rive
#include "rive/core/binary_reader.hpp"
#include "rive/file.hpp"
#include "skia_renderer.hpp"

// Other
#include <iostream>

using namespace rive;

namespace derive {
	namespace display {

		Rive::Rive() { }

		Rive::Rive( string filename ) {
			load( filename );
		}

		Rive::~Rive() {
			if ( animation ) delete animation;
			if ( artboard ) delete artboard;
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
			File* file = nullptr;
			auto result = File::import( reader, &file );
			if ( result != ImportResult::success ) {
				fprintf( stderr, "failed to import file\n" );
				return;
			}
			artboard = file->artboard();
			width = artboard->width();
			height = artboard->height();
			artboard->advance( 0.0f );

			play();
		}

		bool Rive::loaded() {
			return !!artboard;
		}

		void Rive::play( int index ) {
			if ( animation ) delete animation;
			if ( index > artboard->animationCount() ) index = artboard->animationCount() - 1;
			if ( index < 0 ) index = 0;

			animation = new LinearAnimationInstance( artboard->animation( index ) );
		}

		void Rive::update( double dt ) {
			if ( artboard ) {
				if ( animation ) {
					animation->advance( dt );
					animation->apply( artboard );
				}
				artboard->advance( dt );
			}
			DisplayObject::update( dt );
		}

		void Rive::render( SkSurface* surface, double dt ) {
			if ( artboard ) {
				SkiaRenderer renderer( surface->getCanvas() );
				renderer.save();
				renderer.transform( _transform );
				artboard->draw( &renderer );
				renderer.restore();
			}
			DisplayObject::render( surface, dt );
		}

	} // display
} // derive