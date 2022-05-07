// Derive
#include "../Rive.h"
#include "derive/Player.h"
#include "derive/utils/RiveTypes.h"
// Rive
#include "rive/core/binary_reader.hpp"

using namespace derive::render;

namespace derive {
	namespace display {

		Rive::Rive() {
			_renderer = new rive::TvgRenderer(_scene.get());
		}

		Rive::Rive( string filename ): Rive() {
			load( filename );
		}

		Rive::~Rive() {
			delete _renderer;
		}

		bool Rive::load( string filename ) {
			EmbeddedAssets assetLib;
			auto it = assetLib.items.find( filename );
			if ( it != assetLib.items.end() ) {
				loadFromAsset( it->second );
			}
			return loaded();
		}

		void Rive::loadFromAsset( EmbeddedAssetData asset ) {
			auto reader = rive::BinaryReader( (uint8_t*)asset.data, asset.length );
			_file = rive::File::import(reader);
			if (!_file) {
				fprintf( stderr, "failed to import file\n" );
				return;
			}
			_artboard = _file->artboardDefault();
			width = _artboard->width();
			height = _artboard->height();
			_artboard->advance( 0.0f );

			play();
		}

		bool Rive::loaded() {
			return !!_artboard;
		}

		void Rive::play( int index ) {
			if ( index > _artboard->animationCount() ) index = _artboard->animationCount() - 1;
			if ( index < 0 ) index = 0;

			_animation = _artboard->animationAt(index);
		}

		void Rive::update(double dt) {
			if ( _artboard ) {
				if ( _animation ) {
					_animation->advance( dt );
					_animation->apply();
				}
				_artboard->advance( dt );
			}
			DisplayObject::update( dt );
		}

		void Rive::render(Context* context, double dt) {
			_scene->clear();
			if ( _artboard ) {
				_renderer->save();
				rive::Mat2D _riveTransform;
				derive::utils::RiveTypes::convert(_transform, &_riveTransform);
				_renderer->transform(_riveTransform);
				_artboard->draw(_renderer);
				_renderer->restore();
			}
		}

	} // display
} // derive