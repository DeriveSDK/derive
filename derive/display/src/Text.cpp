// Derive
#include "../Text.h"
#include "derive/utils/SkiaTypes.h"
// SKia
#include "core/SkCanvas.h"
#include "core/SkPaint.h"
#include "core/SkFont.h"

using namespace derive::utils;

namespace derive {
	namespace display {

		void TextProps::size( double s ) {
			_size = s;
			_size_changed = true;
		}
		double TextProps::size() { return _size; }

		void TextProps::bold( bool s ) {
			_bold = s;
			_bold_changed = true;
		}
		bool TextProps::bold() { return _bold; }

		void TextProps::italic( bool s ) {
			_italic = s;
			_italic_changed = true;
		}
		bool TextProps::italic() { return _italic; }

		void TextProps::underline( bool s ) {
			_underline = s;
			_underline_changed = true;
		}
		bool TextProps::underline() { return _underline; }

		void TextProps::strike( bool s ) {
			_strike = s;
			_strike_changed = true;
		}
		bool TextProps::strike() { return _strike; }

		void TextProps::sup( bool s ) {
			_sup = s;
			if (s) sub( false );
			_sup_changed = true;
		}
		bool TextProps::sup() { return _sup; }

		void TextProps::sub( bool s ) {
			_sub = s;
			if (s) sup( false );
			_sub_changed = true;
		}
		bool TextProps::sub() { return _sub; }

		void TextProps::align( int alignment ) {
			_align = alignment;
			_align_changed = true;
		}
		int TextProps::align() { return _align; }

		void TextProps::color( colorARGB c ) {
			_color = c;
			_color_changed = true;
		}
		colorARGB TextProps::color() { return _color; }

		void TextProps::font( string name ) {
			_font = Font::Library(name);
			_font_changed = true;
		}
		string TextProps::font() {
			if (!_font) return "";
			return _font->name;
		}

		bool TextProps::equals( TextProps* props ) {
			return 
				(!_size_changed || _size == props->_size)
				&& (!_bold_changed || _bold == props->_bold)
				&& (!_italic_changed || _italic == props->_italic)
				&& (!_underline_changed || _underline == props->_underline)
				&& (!_strike_changed || _strike == props->_strike)
				&& (!_sub_changed || _sub == props->_sub)
				&& (!_sup_changed || _sup == props->_sup)
				&& (!_align_changed || _align == props->_align)
				&& (!_color_changed || _color == props->_color)
				&& (!_font_changed || _font == props->_font);
		}

		void TextProps::copy( TextProps* from ) {
			if (from->_size_changed) size( from->_size );
			if (from->_bold_changed) bold( from->_bold );
			if (from->_italic_changed) italic( from->_italic );
			if (from->_underline_changed) underline( from->_underline );
			if (from->_strike_changed) strike( from->_strike );
			if (from->_sub_changed) sub( from->_sub );
			if (from->_sup_changed) sup( from->_sup );
			if (from->_align_changed) align( from->_align );
			if (from->_color_changed) color( from->_color );
			if (from->_font_changed) {
				_font = from->_font;
				_font_changed = true;
			}
		}

		void TextProps::copy( TextProps* from, TextProps* to ) {
			if (_size_changed) to->size( from->_size );
			if (_bold_changed) to->bold( from->_bold );
			if (_italic_changed) to->italic( from->_italic );
			if (_underline_changed) to->underline( from->_underline );
			if (_strike_changed) to->strike( from->_strike );
			if (_sub_changed) to->sub( from->_sub );
			if (_sup_changed) to->sup( from->_sup );
			if (_align_changed) to->align( from->_align );
			if (_color_changed) to->color( from->_color );
			if (_font_changed) {
				_font = from->_font;
				_font_changed = true;
			}
		}

