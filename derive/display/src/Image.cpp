// Derive
#include "../Image.h"

// Skia
#include "codec/SkCodec.h"

namespace derive {
	namespace display {

		Image::Image() { }

		Image::Image( string filename ) {
			load( filename );
		}

		Image::~Image() {
			if ( bitmap ) delete bitmap;
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

			bitmap = new SkBitmap();
			const SkImageInfo info = codec->getInfo();

			bitmap->allocPixels( info );
			codec->getPixels( info, bitmap->getPixels(), bitmap->rowBytes() );
			_width = info.width();
			_height = info.height();
		}

		bool Image::loaded() {
			return ( bitmap != NULL );
		}

		int Image::width() {
			return _width;
		}

		int Image::height() {
			return _height;
		}

		unsigned char* Image::pixelData() {
			return nullptr;
		}

		colorARGB Image::getPixel( int x, int y ) {
			if ( !bitmap ) return 0;
			return bitmap->getColor( x, y );
		}

		void Image::setPixel( int x, int y, colorARGB c ) { }

		void Image::render( SkSurface* surface, double dt ) {

			surface->writePixels( *bitmap, (int)( x - originX ), (int)( y - originY ) );

			return;
		}

	} // display
} // derive