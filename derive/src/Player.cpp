// Derive
#include "../Player.h"
#include "derive/events/PlayerEvent.h"
#include "derive/geom/HitAreaRect.h"
// Other
#include <algorithm>
#include <math.h>
#include <string.h>
#include <thread>
#include <iostream>

using namespace derive::display;
using namespace derive::events;

namespace derive {

	Player* Player::instance = NULL;

	Player* Player::getInstance() {
		return Player::instance;
	}

	Context* Player::getContext() {
		if (Player::getInstance()) {
			return Player::instance->_context;
		}
		return nullptr;
	}

	void _deriveOnFramebufferResize( GLFWwindow* window, int width, int height ) {
		if ( Player::getInstance() ) {
			Player::getInstance()->onResize();
		}
	}

	void _deriveOnKey( GLFWwindow* window, int key, int scancode, int action, int mods ) {
		if ( Player::getInstance() ) {
			Player::getInstance()->onKey( key, scancode, action, mods );
		}
	}

	void _deriveOnMouseEnterLeave( GLFWwindow* window, int entered ) {
		if ( Player::getInstance() ) {
			Player::getInstance()->onMouseEnterLeave( entered != 0 );
		}
	}

	void _deriveOnMouseButton( GLFWwindow* window, int button, int action, int mods ) {
		if ( Player::getInstance() ) {
			Player::getInstance()->onMouseButton( button, action, mods );
		}
	}

	void _deriveOnMouseScroll( GLFWwindow* window, double xoffset, double yoffset ) {
		if ( Player::getInstance() ) {
			Player::getInstance()->onMouseScroll( xoffset, yoffset );
		}
	}

	void _deriveOnFileDrop( GLFWwindow* window, int count, const char** paths ) {
		if ( Player::getInstance() ) {
			Player::getInstance()->onFileDrop( count, paths );
		}
	}

	void traceGlErrors(string message = "") {
		GLenum err;
		while ((err = glGetError()) != GL_NO_ERROR)
		{
			cout << "OpenGL Error" << (message.length()?" ("+message+")" : "") << ": " << hex << err << dec << endl;
		}
	}

	Player::Player( int width, int height, string name, bool fullscreen ) {
		// Check we are a singleton
		if ( instance ) {
			throw "Only a single player instance may be created";
		}
		instance = this;

		// Initialise GLFW
		if ( !glfwInit() ) {
			throw "Unable to initialise GLFW";
		}
		// Create a window
		GLFWmonitor* monitor = glfwGetPrimaryMonitor();
		const GLFWvidmode* mode = glfwGetVideoMode( monitor );
		glfwWindowHint( GLFW_RED_BITS, mode->redBits );
		glfwWindowHint( GLFW_GREEN_BITS, mode->greenBits );
		glfwWindowHint( GLFW_BLUE_BITS, mode->blueBits );
		glfwWindowHint( GLFW_REFRESH_RATE, mode->refreshRate );
		glfwWindowHint( GLFW_STENCIL_BITS, 0 );
		glfwWindowHint( GLFW_DEPTH_BITS, 0 );
		_window = glfwCreateWindow( width, height, name.c_str(), NULL, NULL );
		if ( !_window ) {
			glfwTerminate();
			throw "Unable to create window";
		}
		if ( fullscreen ) this->fullscreen( true );
		glfwMakeContextCurrent( _window );
		glfwSwapInterval( 1 ); // Vsync
		glEnable(GL_TEXTURE_2D);
		// Mouse
		_mouseOver = glfwGetWindowAttrib( _window, GLFW_HOVERED );
		double mx;
		double my;
		glfwGetCursorPos( _window, &mx, &my );
		_mouse = new Point( mx, my );
		_hitAreas = new vector<DisplayObject*>();
		_mouseEvents = new vector<MouseEvent*>();
		// Callbacks
		glfwSetFramebufferSizeCallback( _window, _deriveOnFramebufferResize); // Framebuffer / Window resize
		glfwSetKeyCallback( _window, _deriveOnKey ); // Key
		glfwSetCursorEnterCallback( _window, _deriveOnMouseEnterLeave ); // Mouse residency
		glfwSetMouseButtonCallback( _window, _deriveOnMouseButton ); // Mouse button
		glfwSetScrollCallback( _window, _deriveOnMouseScroll ); // Mouse scroll
		glfwSetDropCallback( _window, _deriveOnFileDrop ); // File/folder drop target
		// Initialise ThorVG (tvg) and drawing context
		tvg::Initializer::init(tvg::CanvasEngine::Sw, std::thread::hardware_concurrency());
		_context = new Context();
		// Stage
		_stage = new DisplayObject();
		_stage->stage( _stage );
		_stage->hitArea( new HitAreaRect( 0, 0, width, height ) );
		_stage->width = width;
		_stage->height = height;
		_stageTransform = new Matrix();
		// Force resize to create the render surface
		onResize();
		// Start timing
		_lastUpdateSeconds = glfwGetTime();
		_lastRenderSeconds = _lastUpdateSeconds;
	}

