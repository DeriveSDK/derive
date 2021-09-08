#pragma once

// Derive
#include "derive/geom/Bounds.h"
#include "derive/display/Color.h"
#include "derive/display/DisplayObject.h"
#include "derive/display/Font.h"
// Skia
#include "core/SkMatrix.h"
// Other
#include <string>
#include <list>

using namespace std;

namespace derive {
	namespace display {

		class Text;

		class TextAlign {
		public:
			static const int Left = 0;
			static const int Right = 1;
			static const int Center = 2;
		};

		/**
		 * @brief Stores text properties for a span of text
		 * 
		 */
		class TextProps {
		protected:
			friend class Text;
			int _pos = 0;

			double _size = 10;
			bool _size_changed = false;
			bool _bold = false;
			bool _bold_changed = false;
			bool _italic = false;
			bool _italic_changed = false;
			bool _underline = false;
			bool _underline_changed = false;
			bool _strike = false;
			bool _strike_changed = false;
			bool _sub = false;
			bool _sub_changed = false;
			bool _sup = false;
			bool _sup_changed = false;
			int _align = 0;
			bool _align_changed = false;
			colorARGB _color = 0xff000000;
			bool _color_changed = false;
			Font* _font;
			bool _font_changed = false;
		public:
			virtual ~TextProps(){}

			/**
			 * @brief Set the font size
			 * @param s The font size
			 */
			void size( double s );

			/**
			 * @brief Get the font size
			 * @return double The font size
			 */
			double size();

			/**
			 * @brief Set the bold state
			 * @param s The bold state
			 */
			void bold( bool s );

			/**
			 * @brief Get the bold state
			 * @return bool The bold state
			 */
			bool bold();

			/**
			 * @brief Set the italic state
			 * @param s The italic state
			 */
			void italic( bool s );

			/**
			 * @brief Get the italic state
			 * @return bool The italic state
			 */
			bool italic();

			/**
			 * @brief Set the underline state
			 * @param s The underline state
			 */
			void underline( bool s );

			/**
			 * @brief Get the underline state
			 * @return bool The underline state
			 */
			bool underline();

			/**
			 * @brief Set the strike-through state
			 * @param s The strike-through state
			 */
			void strike( bool s );

			/**
			 * @brief Get the strike-through state
			 * @return bool The strike-through state
			 */
			bool strike();

			/**
			 * @brief Set the super-script state
			 * @param s The super-script state
			 */
			void sup( bool s );

			/**
			 * @brief Get the super-script state
			 * @return bool The super-script state
			 */
			bool sup();

			/**
			 * @brief Set the sub-script state
			 * @param s The sub-script state
			 */
			void sub( bool s );

			/**
			 * @brief Get the sub-script state
			 * @return bool The sub-script state
			 */
			bool sub();

			/**
			 * @brief Set the alignment
			 * @param s The alignment
			 */
			void align( int alignment );

			/**
			 * @brief Get the alignment
			 * @return int The alignment
			 */
			int align();

			/**
			 * @brief Set the color
			 * @param c The color
			 */
			void color( colorARGB c );

			/**
			 * @brief Get the color
			 * @return colorARGB The color
			 */
			colorARGB color();

			/**
			 * @brief Set the font
			 * @param name The font name from the library
			 */
			void font( string name );

			/**
			 * @brief Get the font
			 * @return string The font name
			 */
			string font();

			/**
			 * @brief Mark all properties as changed
			 */
			void changed();

			/**
			 * @brief Check if another props matches this one exactly
			 * Only the changed properties are checked. To check all properties first call `changed()`.
			 * @param props The text props to compare with
			 * @return true If the changed text props match exactly
			 * @return false If the text props differ
			 */
			virtual bool equals( TextProps* props );

			/**
			 * @brief Copy changed properties from another TextProps
			 * Only the changed properties of `from` are copied. To copy all properties first call `changed()` on `from`.
			 * @param from The props to copy from
			 */
			void copy( TextProps* from );

			/**
			 * @brief Copy changed properties between two TextProps if they have changed in this one

			 * @param from The props to copy from
			 * @param to The props to copy to
			 */
			void copy( TextProps* from, TextProps* to );

			/**
			 * @brief Create a clone of these props
			 * 
			 * @return TextProps* The cloned props
			 */
			TextProps* clone();

			/**
			 * @brief Log to stadout
			 * 
			 */
			void log();
		};

		/**
		 * @brief A textarea class
		 */
		class Text: public DisplayObject {
		protected:
			list<TextProps*> _spans;
			string _text;
			int _selStart = 0; 
			int _selEnd = 0; // past-the-end index
			bool _autoWidth = true;
			bool _autoHeight = true;
			SkMatrix* _canvasMatrix = nullptr;

