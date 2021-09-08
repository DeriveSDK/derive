// Derive
#include "../Font.h"
// Skia
#include "core/SkData.h"
// Other
#include <iostream>

namespace derive {
	namespace display {

		Font::Font(){}

		Font::Font( string filename, string name ) {
			load( filename, name );
		}

		Font::~Font(){
			// XXX: Delete typeface?
		}

		bool Font::load( string filename, string name ) {
			EmbeddedAssets assetLib;
			auto it = assetLib.items.find( filename );
			if ( it != assetLib.items.end() ) {
				_loadFromAsset( it->second );
			}
			else {
				cout << filename << " not found in assets" << endl;
			}
			if (name != "") this->name = name;
			return loaded();
		}

		void Font::_loadFromAsset( EmbeddedAssetData asset ) {
			sk_sp<SkData> data = SkData::MakeWithoutCopy( asset.data, asset.length );
			typeface = SkTypeface::MakeFromData( data );
			if (typeface){
				SkString* s;
				typeface->getFamilyName(s);
				name = s->c_str();
				//delete s;
			}
		}

		bool Font::loaded() {
			return typeface != nullptr;
		}

		// ### STATIC

		map<string,Font*> Font::_library;

		bool Font::Load( string filename, string name ) {
			Font* font = new Font( filename, name );
			if (font->loaded()) {
				Library( font );
				return true;
			}
			else {
				delete font;
			}
			return false;
		}

		bool Font::Library( Font* font ) {
			// No name set
			if (font->name == "") return false;
			// Already in library
			for (auto pair : _library) {
				if (pair.second == font) {
					return true;
				}
			}
			// Add to library
			_library.insert( std::pair<string,Font*>( font->name, font ));
			return true;
		}

		Font* Font::Library( string name ) {
			if (_library.count(name) == 0) return nullptr;
			return _library[name];
		}

		void Font::Destroy() {
			for (auto pair : _library) delete pair.second;
			_library.clear();
		}

		void Font::Unload( string name ) {
			if (_library.count(name) > 0) {
				delete _library[name];
				_library.erase(name);
			}
		}

		void Font::Unload( Font* font ) {
			for (auto pair : _library) {
				if (pair.second == font) {
					_library.erase( pair.first );
					return;
				}
			}
		}

	} // display
} // derive