// Derive
#include "../Player.h"
#include "derive/geom/HitAreaRect.h"
// Skia
#include "core/SkColorSpace.h"
// Other
#include <algorithm>
#include <math.h>
#include <string.h>
#include <iostream>

using namespace std;
using namespace derive::display;

namespace derive {

	Player* Player::instance = NULL;

	Player* Player::getInstance() {
		return Player::instance;
	}

	void _deriveOnWindowResize( GLFWwindow* window, int width, int height ) {
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
		// Mouse
		_mouseOver = glfwGetWindowAttrib( _window, GLFW_HOVERED );
		double mx;
		double my;
		glfwGetCursorPos( _window, &mx, &my );
		_mouse = new Point( mx, my );
		_hitAreas = new vector<DisplayObject*>();
		_mouseEvents = new vector<MouseEvent*>();
		// Callbacks
		glfwSetWindowSizeCallback( _window, _deriveOnWindowResize ); // Window resize
		glfwSetKeyCallback( _window, _deriveOnKey ); // Key
		glfwSetCursorEnterCallback( _window, _deriveOnMouseEnterLeave ); // Mouse residency
		glfwSetMouseButtonCallback( _window, _deriveOnMouseButton ); // Mouse button
		glfwSetScrollCallback( _window, _deriveOnMouseScroll ); // Mouse scroll
		glfwSetDropCallback( _window, _deriveOnFileDrop ); // File/folder drop target
		// Stage
		_stage = new DisplayObject();
		_stage->stage( _stage );
		_stage->hitArea( new HitAreaRect( 0, 0, width, height ) );
		_stage->width = width;
		_stage->height = height;
		_stageTransform = new Matrix();
		_stageRect = new SkRect();
		// Force resize to create the render surface
		onResize();
		// Start timing
		_lastUpdateSeconds = glfwGetTime();
		_lastRenderSeconds = _lastUpdateSeconds;
	}