			/**
			 * @brief Get the props at the exact position
			 * If `create` is true, will create properties at that position if they do not exist yet
			 * @param pos The position to check
			 * @param create If true, will create properties at the position if they do not exist
			 * @return TextProps* The props at the position, or nullptr
			 */
			TextProps* _propsAt( int pos, bool create = false );

			/**
			 * @brief Get the props after the specified position, or nullptr if not found
			 * 
			 * @param pos The position
			 * @return TextProps* The props after the position
			 */
			TextProps* _propsAfter( int pos );

			/**
			 * @brief Remove a specific span
			 * 
			 * @param props The span/props to remove
			 */
			void _removeSpan( TextProps* props );

		public:
			/**
			 * @brief Construct a new empty Text object
			 */
			Text();

			/**
			 * @brief Destroy the Text object
			 */
			~Text();

			/**
			 * @brief Set the full text string
			 * This will delete all spans in the text, except the first one. The selection will be set to the whole string
			 * @see paste
			 * @see append
			 * @param t The text to set
			 * @param props (optional) Properties to assign to the text
			 */
			void text( string t, TextProps* props = nullptr );

			/**
			 * @brief Return the full text string
			 * 
			 * @return string The text string
			 */
			string textAsString();

			/**
			 * @brief Retrieve the selected text string as plain text
			 */
			string selectedTextAsString();

			/**
			 * @brief Retrieve the selected text string
			 */
			Text* selectedText();

			/**
			 * @brief Make a selection
			 * The default selection is the whole text string (from = 0, to = 0)
			 * @param from The index of the first character in the selection
			 * @param to The index of the last character in the selection
			 */
			void select( int from, int to );

			/**
			 * @brief Make a selection that includes the whole text string
			 */
			void selectAll();

			/**
			 * @brief Get the text properties at the specified position in the text
			 * 
			 * @param pos The position, starting at 0
			 * @return TextProps* The text properties
			 */
			TextProps* props( int pos );

			/**
			 * @brief Bold or un-bold the selection
			 * 
			 * @param state If true, set selection to bold, otherwise remove bold
			 */
			void bold( bool state = true );

			/**
			 * @brief Italicise or un-italicise the selection
			 * 
			 * @param state If true, set selection to italic, otherwise remove italic
			 */
			void italic( bool state = true );

			/**
			 * @brief Underline or un-underline the selection
			 * 
			 * @param state If true, set selection to underline, otherwise remove underline
			 */
			void underline( bool state = true );

			/**
			 * @brief Strike-through or un-strike-through the selection
			 * 
			 * @param state If true, set selection to strike-through, otherwise remove strike-through
			 */
			void strike( bool state = true );

			/**
			 * @brief Super-script or un-Super-script the selection
			 * 
			 * @param state If true, set selection to super-script, otherwise remove super-script
			 */
			void sup( bool state = true );

			/**
			 * @brief Sub-script or un-sub-script the selection
			 * 
			 * @param state If true, set selection to sub-script, otherwise remove sub-script
			 */
			void sub( bool state = true );

			/**
			 * @brief Set the selection color
			 */
			void color( colorARGB c );

			/**
			 * @brief Set the selection font size
			 * 
			 * @param s The size
			 */
			void size( double s );

			/**
			 * @brief Align the selected text
			 * Will change the alignment of all spans covered by the selection, up until the
			 * next line break.
			 * @param alignment The alignment (TextAlign)
			 */
			void align( int alignment );

			/**
			 * @brief Set the font for the selected text
			 * The font should be loaded into the library first
			 * @see derive::display::Font
			 * @param name The name of the font in the library
			 */
			void font( string name );

			/**
			 * @brief Apply text properties to the selection
			 * 
			 * @param props The properties to apply
			 */
			void apply( TextProps* props );

			/**
			 * @brief Replace the selection with the text
			 * The selection is updated to the pasted text
			 * @param t The text to paste
			 * @param props (optional) Properties to assign to the text
			 */
			void paste( string t, TextProps* props = nullptr );

			/**
			 * @brief Replace the selection with the text
			 * The selection is updated to the pasted text
			 * @param t The text to paste
			 */
			void paste( Text* t );

			/**
			 * @brief Remove the selected text
			 * The selection is updated to the cut text position
			 */
			void cut();

			/**
			 * @brief Get the bounds of the text
			 */
			Bounds* getBounds();

			/**
			 * @brief Render the text to a surface
			 * 
			 * @param surface The surface
			 * @param dt Secodns since last call to render
			 */
			void render( SkSurface* surface, double dt );

			/**
			 * @brief Log to stadout
			 * 
			 */
			void log();
		};

	} // ns:display
} // ns:derive