#pragma once

// Derive
#include "EmbeddedAssets.h"
#include "derive/display/Color.h"
#include "derive/display/DisplayObject.h"
// Skia
#include "core/SkBitmap.h"
#include "core/SkImage.h"
#include "core/SkMatrix.h"
// Other
#include <string>

using namespace derive::assets;

namespace derive {
	namespace display {

		/**
		 * @brief A static image class
		 * @see AnimatedImage for animated gif and png
		 * @see Rive for animated Rive files
		 */
		class Image : public DisplayObject {
		private:
			SkBitmap* _bitmap = nullptr;
			sk_sp<SkImage> _image = nullptr;
			SkMatrix* _canvasMatrix = nullptr;
			int _width;
			int _height;
		public:
			/**
			 * @brief Construct a new Image object
			 *
			 */
			Image();

			/**
			 * @brief Create Image from an embedded assets by name
			 *
			 * @param filename The path and name of the embdded asset
			 */
			Image( string filepath );

			/**
			 * @brief Destroy the Image object
			 */
			virtual ~Image();

			/**
			 * @brief Load image file by path
			 *
			 * @param filepath The path and name of the embdded asset
			 * @return true The file was loaded succesfully
			 * @return false The file was not loaded
			 */
			virtual bool load( string filepath );

			/**
			 * @brief Check if the image was succesfully loaded
			 *
			 * @return true The image was loaded successfully
			 * @return false The image is not loaded
			 */
			virtual bool loaded();

			/**
			 * @brief The loaded image width
			 *
			 * @return int The width
			 */
			virtual int width();

			/**
			 * @brief The loaded image height
			 *
			 * @return int The height
			 */
			virtual int height();

			/**
			 * @brief Called every render step
			 * Usually called less often than update (@see update).
			 * Use this to perform any drawing or rendering operatons.
			 * @param drawingContext The context to draw to
			 * @param dt The time, in seconds, since the last call to update
			 */
			virtual void render( SkSurface* surface, double dt );

		protected:
			/**
			 * @brief Load an image from an embedded asset
			 *
			 * @param asset The asset object
			 */
			virtual void loadFromAsset( EmbeddedAssetData asset );

		};

	} // display
} // derive