#pragma once

// Derive
#include "derive/display/AlignMode.h"
#include "derive/display/Color.h"
#include "derive/display/DisplayObject.h"
#include "derive/display/DisplayMode.h"
#include "derive/display/ScaleMode.h"
#include "derive/events/MouseEvent.h"
#include "derive/geom/Matrix.h"
#include "derive/render/Context.h"
// GLFW
#include <GL/glew.h>
#include <GLFW/glfw3.h>
// Other
#include <string>
#include <vector>

using namespace derive;
using namespace derive::render;
using namespace derive::display;
using namespace derive::geom;

namespace derive {

	class Player {
	private:
		static Player* instance;
	protected:
		GLFWwindow* _window = nullptr;
		bool _isFullscreen = false;
		colorARGB _bgColor = 0xffffffff;
		colorARGB _lboxColor = 0x000000ff;
		int width = 0;
		int height = 0;
		int _displayMode = DisplayMode::Default;
		int _scaleMode = ScaleMode::Default;
		int _alignMode = AlignMode::Default;
		bool _mouseOver = false;
		bool _mouseMoved = false;
		derive::geom::Point* _mouse;
		vector<DisplayObject*>* _hitAreas;
		vector<MouseEvent*>* _mouseEvents;
		Context* _context;
		GLuint _texture = 0;

		double _lastUpdateSeconds;
		double _dtUpdateSeconds;
		double _updatePeriod = 0.0; // as fast as possible
		double _lastRenderSeconds;
		double _dtRenderSeconds;
		double _renderPeriod = 1.0 / 60.0; // 60fps

		DisplayObject* _stage;
		derive::geom::Matrix* _stageTransform;
		bool _dirty = true;

	public:
		/**
		 * @brief Get the Player singleton instance
		 *
		 * @return Player* The player
		 */
		static Player* getInstance();

		/**
		 * @brief Get the context from the Player singleton instance
		 *
		 * @return Context* The player's drawing context
		 */
		static Context* getContext();

		/**
		 * @brief Construct a new Player object
		 * Construct a new Player with a default window
		 * @param width 	The window width
		 * @param height 	The window height
		 * @param name 		The name of the window
		 * @param fullscreen True to start the window fullscreen
		 */
		Player( int width, int height, string name, bool fullscreen = false );

		/**
		 * @brief Destroy the Player object
		 *
		 */
		virtual ~Player();

		/**
		 * @brief Set the target render and update framerate
		 * Usually update is called as often as possible (set update fps = 0), but render
		 * is usually called less frequently - e.g. 30 or 60 fps.
		 * @param render	The target rendering frame rate
		 * @param update	The target update frame rate
		 */
		virtual void fps( int render, int update = 0 );

		/**
		 * @brief Starts the player
		 */
		virtual void run();

		/**
		 * @brief Called on update fps
		 * User can override this to call code on every update cycle
		 * @param dt Seconds since last update
		 */
		virtual void update( double dt ) {}

		/**
		 * @brief Set the display mode
		 *
		 * @param scaleMode The display mode
		 */
		virtual void displayMode( int mode );

		/**
		 * @brief Get the display mode
		 *
		 * @return int The display mode
		 */
		virtual int displayMode();

		/**
		 * @brief Set the scale mode
		 *
		 * @param scaleMode The scale mode
		 */
		virtual void scaleMode( int mode );

		/**
		 * @brief Get the scale mode
		 *
		 * @return int The scale mode
		 */
		virtual int scaleMode();

		/**
		 * @brief Set the alignment mode
		 *
		 * @param alignMode The alignment mode
		 */
		virtual void alignMode( int mode );

		/**
		 * @brief Get the alignment mode
		 *
		 * @return int The alignment mode
		 */
		virtual int alignMode();

		/**
		 * @brief Set whether the window should be fullscreen or not
		 *
		 * @param state True for fullscreen, false for windowed
		 */
		virtual void fullscreen( bool state );

		/**
		 * @brief Check if thw window is fullscreen
		 *
		 * @return true If the window is fullscreen
		 * @return false If the window is windowed
		 */
		virtual bool fullscreen();

		/**
		 * @brief Set the background color of the window
		 *
		 * @param color The color
		 */
		virtual void backgroundColor( colorARGB color );

		/**
		 * @brief Get the background color of the window
		 *
		 * @return colorARGB The color
		 */
		virtual colorARGB backgroundColor();

		/**
		 * @brief Set the color of the letterbox
		 *
		 * @param color The color
		 */
		virtual void letterboxColor( colorARGB color );

		/**
		 * @brief Get the letterbox color
		 *
		 * @return colorARGB The color
		 */
		virtual colorARGB letterboxColor();

		/**
		 * @brief Get the stage
		 * The stage is the root display object at the lowest level. All other display objects are
		 * added as children or descendents of the stage.
		 * @return Stage* The stage
		 */
		DisplayObject* stage();

		/**
		 * @brief Update the window if it has resized
		 */
		virtual void onResize();

		/**
		 * @brief Called when a key action occurs (press, release, etc)
		 *
		 * @param key The key
		 * @param scancode The scancode
		 * @param action The action
		 * @param mods The modifiers
		 */
		virtual void onKey( int key, int scancode, int action, int mods );

		/**
		 * @brief Called when the cursor/mouse enters or leaves the window
		 *
		 * @param entered True if entered, false if left
		 */
		virtual void onMouseEnterLeave( bool entered );

		/**
		 * @brief Called when a mouse button is actioned (press, release)
		 *
		 * @param button The button
		 * @param action The action
		 * @param mods The modifiers
		 */
		virtual void onMouseButton( int button, int action, int mods );

		/**
		 * @brief Called when the scroll wheel moves, or when a scroll pad is used
		 *
		 * @param xoffset The movement in the X direction
		 * @param yoffset The movement in the Y direction
		 */
		virtual void onMouseScroll( double xoffset, double yoffset );

		/**
		 * @brief Called when file(s) and/or folder(s) are dropped on the player window
		 *
		 * @param count The number of file paths
		 * @param paths Pointers to the file paths
		 */
		virtual void onFileDrop( int count, const char** paths );
	};

}