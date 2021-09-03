#pragma once

// Derive
#include "EmbeddedAssets.h"
#include "derive/display/Color.h"
#include "derive/display/DisplayObject.h"
#include "derive/geom/Bounds.h"
// Rive
#include "rive/artboard.hpp"
#include "rive/animation/linear_animation_instance.hpp"
// Skia
#include "core/SkMatrix.h"
// Other
#include <string>

using namespace rive;
using namespace derive::assets;

namespace derive {
	namespace display {

		/**
		 * @brief A rive animation class
		 */
		class Rive : public DisplayObject {
		protected:
			SkMatrix* _rendererTransform;
		public:
			/**
			 * @brief Construct a new Rive object
			 *
			 */
			Rive();

			/**
			 * @brief Create Rive from an embedded assets by path
			 *
			 * @param filename The path and name of the embdded asset
			 */
			Rive( string filepath );

			/**
			 * @brief Destroy the Image object
			 */
			virtual ~Rive();

			/**
			 * @brief Load rive file by path
			 *
			 * @param filepath The path and name of the embdded asset
			 * @return true The file was loaded succesfully
			 * @return false The file was not loaded
			 */
			virtual bool load( string filepath );

			/**
			 * @brief Check if the rive animation was succesfully loaded
			 *
			 * @return true The rive animation was loaded successfully
			 * @return false The rive animation is not loaded
			 */
			virtual bool loaded();

			/**
			 * @Brief Start playing an animation
			 * @param index The index of the animation to play
			 **/
			virtual void play( int index = 0 );

			/**
			 * @brief Called every update step
			 * Use this to update physics or other operations that need to happen is often as
			 * possible. Do not use this to perform any drawing or rendering (@see render).
			 * @param dt The time, in seconds, since the last call to update
			 */
			virtual void update( double dt );

			/**
			 * @brief Called every render step
			 * Usually called less often than update (@see update).
			 * Use this to perform any drawing or rendering operatons.
			 * @param drawingContext The context to draw to
			 * @param dt The time, in seconds, since the last call to update
			 */
			virtual void render( SkSurface* surface, double dt );

		protected:
			// The artboard for this rive
			Artboard* artboard = nullptr;
			// The animation instance
			LinearAnimationInstance* animation = nullptr;

			/**
			 * @brief Load from an embedded asset
			 *
			 * @param asset The asset object
			 */
			virtual void loadFromAsset( EmbeddedAssetData asset );

		};

	} // display
} // derive