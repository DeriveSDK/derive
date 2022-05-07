// Derive
#include "../Image.h"
#include "derive/Player.h"
#include "derive/utils/TvgTypes.h"

using namespace derive::utils;

namespace derive {
	namespace display {

		Image::Image() {}

		Image::Image( string filename ):Image() {
			load( filename );
		}

		bool Image::load( string filename ) {
			_scene->clear();
			_width = 0;
			_height = 0;
			_pictureRef = nullptr;
			EmbeddedAssets assetLib;
			auto it = assetLib.items.find( filename );
			if ( it != assetLib.items.end() ) {
				loadFromAsset( it->second );
			}
			return loaded();
		}

		void Image::loadFromAsset( EmbeddedAssetData asset ) {
			_picture = tvg::Picture::gen();
			if (_picture->load((const char*)asset.data, asset.length) != tvg::Result::Success) return;

			uint32_t w;
			uint32_t h;
			_picture->data(&w, &h);
			_width = w;
			_height = h;
			_pictureRef = _picture.get();
			_scene->push(std::move(_picture));
		}

		bool Image::loaded() {
			return _width && _height;
		}

		int Image::width() {
			return _width;
		}

		int Image::height() {
			return _height;
		}

		void Image::render(Context* context, double dt ) {
			if (!_pictureRef) return;
			tvg::Matrix m = { 1, 0, 0, 0, 1, 0, 0, 0, 1 };
			TvgTypes::convert(_transform, &m);
			_pictureRef->transform(m);
		}

	} // display
} // derive