	Player::~Player() {
		delete _stage;
		delete _stageTransform;
		delete _mouse;
		delete _hitAreas;
		for ( auto event : *_mouseEvents ) event->recycle();
		delete _mouseEvents;
		delete _context;
		tvg::Initializer::term(tvg::CanvasEngine::Sw);
		glfwDestroyWindow( _window );
		glfwTerminate();
		instance = NULL;

		// Destroy memory pool
		MemoryPool::Destroy<MouseEvent>();
		MemoryPool::Destroy<PlayerEvent>();
	}

	DisplayObject* Player::stage() {
		return _stage;
	}

	void Player::displayMode( int mode ) {
		_displayMode = DisplayMode::Check( mode );
	}

	int Player::displayMode() {
		return _displayMode;
	}

	void Player::scaleMode( int mode ) {
		_scaleMode = ScaleMode::Check( mode );
	}

	int Player::scaleMode() {
		return _scaleMode;
	}

	void Player::alignMode( int mode ) {
		_alignMode = AlignMode::Check( mode );
	}

	int Player::alignMode() {
		return _alignMode;
	}

	void Player::fullscreen( bool state ) {
		if ( _isFullscreen == state ) return;
		_isFullscreen = state;
		if ( _isFullscreen ) {
			// get details of the current monitor that the window is in
			GLFWmonitor* monitor = glfwGetPrimaryMonitor();
			const GLFWvidmode* mode = glfwGetVideoMode( monitor );
			glfwSetWindowMonitor( _window, monitor, 0, 0, mode->width, mode->height, mode->refreshRate );
			glfwMaximizeWindow( _window );
		}
		else {
			glfwSetWindowMonitor( NULL, NULL, 0, 0, 0, 0, 0 );
		}
	}

	bool Player::fullscreen() {
		return _isFullscreen;
	}

	void Player::backgroundColor( colorARGB color ) {
		_bgColor = color;
	}

	colorARGB Player::backgroundColor() {
		return _bgColor;
	}

	void Player::letterboxColor( colorARGB color ) {
		_lboxColor = color;
	}

	colorARGB Player::letterboxColor() {
		return _lboxColor;
	}

	void Player::fps( int render, int update ) {
		_renderPeriod = ( render == 0.0 ) ? 0.0 : 1.0 / render;
		_updatePeriod = ( update == 0.0 ) ? 0.0 : 1.0 / update;
	}

