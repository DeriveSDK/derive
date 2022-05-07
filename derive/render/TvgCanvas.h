#pragma once

// Derive
#include "Canvas.h"
#include "RiveTvgRenderer.h"
// ThorVG
#include <thorvg.h>

using namespace derive::display;

namespace derive {
	namespace render {

		/**
		 * @brief An abstract class that manages low-level pixel bashing
		 */
		class TvgCanvas : public Canvas {
		protected:
			std::unique_ptr<tvg::SwCanvas> _tvgSwCanvas;
			RiveTvgRenderer* _renderer;
		public:

			/**
			 * @brief Create a thorVG canvas object
			 */
			TvgCanvas();

			/**
			 * @brief (Re)create the buffer at a new size
			 * @param w Width of buffer
			 * @param h Height of buffer
			 */
			void create(int w, int h) override;

			/**
			 * Clear the canvas
			 * @param color The color to clear to
			 */
			void clear(colorARGB color) override;

			/**
			 * Draw snapshot of rive artboard with given matrix. Respects clipping area
			 * @param artboard The artboard to draw
			 * @param transform The transformation matrix
			 */
			void draw(rive::Artboard* artboard, derive::geom::Matrix* transform) override;

			void draw(unique_ptr<tvg::Picture> picture, Matrix* transform) override;

			/**
			 * @brief Finalise render
			 * Render steps are performed here to finalise a render pass
			 */
			void render() override;
		};

	} // render
} // derive