		TextProps* TextProps::clone() {
			TextProps* props = new TextProps();
			props->_size = this->_size;
			props->_size_changed = this->_size_changed;
			props->_bold = this->_bold;
			props->_bold_changed = this->_bold_changed;
			props->_italic = this->_italic;
			props->_italic_changed = this->_italic_changed;
			props->_underline = this->_underline;
			props->_underline_changed = this->_underline_changed;
			props->_strike = this->_strike;
			props->_strike_changed = this->_strike_changed;
			props->_sup = this->_sup;
			props->_sup_changed = this->_sup_changed;
			props->_sub = this->_sub;
			props->_sub_changed = this->_sub_changed;
			props->_align = this->_align;
			props->_align_changed = this->_align_changed;
			props->_color = this->_color;
			props->_color_changed = this->_color_changed;
			props->_font = this->_font;
			props->_font_changed = this->_font_changed;
			return props;
		}

		void TextProps::changed() {
			_size_changed = true;
			_bold_changed = true;
			_italic_changed = true;
			_underline_changed = true;
			_strike_changed = true;
			_sup_changed = true;
			_sub_changed = true;
			_align_changed = true;
			_color_changed = true;
			_font_changed = true;
		}

		void TextProps::log() {
			cout << "TextProps at " << _pos << endl;
			cout << "  font: " << (_font?_font->name:"null") << " (" << _font_changed << ")" << endl;
			cout << "  size: " << _size << " (" << _size_changed << ")" << endl;
			cout << "  bold: " << _bold << " (" << _bold_changed << ")" << endl;
			cout << "  italic: " << _italic << " (" << _italic_changed << ")" << endl;
			cout << "  underline: " << _underline << " (" << _underline_changed << ")" << endl;
			cout << "  strike: " << _strike << " (" << _strike_changed << ")" << endl;
			cout << "  sup: " << _sup << " (" << _sup_changed << ")" << endl;
			cout << "  sub: " << _sub << " (" << _sub_changed << ")" << endl;
			cout << "  align: " << _align << " (" << _align_changed << ")" << endl;
			cout << "  color: " << _color << " (" << _color_changed << ")" << endl;
		}

		Text::Text() {
			// At least one span at the start
			TextProps* props = new TextProps();
			props->changed(); // Bake all props
			_spans.push_back( props );
			_canvasMatrix = new SkMatrix();
		}

		Text::~Text() {
			for (auto span : _spans) delete span;
			delete _canvasMatrix;
		}

		void Text::text( string t, TextProps* props ) {
			_text = t;
			// Remove all except first props
			auto it = _spans.begin(); it++;
			while ( it != _spans.end() ) {
				delete (*it);
				it = _spans.erase( it );
			}
			selectAll();
			if (props) apply( props );
		}

		void Text::select( int from, int to ) {
			if (from < 0) from = 0;
			if (from > _text.size()) from = _text.size();
			if (to < from) to = from;
			if (to > _text.size()) to = _text.size();
			_selStart = from;
			_selEnd = to;
		}

		void Text::selectAll() {
			_selStart = 0;
			_selEnd = _text.size();
		}

		TextProps* Text::props( int pos ) {
			TextProps* props = _spans.front();
			if (_spans.size() > 1) {
				auto it = _spans.begin(); it++;
				while ( it != _spans.end() ) {
					if ( ( *it )->_pos > pos ) {
						return props;
					}
					props = *it;
					it++;
				}
			}
			return props;
		}

		TextProps* Text::_propsAt( int pos, bool create ) {
			auto it = _spans.begin();
			TextProps* check;
			while ( it != _spans.end() ) {
				check = (*it);
				if ( check->_pos == pos ) return check;
				if ( check->_pos > pos ) break;
				it++;
			}
			if (!create) return nullptr;
			TextProps* props = check->clone();
			props->_pos = pos;
			props->changed(); // Bake all props
			_spans.insert( it, props );
			return props;
		}

		TextProps* Text::_propsAfter( int pos ) {
			auto it = _spans.begin();
			while ( it != _spans.end() ) {
				if ( (*it)->_pos > pos ) return *it;
				it++;
			}
			return nullptr;
		}

		void Text::_removeSpan( TextProps* props ) {
			_spans.remove( props );
			delete props;
		}