	void Player::run() {
		while ( !glfwWindowShouldClose( _window ) ) {

			// Current time
			double nowSeconds = glfwGetTime();

			// Mouse events: over, out, move
			if ( _hitAreas->size() > 0 ) {
				for ( auto child : *_hitAreas ) {
					if ( child->hitArea()->hit( child->mouse ) ) {
						// Over
						if ( !child->hitArea()->over ) {
							child->hitArea()->over = true;
							MouseEvent* event = MouseEvent::Create( MouseEvent::Over );
							event->localX = child->mouse->x;
							event->localY = child->mouse->y;
							event->stageX = stage()->mouse->x;
							event->stageY = stage()->mouse->y;
							child->dispatch( event );
							event->recycle();
						}
						// Step pending mouse events
						auto it = _mouseEvents->begin();
						while ( it != _mouseEvents->end() ) {
							( *it )->localX = child->mouse->x;
							( *it )->localY = child->mouse->y;
							child->dispatch( ( *it ) );
							// remove event if receiver has stopped propagation
							if ( ( *it )->cancelled ) {
								( *it )->recycle();
								it = _mouseEvents->erase( it );
							}
							else {
								++it;
							}
						}
					}
					// Out
					else if ( child->hitArea()->over ) {
						child->hitArea()->over = false;
						MouseEvent* event = MouseEvent::Create( MouseEvent::Out );
						event->localX = child->mouse->x;
						event->localY = child->mouse->y;
						event->stageX = stage()->mouse->x;
						event->stageY = stage()->mouse->y;
						child->dispatch( event );
						event->recycle();
					}
				}
			}
			// Clear mouse events
			for ( auto event : *_mouseEvents ) event->recycle();
			_mouseEvents->clear();

			// Update
			_dtUpdateSeconds = nowSeconds - _lastUpdateSeconds;
			if ( _dtUpdateSeconds >= _updatePeriod ) {
				_lastUpdateSeconds = nowSeconds;

				// Update display list
				stage()->preUpdate( _dtUpdateSeconds );
				update( _dtUpdateSeconds );
				stage()->update( _dtUpdateSeconds );
				PlayerEvent* event = PlayerEvent::Create( PlayerEvent::Update );
				event->dt = _dtUpdateSeconds;
				stage()->dispatch( event );
				event->recycle();
				stage()->postUpdate( _dtUpdateSeconds );
			}

			// Render
			_dtRenderSeconds = nowSeconds - _lastRenderSeconds;
			if ( _dtRenderSeconds >= _renderPeriod ) {
				_lastRenderSeconds = nowSeconds;

				// Clear context
				_context->clear(_bgColor);

				// Clip to the stage
				/*
				// XXX: Clip to dirty area
				_context->clip(nullptr);
				_context->fill(_lboxColor);
				_context->clip(stage()->bounds());
				_context->fill(_bgColor);
				*/

				// Pre-render process
				stage()->preRender(_context, _stageTransform, _dirty, _dtRenderSeconds);

				// Render
				stage()->render(_context, _dtRenderSeconds );
				PlayerEvent* event = PlayerEvent::Create( PlayerEvent::Render);
				event->dt = _dtRenderSeconds;
				stage()->dispatch( event );
				event->recycle();

				// Post render process
				int depth = 0;
				double mx = _mouse->x;
				double my = _mouse->y;
				glfwGetCursorPos( _window, &_mouse->x, &_mouse->y );
				_hitAreas->clear();
				stage()->postRender(_context, _stageTransform, _dtRenderSeconds, depth, _hitAreas, _mouse);
				_dirty = false;

				// Mouse move event
				if ( ( _mouse->x != mx ) || ( _mouse->y != my ) ) {
					MouseEvent* event = MouseEvent::Create( MouseEvent::Move );
					event->stageX = stage()->mouse->x;
					event->stageY = stage()->mouse->y;
					event->moveX = _mouse->x - mx;
					event->moveY = _mouse->y - my;
					_mouseEvents->push_back( event );
				}

				// Render
				_context->render();

				// XXX: NEED TO CREATE DEBUG BUILDS OF LIBRARIES
				// And also create a proper release config for VS (debug is actually release)
				glClearColor(1.0f, 0.6f, 0.0f, 1.0f);
				glClear(GL_COLOR_BUFFER_BIT);
				glBindTexture(GL_TEXTURE_2D, _texture);
				glTexSubImage2D(
					GL_TEXTURE_2D,
					0,
					0, 0,
					_context->width(), _context->height(),
					GL_RGBA,
					GL_UNSIGNED_BYTE,
					(void*)_context->buffer()
				);
				glBegin(GL_QUADS);
				glTexCoord2f(0, 0); glVertex2f(0, 0);
				glTexCoord2f(1, 0); glVertex2f(width, 0);
				glTexCoord2f(1, 1); glVertex2f(width, height);
				glTexCoord2f(0, 1); glVertex2f(0, height);
				glEnd();
				glBindTexture(GL_TEXTURE_2D, 0);
				traceGlErrors("glEnd");

				glfwSwapBuffers( _window );
			}

			// Process pending events
			glfwPollEvents();
		}
	}

