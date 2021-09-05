// Derive
#include "../Image.h"
#include "derive/utils/SkiaTypes.h"
// Skia
#include "codec/SkCodec.h"
#include "core/SkCanvas.h"
#include "core/SkBitmap.h"
#include "core/SkImageGenerator.h"

using namespace derive::utils;

namespace derive {
	namespace display {

		Image::Image() {
			_canvasMatrix = new SkMatrix();
		}

		Image::Image( string filename ):Image() {
			load( filename );
		}

		Image::~Image() {
			delete _canvasMatrix;
			delete _bitmap;
		}

		bool Image::load( string filename ) {
			EmbeddedAssets assetLib;
			auto it = assetLib.items.find( filename );
			if ( it != assetLib.items.end() ) {
				loadFromAsset( it->second );
			}
			return loaded();
		}

		void Image::loadFromAsset( EmbeddedAssetData asset ) {
			std::unique_ptr<SkCodec> codec( SkCodec::MakeFromData( SkData::MakeWithoutCopy( asset.data, asset.length ) ) );
			if ( !codec ) return;

			const SkImageInfo info = codec->getInfo();
			_bitmap = new SkBitmap();
			_bitmap->allocPixels( info );
			codec->getPixels( info, _bitmap->getPixels(), _bitmap->rowBytes() );
			_image = SkImage::MakeFromBitmap( *_bitmap );

			_width = info.width();
			_height = info.height();
		}

		bool Image::loaded() {
			return ( _image != NULL );
		}

		int Image::width() {
			return _width;
		}

		int Image::height() {
			return _height;
		}

		void Image::render( SkSurface* surface, double dt ) {
			SkCanvas* canvas = surface->getCanvas();
			canvas->save();
			SkiaTypes::convert( _transform, _canvasMatrix );
			canvas->concat( *_canvasMatrix );
			canvas->drawImage( _image, 0, 0 );
			canvas->restore();
		}

	} // display
} // derive