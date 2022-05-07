// Derive
#include "../TvgCanvas.h"

using namespace derive::render;
using namespace derive::display;

namespace derive {
	namespace render {

		TvgCanvas::TvgCanvas() {
			_tvgSwCanvas = tvg::SwCanvas::gen();
			_renderer = new RiveTvgRenderer(_tvgSwCanvas.get());
		}

		/**
		* @brief (Re)create the buffer at a new size
		* @param w Width of buffer
		* @param h Height of buffer
		*/
		void TvgCanvas::create(int w, int h){
			Canvas::create(w, h);
			_tvgSwCanvas->target((uint32_t*)_buffer, _width, _width, _height, tvg::SwCanvas::ARGB8888);
		}

		/**
		 * @brief Finalise render
		 * Render steps are performed here to finalise a render pass
		*/
		void TvgCanvas::render() {
			_tvgSwCanvas->draw();
			_tvgSwCanvas->sync();
		}

	} // render
} // derive