		void Text::apply( TextProps* newProps ) {
			// If the selection is not right to the end, get the props at the end. Remember them if they are not equal to our delta
			TextProps* end = nullptr;
			if (_selEnd < _text.size()) {
				end = props( _selEnd - 1 );
				if (newProps->equals(end)) end = nullptr;
			}
			// Get the props exactly at the start of the selection or create props there if none exist yet (copy from previous props).
			// Then iterate through all spans in the selection and update them to bold. If a span equals a previous span it is removed. 
			TextProps* props = _propsAt( _selStart, true );
			TextProps* prev = nullptr;
			do {
				props->copy( newProps );
				if (prev && prev->equals(props)) {
					_removeSpan(props);
				}
				else {
					prev = props;
				}
				props = _propsAfter( prev->_pos );
			} while (props && props->_pos < _selEnd);
			// Exit if there was no end span or the end span state doesn't need to change
			if (!end) return;
			// Get the props at exactly the end of the selection or create props there if none exist yet (copy from previous props).
			props = _propsAt( _selEnd-1, true );
			newProps->copy( end, props );
		}
		
		void Text::bold( bool state ) {
			TextProps* props = new TextProps();
			props->bold( state );
			apply( props );
			delete props;
		}

		void Text::italic( bool state ) {
			TextProps* props = new TextProps();
			props->italic( state );
			apply( props );
			delete props;
		}

		void Text::underline( bool state ) {
			TextProps* props = new TextProps();
			props->underline( state );
			apply( props );
			delete props;
		}

		void Text::strike( bool state ) {
			TextProps* props = new TextProps();
			props->strike( state );
			apply( props );
			delete props;
		}

		void Text::sup( bool state ) {
			TextProps* props = new TextProps();
			props->sup( state );
			apply( props );
			delete props;
		}

		void Text::sub( bool state ) {
			TextProps* props = new TextProps();
			props->sub( state );
			apply( props );
			delete props;
		}

		void Text::align( int alignment ) {
			TextProps* props = new TextProps();
			props->align( alignment );
			apply( props );
			delete props;
		}

		void Text::size( double s ) {
			TextProps* props = new TextProps();
			props->size( s );
			apply( props );
			delete props;
		}

		void Text::color( colorARGB c ) {
			TextProps* props = new TextProps();
			props->color( c );
			apply( props );
			delete props;
		}

		void Text::font( string name ) {
			TextProps* props = new TextProps();
			props->font( name );
			apply( props );
			delete props;
		}

		string Text::textAsString() {
			return _text;
		}

		string Text::selectedTextAsString() {
			if (_selEnd == _selStart) return "";
			return _text.substr( _selStart, _selEnd - _selStart );
		}

		Text* Text::selectedText() {
			Text* t = new Text();
			// If the selection is empty, copy only the props
			if (_selEnd == _selStart){
				t->apply( this->props(_selStart) );
				return t;
			}
			// Copy the text portion
			t->text( _text.substr( _selStart, _selEnd - _selStart ) );
			// Copy the props
			TextProps* p = props( _selStart );
			int pos = _selStart;
			while (p && pos < _selEnd) {
				t->select(pos-_selStart,_selEnd-_selStart);
				t->apply( p );
				p = _propsAfter( pos );
				if (p) pos = p->_pos;
			}
			return t;
		}

		void Text::render( SkSurface* surface, double dt ) {
			if ( _text != "" ) {
				SkiaTypes::convert(_transform, _canvasMatrix);
				SkCanvas* canvas = surface->getCanvas();
				canvas->save();
				canvas->concat( *_canvasMatrix );
				SkPaint paint;
				paint.setAntiAlias(true);
				paint.setAlpha( alpha );
				paint.setStroke( false );
				double xx = x;
				double yy = y;
				for (auto props : _spans) {
					SkFont font = SkFont( props->_font->typeface, props->_size );
					paint.setColor( props->color() );
					canvas->drawSimpleText( _text.c_str(), _text.size(), SkTextEncoding::kUTF8, xx, yy, font, paint );
				}
				canvas->restore();
				paint.~SkPaint();
			}
			DisplayObject::render( surface, dt );
		}

		void Text::log() {
			cout << "Text: '" << _text << "'" << endl;
			for (auto props : _spans) {
				props->log();
			}
		}

	} // display
} // derive