	void Player::onResize() {
		glfwGetWindowSize( _window, &width, &height );

		// Create a new framebuffer in the context
		_context->create(width, height);

		// Create a new texture
		glDeleteTextures(1, &_texture);
		glGenTextures(1, &_texture);
		glBindTexture(GL_TEXTURE_2D, _texture);
		/*
		GLint const Swizzle[] = { GL_BLUE, GL_GREEN, GL_RED, GL_ALPHA };
		glTexParameteriv(GL_TEXTURE_2D, GL_TEXTURE_SWIZZLE_RGBA, Swizzle);
		*/
		glTexImage2D(
			GL_TEXTURE_2D,
			0,
			GL_RGBA,
			_context->width(), _context->height(),
			0,
			GL_RGBA,
			GL_UNSIGNED_BYTE,
			(void*)_context->buffer()
		);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		cout << "Window size " << _context->width() << " x " << _context->height() << endl;
		traceGlErrors();

		// Set projection
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(0.0f, width, height, 0.0f, 0.0f, 1.0f);
		glViewport(0, 0, width, height);

		// Scale stage
		double fx = width / stage()->width;
		double fy = height / stage()->height;
		switch ( _displayMode ) {
			case DisplayMode::Contain:
			case DisplayMode::Letterbox: {
				if ( fx < fy ) fy = fx;
				else fx = fy;
				break;
			}
			case DisplayMode::Cover: {
				if ( fx > fy ) fy = fx;
				else fx = fy;
				break;
			}
		}
		switch ( _scaleMode ) {
			case ScaleMode::Pixel: {
				if ( _displayMode == DisplayMode::Cover ) {
					fx = ceil( fx );
					fy = ceil( fy );
				}
				else {
					fx = max( 1.0, floor( fx ) );
					fy = max( 1.0, floor( fy ) );
				}
				break;
			}
		}
		stage()->scaleX = fx;
		stage()->scaleY = fy;
		double sw = stage()->width * fx;
		double sh = stage()->height * fy;
		// Position stage horizontally
		if ( _alignMode == 0 || ( _alignMode & AlignMode::Left && _alignMode & AlignMode::Right ) ) {
			stage()->x = ( width - sw ) / 2;
		}
		else if ( _alignMode & AlignMode::Left ) {
			stage()->x = 0;
		}
		else if ( _alignMode & AlignMode::Right ) {
			stage()->x = width - sw;
		}
		// Position stage vertically
		if ( _alignMode == 0 || ( _alignMode & AlignMode::Top && _alignMode & AlignMode::Bottom ) ) {
			stage()->y = ( height - sh ) / 2;
		}
		else if ( _alignMode & AlignMode::Top ) {
			stage()->y = 0;
		}
		else if ( _alignMode & AlignMode::Bottom ) {
			stage()->y = height - sh;
		}
		HitAreaRect* stageHit = (HitAreaRect*)_stage->hitArea();
		stageHit->x = _stage->x;
		stageHit->y = _stage->y;
		stageHit->width = _stage->width;
		stageHit->height = _stage->height;

		_dirty = true;
	}

	void Player::onKey( int key, int scancode, int action, int mods ) {
		KeyEvent* event = new KeyEvent();
		event->keyCode = key;
		event->scanCode = scancode;
		switch ( action ) {
			case GLFW_PRESS: event->type = KeyEvent::Down; break;
			case GLFW_RELEASE: event->type = KeyEvent::Up; break;
			case GLFW_REPEAT: event->type = KeyEvent::Repeat; break;
		}
		if ( mods & GLFW_MOD_SHIFT ) event->shift = true;
		if ( mods & GLFW_MOD_ALT ) event->alt = true;
		if ( mods & GLFW_MOD_CONTROL ) event->ctrl = true;
		if ( mods & GLFW_MOD_SUPER ) event->super = true;
		if ( mods & GLFW_MOD_CAPS_LOCK ) event->capsLock = true;
		if ( mods & GLFW_MOD_NUM_LOCK ) event->numLock = true;
		stage()->dispatch( event );
	}

	void Player::onMouseEnterLeave( bool entered ) {
		_mouseOver = entered;
	}

	void Player::onMouseButton( int button, int action, int mods ) {
		MouseEvent* event = MouseEvent::Create();
		event->stageX = stage()->mouse->x;
		event->stageY = stage()->mouse->y;
		switch ( action ) {
			case GLFW_PRESS:
				switch ( button ) {
					case GLFW_MOUSE_BUTTON_LEFT: event->type = MouseEvent::Down; break;
					case GLFW_MOUSE_BUTTON_RIGHT: event->type = MouseEvent::RightDown; break;
					case GLFW_MOUSE_BUTTON_MIDDLE: event->type = MouseEvent::MiddleDown; break;
				}
				break;
			case GLFW_RELEASE:
				switch ( button ) {
					case GLFW_MOUSE_BUTTON_LEFT: event->type = MouseEvent::Up; break;
					case GLFW_MOUSE_BUTTON_RIGHT: event->type = MouseEvent::RightUp; break;
					case GLFW_MOUSE_BUTTON_MIDDLE: event->type = MouseEvent::MiddleUp; break;
				}
				break;
		}
		if ( mods & GLFW_MOD_SHIFT ) event->shift = true;
		if ( mods & GLFW_MOD_ALT ) event->alt = true;
		if ( mods & GLFW_MOD_CONTROL ) event->ctrl = true;
		if ( mods & GLFW_MOD_SUPER ) event->super = true;
		if ( mods & GLFW_MOD_CAPS_LOCK ) event->capsLock = true;
		if ( mods & GLFW_MOD_NUM_LOCK ) event->numLock = true;
		_mouseEvents->push_back( event );
	}

	void Player::onMouseScroll( double xoffset, double yoffset ) {
		MouseEvent* event = MouseEvent::Create( MouseEvent::Scroll );
		event->stageX = stage()->mouse->x;
		event->stageY = stage()->mouse->y;
		event->scrollX = xoffset;
		event->scrollY = yoffset;
		_mouseEvents->push_back( event );
	}

	void Player::onFileDrop( int count, const char** paths ) {}

}