	Player::~Player() {
		delete _surface;
		delete _context;
		delete _stage;
		delete _stageRect;
		delete _stageTransform;
		delete _mouse;
		for (auto event : *_mouseEvents) delete event;
		delete _hitAreas;
		delete _mouseEvents;
		glfwTerminate();
		instance = NULL;
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
					if (child->hitArea()->hit(child->mouse)) {
						// Over
						if (!child->hitArea()->over) {
							child->hitArea()->over = true;
							MouseEvent* event = new MouseEvent( MouseEvent::over, child );
							event->localX = child->mouse->x;
							event->localY = child->mouse->y;
							event->stageX = stage()->mouse->x;
							event->stageY = stage()->mouse->y;
							child->dispatch( event );
							delete event;
						}
						// Step pending mouse events
						auto it = _mouseEvents->begin();
						while ( it != _mouseEvents->end() ) {
							(*it)->target = child;
							(*it)->localX = child->mouse->x;
							(*it)->localY = child->mouse->y;
							child->dispatch( (*it) );
							// remove event if receiver has stopped propagation
							if ((*it)->propogate == PropogationType::None) {
								it = _mouseEvents->erase( it );
							}
							else {
								++it;
							}
						}
					}
					// Out
					else if (child->hitArea()->over){
						child->hitArea()->over = false;
						MouseEvent* event = new MouseEvent( MouseEvent::out, child );
						event->localX = child->mouse->x;
						event->localY = child->mouse->y;
						event->stageX = stage()->mouse->x;
						event->stageY = stage()->mouse->y;
						child->dispatch( event );
						delete event;
					}
				}
			}
			// Clear mouse events
			for (auto event : *_mouseEvents) delete event;
			_mouseEvents->clear();

			// Update
			_dtUpdateSeconds = nowSeconds - _lastUpdateSeconds;
			if ( _dtUpdateSeconds >= _updatePeriod ) {
				_lastUpdateSeconds = nowSeconds;

				// Update display list
				stage()->preUpdate( _dtUpdateSeconds );
				update( _dtUpdateSeconds );
				stage()->update( _dtUpdateSeconds );
				stage()->postUpdate( _dtUpdateSeconds );
			}

			// Render
			_dtRenderSeconds = nowSeconds - _lastRenderSeconds;
			if ( _dtRenderSeconds >= _renderPeriod ) {
				_lastRenderSeconds = nowSeconds;

				// Clip to the stage
				// XXX: Clip to dirty area
				_surface->getCanvas()->clear( _lboxColor );
				_surface->getCanvas()->save();
				_surface->getCanvas()->clipRect( *_stageRect );
				_surface->getCanvas()->clear( _bgColor );

				// Pre-render process
				stage()->preRender( _surface, _stageTransform, _dirty, _dtRenderSeconds );

				// Render
				stage()->render( _surface, _dtRenderSeconds );

				// Post render process
				int depth = 0;
				double mx;
				double my;
				glfwGetCursorPos( _window, &mx, &my );
				if ((_mouse->x != mx) || (_mouse->y != my)){
					MouseEvent* event = new MouseEvent( MouseEvent::move );
					event->moveX = mx - _mouse->x;
					event->moveY = my - _mouse->y;
					_mouseEvents->push_back( new MouseEvent( MouseEvent::move ) );
				}
				_mouse->set( mx, my );
				_hitAreas->clear();
				stage()->postRender( _surface, _stageTransform, _dtRenderSeconds, depth, _hitAreas, _mouse );
				_surface->getCanvas()->restore();
				_dirty = false;

				// Finalize
				_context->flush();
				glfwSwapBuffers( _window );
			}

			// Process pending events
			glfwPollEvents();
		}
	}

	void Player::onResize() {
		glfwGetWindowSize( _window, &width, &height );

		delete _surface;
		delete _context;

		GrContextOptions options;
		_context = GrDirectContext::MakeGL( nullptr, options ).release();

		GrGLFramebufferInfo framebufferInfo;
		framebufferInfo.fFBOID = 0; // assume default framebuffer
		framebufferInfo.fFormat = GL_RGBA8;

		GrBackendRenderTarget backendRenderTarget(
			width, height,
			0, // sample count
			0, // stencil bits
			framebufferInfo );

		_surface = SkSurface::MakeFromBackendRenderTarget(
			_context,
			backendRenderTarget,
			kBottomLeft_GrSurfaceOrigin,
			kRGBA_8888_SkColorType,
			nullptr, nullptr ).release();
		if ( _surface == nullptr ) abort();

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
		_stageRect->setLTRB(
			max( 0, (int)stage()->x ),
			max( 0, (int)stage()->y ),
			min( width, (int)( stage()->x + stage()->width + 0.5 ) ),
			min( height, (int)( stage()->y + stage()->height + 0.5 ) )
		);
		HitAreaRect* stageHit = (HitAreaRect*)_stage->hitArea();
		stageHit->x = _stage->x;
		stageHit->y = _stage->y;
		stageHit->width = _stage->width;
		stageHit->height = _stage->height;

		_dirty = true;
	}

	void Player::onKey( int key, int scancode, int action, int mods ) {
		KeyEvent* event = new KeyEvent( 0, stage() );
		event->propogate = PropogationType::Downward;
		event->keyCode = key;
		event->scanCode = scancode;
		switch ( action ) {
			case GLFW_PRESS: event->type = KeyEvent::down; break;
			case GLFW_RELEASE: event->type = KeyEvent::up; break;
			case GLFW_REPEAT: event->type = KeyEvent::repeat; break;
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
		MouseEvent* event = new MouseEvent();
		event->stageX = stage()->mouse->x;
		event->stageY = stage()->mouse->y;
		switch ( action ) {
			case GLFW_PRESS:
				switch ( button ) {
					case GLFW_MOUSE_BUTTON_LEFT: event->type = MouseEvent::down; break;
					case GLFW_MOUSE_BUTTON_RIGHT: event->type = MouseEvent::rightDown; break;
					case GLFW_MOUSE_BUTTON_MIDDLE: event->type = MouseEvent::middleDown; break;
				}
				break;
			case GLFW_RELEASE:
				switch ( button ) {
					case GLFW_MOUSE_BUTTON_LEFT: event->type = MouseEvent::up; break;
					case GLFW_MOUSE_BUTTON_RIGHT: event->type = MouseEvent::rightUp; break;
					case GLFW_MOUSE_BUTTON_MIDDLE: event->type = MouseEvent::middleUp; break;
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
		MouseEvent* event = new MouseEvent( MouseEvent::scroll );
		event->stageX = stage()->mouse->x;
		event->stageY = stage()->mouse->y;
		event->scrollX = xoffset;
		event->scrollY = yoffset;
		_mouseEvents->push_back( event );
	}

	void Player::onFileDrop( int count, const char** paths ) { }

}