// Derive
#include "../Context.h"
#include "derive/utils/TvgTypes.h"
#include <iostream>

using namespace derive::render;
using namespace derive::display;
using namespace derive::utils;

namespace derive {
	namespace render {

		Context::Context() {
			_clip = new Bounds();
			_canvas = tvg::SwCanvas::gen();
		}

		Context::~Context() {
			_canvas->clear(false);
			delete[] _buffer;
			delete _clip;
		}

		void Context::create(int w, int h) {
			_width = w;
			_height = h;
			delete[] _buffer;
			_buffer = new colorARGB[_width * _height];
			_clip->set(0, 0, _width, _height);
			_canvas->target((uint32_t*)_buffer, _width, _width, _height, tvg::SwCanvas::ABGR8888);
		}

		colorARGB* Context::buffer() {
			return _buffer;
		}

		int Context::width() {
			return _width;
		}

		int Context::height() {
			return _height;
		}

		void Context::clip(Bounds* bounds) {
			// Set clipping area to full buffer, then clip to supplied bounds (intersection)
			_clip->set(0, 0, _width, _height);
			if (bounds) _clip->clip(bounds);
		}

		void Context::clear(colorARGB color) {
			int i = _height * _width;
			while (i--) _buffer[i] = color;
			_canvas->clear(false);
		}

		void Context::fill(colorARGB color) {
			colorARGB* pixel = _buffer + (int)_clip->y() * _width + (int)_clip->x();
			int y = (int)(_clip->height() + 0.5);
			while (y > 0) {
				int x = (int)(_clip->width() + 0.5);
				while (x > 0) {
					pixel[x--] = color;
				}
				pixel += _width;
				y--;
			}
		}

		void Context::pixel(int x, int y, colorARGB color) {
			if ((x < 0) || (x >= _width) || (y < 0) || (y >= _height)) return;
			_buffer[y * _width + x] = color;
		}

		colorARGB Context::pixel(int x, int y) {
			if ((x < 0) || (x >= _width) || (y < 0) || (y >= _height)) return 0;
			return _buffer[y * _width + x];
		}

		void Context::push(tvg::Scene* scene) {
			_canvas->push(unique_ptr<tvg::Scene>(scene));
		}

		void Context::update(tvg::Scene* scene) {
			_canvas->update(scene);
		}

		void Context::render() {
			if (_canvas->draw() == tvg::Result::Success) _canvas->sync();
		}

	} // render
} // derive