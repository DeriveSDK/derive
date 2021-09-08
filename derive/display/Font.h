#pragma once

// Derive
#include "EmbeddedAssets.h"
#include "derive/assets/EmbeddedAsset.h"
// Skia
#include "core/SkTypeface.h"
// Other
#include <string>
#include <map>

using namespace std;

namespace derive {
	namespace display {

		/**
		 * @brief A font class
		 * 
		 * Recommend usage:
		 * 
		 * // At some point before you need to use font, load the fonts into the library
		 * Fonts::Load("assets/fonts/OpenSans.ttf");
		 * Fonts::Load("assets/fonts/ComicSans.ttf", "Comic-Sans");
		 * 
		 * // When you require a font, grab it from the library by name
		 * Font* comic = Fonts::Library("Comic-Sans");
		 * 
		 * // Most objects that use fonts (e.g. Text) use the library and just require the name
		 * text->font( "Comic-Sans" );
		 * 
		 * Alternative usage:
		 * 
		 * // Load a font and use immediatly
		 * Font* comic = new Font("assets/fonts/OpenSans.ttf");
		 * 
		 * // Add it to the library if you want to use it later
		 * Font::Library( comic );
		 * 
		 * Note: Library fonts are freed automatically when Player exits.
		 */
		class Font {
		protected:
			static map<string,Font*> _library;
			virtual void _loadFromAsset( EmbeddedAssetData asset );
		public:
			sk_sp<SkTypeface> typeface = nullptr;
			
			/**
			 * @brief Construct a new empty Font object
			 * 
			 */
			Font();

			/**
			 * @brief Load a font
			 * If no name is provided, the name will be set from the font file
			 * @param filename The filename in the assets
			 * @param name (optional) The name/identifier to give the font. If not set uses the name from the font file
			 */
			Font( string filename, string name = "" );

			/**
			 * @brief Destroy the Font object
			 */
			virtual ~Font();

			/**
			 * @brief The font name for referencing it from the library
			 * If this is not empty, it will be set from the loaded font
			 */
			string name = "";

			/**
			 * @brief Load the font
			 * This does not add the font to the library for later retrieval.
			 * @see Load
			 * @param filepath The filepath within the assets
			 * @param name (optional) The name/identifier to give the font. If not set uses the name from the font file
			 * @return true The font was loaded
			 * @return false The font was not loaded
			 */
			virtual bool load( string filename, string name = "" );
			
			/**
			 * @brief Check if a font is loaded
			 * 
			 * @return true The font is loaded
			 * @return false The font is not loaded
			 */
			virtual bool loaded();

			/**
			 * @brief Load a font into the library
			 * 
			 * @param filepath The filepath within the assets
			 * @param name (optional) The name/identifier to give the font. If not set uses the name from the font file
			 * @return true The font was loaded
			 * @return false The font was not loaded
			 */
			static bool Load( string filename, string name = "" );

			/**
			 * @brief Grab a font from the library
			 * 
			 * @param name The name/identifier of the font in the library 
			 * @return Font* The font, or nullptr if it can not be found
			 */
			static Font* Library( string name );

			/**
			 * @brief Add a font to the library
			 * The font must have a name set of it will not be added
			 * @param font The font to add to the library
			 * @return true The font was added (or already existed)
			 * @return false The font was not added. Check the name is set
			 */
			static bool Library( Font* font );

			/**
			 * @brief Remove a font from the library
			 * Removes the font but does not free it. Make sure to call delete on the font manually
			 * @param font The font to unload
			 */
			static void Unload( Font* font );

			/**
			 * @brief Remove a font from the library by name
			 * Removes the font and also frees it from memory
			 * @param name The font to unload
			 */
			static void Unload( string name );

			/**
			 * @brief Clear all loaded fonts from the library
			 * 
			 */
			static void Destroy();

		};

	} // ns:display
} // ns:derive