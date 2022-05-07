#pragma once

// Derive
#include "derive/display/Color.h"
#include "derive/geom/Bounds.h"
#include "derive/geom/Matrix.h"
// ThorVG
#include <thorvg.h>

using namespace derive::display;
using namespace derive::geom;

namespace derive {
	namespace render {

		/**
		 * @brief An abstract class that manages low-level pixel bashing
		 */
		class Context {
		protected:
			colorARGB* _buffer = nullptr;
			int _width = 0;
			int _height = 0;
			Bounds* _clip = nullptr;
			unique_ptr<tvg::SwCanvas> _canvas = nullptr;
		public:
			/** 
			 * @brief Create a context object 
			 */
			Context();

			/**
			 * @brief Destroy the context object
			 */
			~Context();

			/**
			 * @brief (Re)create the buffer at a new size
			 * @param w Width of buffer
			 * @param h Height of buffer
			 */
			void create(int w, int h);

			/**
			 * Return a reference to the raw pixel buffer
			 * @return Buffer
			 */
			colorARGB* buffer();

			/**
			 * Get buffer width
			 * @return The buffer width in pixels
			 */
			int width();

			/**
			 * Get buffer height
			 * @return The buffer height in pixels
			 */
			int height();

			/**
			 * Set a clip area
			 * @param bounds The area to clip to. A nullptr will reset the clipping area
			 */
			void clip(Bounds* bounds);

			/**
			 * Clear the canvas
			 * @param color The color to clear to
			 */
			void clear(colorARGB color = 0x00000000);

			/**
			 * Fill the canvas with the specified color. Respects clipping area
			 * @param color The color to clear to
			 */
			void fill(colorARGB color);

			/**
			 * Set single pixel to specified value. For bulk operations, directly access
			 * the pixel buffer instead (@see buffer). 
			 * @param x The x coordinate
			 * @param y The y coordinate
			 * @param color The color to set
			 */
			void pixel(int x, int y, colorARGB color);

			/**
			 * Get the value of a single pixel. For bulk operations, directly access
			 * the pixel buffer instead (@see buffer). 
			 * @param x The x coordinate
			 * @param y The y coordinate
			 */
			colorARGB pixel(int x, int y);

			/**
			 * Add a scene object to the canvas
			 * @param paint The scene to add
			 */
			void push(tvg::Scene* scene);

			/**
			 * Update a scene object that is on the canvas
			 * @param paint The scene to update
			 */
			void update(tvg::Scene* scene);

			/** 
			 * Render the queued objects to the canvas 
			 */
			void render();
		};

	} // render
} // derive