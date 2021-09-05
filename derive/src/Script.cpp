// Derive
#include "../Script.h"
#include "derive/Player.h"
#include "derive/geom/Point.h"
#include "derive/geom/Bounds.h"
#include "derive/geom/Matrix.h"
#include "derive/geom/HitAreaRect.h"
#include "derive/geom/HitAreaCircle.h"
#include "derive/display/Color.h"
#include "derive/display/DisplayObject.h"
#include "derive/display/Image.h"
#include "derive/display/Rive.h"
#include "derive/events/KeyEvent.h"
#include "derive/events/MouseEvent.h"
#include "derive/events/PlayerEvent.h"
// Other
#include <iostream>

using namespace std;
using namespace derive::geom;
using namespace derive::display;

namespace derive {

	Script::Script( string path ) {
		runtime = new qjs::Runtime();
		context = new qjs::Context( *runtime );

		bindStd();
		bindGeom();
		bindEvents();
		bindDisplay();
		bindCore();

		try {
			cout << path << endl;
			qjs::Value out = context->evalFile( path.c_str() );
		}
		catch ( qjs::exception ) {
			auto exc = context->getException();
			cout << (std::string)exc << endl;
			if ( (bool)exc["stack"] )
				cout << (std::string)exc["stack"] << endl;
		}
	}
	Script::~Script() {
		delete context;
		delete runtime;
	}

	void Script::bindStd() {
		js_std_init_handlers( runtime->rt );
		JS_SetModuleLoaderFunc( runtime->rt, nullptr, js_module_loader, nullptr );
		js_std_add_helpers( context->ctx, 0, nullptr );
		js_init_module_std( context->ctx, "std" );
		js_init_module_os( context->ctx, "os" );

		const char* import = R"(
			import * as std from 'std';
			import * as os from 'os';
			globalThis.std = std;
			globalThis.os = os;
		)";
		context->eval( import, "<import>", JS_EVAL_TYPE_MODULE );
	}

	void Script::bindGeom() {

		// Create display module
		auto& module = context->addModule( "geom" );

		// Point
		typedef void ( Point::* Point_voidPointF )( Point* );
		typedef void ( Point::* Point_void2DoubleF )( double, double );
		typedef bool ( Point::* Point_boolPointF )( Point* );
		typedef bool ( Point::* Point_bool2DoubleF )( double, double );
		typedef void ( Point::* Point_voidDoubleF )( double );
		typedef void ( Point::* Point_voidDoublePointF )( double, Point* );
		typedef void ( Point::* Point_void3DoubleF )( double, double, double );
		module.class_<Point>( "Point" )
			.constructor<double, double>()
			.fun<&Point::x>( "x" )
			.fun<&Point::y>( "y" )
			.fun<&Point::clear>( "clear" )
			.fun<(Point_voidPointF)&Point::set>( "set" )
			.fun<(Point_void2DoubleF)&Point::set>( "setXY" )
			.fun<(Point_boolPointF)&Point::equals>( "equals" )
			.fun<(Point_bool2DoubleF)&Point::equals>( "equalsXY" )
			.fun<(Point_voidPointF)&Point::translate>( "translate" )
			.fun<(Point_void2DoubleF)&Point::translate>( "translateXY" )
			.fun<(Point_voidPointF)&Point::add>( "add" )
			.fun<(Point_void2DoubleF)&Point::add>( "addXY" )
			.fun<(Point_voidPointF)&Point::subtract>( "subtract" )
			.fun<(Point_void2DoubleF)&Point::subtract>( "subtractXY" )
			.fun<(Point_voidDoubleF)&Point::rotate>( "rotate" )
			.fun<(Point_voidDoublePointF)&Point::rotate>( "rotateAbout" )
			.fun<(Point_void3DoubleF)&Point::rotate>( "rotateAboutXY" )
			.fun<&Point::copy>( "copy" )
			.fun<&Point::clone>( "clone" );

		// Bounds
		typedef double( Bounds::* Bounds_getDoubleF )( ) const;
		typedef void( Bounds::* Bounds_setDoubleF )( double );
		typedef void( Bounds::* Bounds_void2Double )( double, double );
		typedef void( Bounds::* Bounds_voidPoint2Double )( Point* p, double, double );
		typedef void( Bounds::* Bounds_void4Double )( double, double, double, double );
		typedef bool( Bounds::* Bounds_boolBounds )( Bounds* );
		typedef bool( Bounds::* Bounds_bool2Double )( double, double );
		typedef void( Bounds::* Bounds_voidPoint )( Point* );
		typedef bool( Bounds::* Bounds_boolPoint )( Point* );
		module.class_<Bounds>( "Bounds" )
			.constructor<double, double, double, double>()
			.property<(Bounds_getDoubleF)&Bounds::x, (Bounds_setDoubleF)&Bounds::x>( "x" )
			.property<(Bounds_getDoubleF)&Bounds::y, (Bounds_setDoubleF)&Bounds::y>( "y" )
			.property<(Bounds_getDoubleF)&Bounds::x2, (Bounds_setDoubleF)&Bounds::x2>( "x2" )
			.property<(Bounds_getDoubleF)&Bounds::y2, (Bounds_setDoubleF)&Bounds::y2>( "y2" )
			.property<(Bounds_getDoubleF)&Bounds::width, (Bounds_setDoubleF)&Bounds::width>( "width" )
			.property<(Bounds_getDoubleF)&Bounds::height, (Bounds_setDoubleF)&Bounds::height>( "height" )
			.fun<&Bounds::empty>( "empty" )
			.fun<&Bounds::clear>( "clear" )
			.fun<(Bounds_voidPoint)&Bounds::setPos>( "setLeftTop" )
			.fun<(Bounds_void2Double)&Bounds::setPos>( "setLeftTopXY" )
			.fun<(Bounds_voidPoint)&Bounds::setPos2>( "setRightBottom" )
			.fun<(Bounds_void2Double)&Bounds::setPos2>( "setRightBottomXY" )
			.fun<(Bounds_void4Double)&Bounds::setPos>( "setCorners" )
			.fun<(Bounds_voidPoint2Double)&Bounds::set>( "set" )
			.fun<(Bounds_void4Double)&Bounds::set>( "setXY" )
			.fun<(Bounds_boolBounds)&Bounds::contains>( "contains" )
			.fun<(Bounds_boolPoint)&Bounds::contains>( "containsPoint" )
			.fun<(Bounds_bool2Double)&Bounds::contains>( "containsXY" )
			.fun<&Bounds::containsX>( "containsX" )
			.fun<&Bounds::containsY>( "containsY" )
			.fun<&Bounds::overlaps>( "overlaps" )
			.fun<(Bounds_voidPoint)&Bounds::translate>( "translate" )
			.fun<(Bounds_void2Double)&Bounds::translate>( "translateXY" )
			.fun<&Bounds::grow>( "grow" )
			.fun<&Bounds::clip>( "clip" )
			.fun<&Bounds::copy>( "copy" )
			.fun<&Bounds::clone>( "clone" );

		// Matrix
		typedef void( Matrix::* Matrix_voidDouble )( double );
		typedef void( Matrix::* Matrix_void3Double )( double, double, double );
		typedef void( Matrix::* Matrix_voidPoint )( Point* );
		typedef void( Matrix::* Matrix_voidPoint2Double )( Point*, double, double );
		module.class_<Matrix>( "Matrix" )
			.constructor<>()
			.fun<&Matrix::apply>( "apply" )
			.fun<&Matrix::identity>( "identity" )
			.fun<&Matrix::concat>( "concat" )
			.fun<&Matrix::invert>( "invert" )
			.fun<(Matrix_voidPoint)&Matrix::transform>( "transform" )
			.fun<(Matrix_voidPoint2Double)&Matrix::transform>( "transformAbout" )
			.fun<(Matrix_voidPoint)&Matrix::inverseTransform>( "inverseTransform" )
			.fun<(Matrix_voidPoint2Double)&Matrix::inverseTransform>( "inverseTransformAbout" )
			.fun<(Matrix_voidDouble)&Matrix::rotate>( "rotate" )
			.fun<(Matrix_void3Double)&Matrix::rotate>( "rotateAbout" )
			.fun<&Matrix::scale>( "scale" )
			.fun<&Matrix::translate>( "translate" )
			.fun<&Matrix::copy>( "copy" )
			.fun<&Matrix::clone>( "clone" );

		// Hit area
		module.class_<HitArea>( "HitArea" )
			.constructor< double, double >()
			.fun<&HitArea::x>( "x" )
			.fun<&HitArea::y>( "y" )
			.fun<&HitArea::hit>( "hit" );

		// Hit area rect
		module.class_<HitAreaRect>( "HitAreaRect" )
			.base<HitArea>()
			.constructor< double, double, double, double >()
			.fun<&HitAreaRect::width>( "width" )
			.fun<&HitAreaRect::height>( "height" );

		// Hit area circle
		typedef double( HitAreaCircle::* HitAreaCircle_getDoubleF )( void );
		typedef void( HitAreaCircle::* HitAreaCircle_setDoubleF )( double );
		module.class_<HitAreaCircle>( "HitAreaCircle" )
			.base<HitArea>()
			.constructor< double, double, double >()
			.property<(HitAreaCircle_getDoubleF)&HitAreaCircle::radius, (HitAreaCircle_setDoubleF)&HitAreaCircle::radius>( "radius" );

		const char* import = R"(
			import * as geom from 'geom';
			globalThis.geom = geom;
		)";
		context->eval( import, "<import>", JS_EVAL_TYPE_MODULE );
	}

	void Script::bindEvents() {

		// Create events module
		auto& module = context->addModule( "events" );

		// Event object
		module.class_<Event>("Event")
			.constructor<>()
			.fun<&Event::type>("type")
			.fun<&Event::cancelled>( "cancelled" )
			.fun<&Event::stopPropagation>( "stopPropagation" )
			.fun<&Event::reset>( "reset" );
		
		// Key Event object
		module.class_<KeyEvent>( "KeyEvent" )
			.base<Event>()
			.constructor<>()
			.fun<&KeyEvent::keyCode>( "keyCode" )
			.fun<&KeyEvent::scanCode>( "scanCode" )
			.fun<&KeyEvent::alt>( "alt" )
			.fun<&KeyEvent::shift>( "shift" )
			.fun<&KeyEvent::ctrl>( "ctrl" )
			.fun<&KeyEvent::super>( "super" )
			.fun<&KeyEvent::capsLock>( "capsLock" )
			.fun<&KeyEvent::numLock>( "numLock" );

		// Mouse Event object
		module.class_<MouseEvent>( "MouseEvent" )
			.base<KeyEvent>()
			.constructor<>()
			.fun<&MouseEvent::localX>( "localX" )
			.fun<&MouseEvent::localY>( "localY" )
			.fun<&MouseEvent::stageX>( "stageX" )
			.fun<&MouseEvent::stageY>( "stageY" )
			.fun<&MouseEvent::moveX>( "moveX" )
			.fun<&MouseEvent::moveY>( "moveY" )
			.fun<&MouseEvent::scrollX>( "scrollX" )
			.fun<&MouseEvent::scrollY>( "scrollY" );

		// Player Event object
		module.class_<PlayerEvent>( "PlayerEvent" )
			.base<Event>()
			.constructor<>()
			.fun<&PlayerEvent::dt>( "dt" )
			.fun<&PlayerEvent::width>( "width" )
			.fun<&PlayerEvent::height>( "height" );
		
		// Event types
		const char* code = R"(
			class KeyEventType {
				static Press=130;
				static Repeat=131;
				static Down=132;
				static Up=133;
				static Input=134;
			};
			class MouseEventType {
				static Over=100;
				static Out=101;
				static Move=102;
				static Click=103;
				static DblClick=104;
				static Down=105;
				static Up=106;
				static ReleaseOutside=107;
				static RightClick=108;
				static RightDblClick=109;
				static RightDown=110;
				static RightUp=111;
				static RightReleaseOutside=112;
				static MiddleClick=113;
				static MiddleDblClick=114;
				static MiddleDown=115;
				static MiddleUp=116;
				static MiddleReleaseOutside=117;
				static Scroll=118;
			};
			class PlayerEventType {
				static Update=10;
				static Render=11;
				static Resize=12;
			};
		)";
		context->eval(code, "<define>", JS_EVAL_TYPE_GLOBAL);

		// Import the module
		const char* import = R"(
			import * as events from 'events';
			globalThis.events = events;
		)";
		context->eval( import, "<import>", JS_EVAL_TYPE_MODULE );
	}

	void Script::bindDisplay() {

		// Create display module
		auto& module = context->addModule( "display" );

		// Dispatcher
		module.class_<Dispatcher>( "Dispatcher" )
			.constructor<>()
			.fun<&Dispatcher::dispatch>( "dispatch" )
			.fun<&Dispatcher::listen>( "listen" )
			.fun<&Dispatcher::remove>( "remove" )
			.fun<&Dispatcher::clear>( "clear" );

		// Display object
		typedef HitArea*( DisplayObject::* DisplayObject_getHitAreaF )( void );
		typedef void( DisplayObject::* DisplayObject_setHitAreaF )( HitArea* );
		module.class_<DisplayObject>( "DisplayObject" )
			.base<Dispatcher>()
			.constructor<>()
			.property<&DisplayObject::parent>( "parent" )
			.property<&DisplayObject::numChildren>( "numChildren" )
			.property<&DisplayObject::first>( "first" )
			.property<&DisplayObject::last>( "last" )
			.property<&DisplayObject::first>( "next" )
			.property<&DisplayObject::last>( "prev" )
			.property<(DisplayObject_getHitAreaF)&DisplayObject::hitArea, (DisplayObject_setHitAreaF)&DisplayObject::hitArea>( "hitArea" )
			.fun<&DisplayObject::x>( "x" )
			.fun<&DisplayObject::y>( "y" )
			.fun<&DisplayObject::width>( "width" )
			.fun<&DisplayObject::height>( "height" )
			.fun<&DisplayObject::scaleX>( "scaleX" )
			.fun<&DisplayObject::scaleY>( "scaleY" )
			.fun<&DisplayObject::rotation>( "rotation" )
			.fun<&DisplayObject::originX>( "originX" )
			.fun<&DisplayObject::originY>( "originY" )
			.fun<&DisplayObject::visible>( "visible" )
			.fun<&DisplayObject::alpha>( "alpha" )
			.fun<&DisplayObject::mouse>( "mouse" )
			.fun<&DisplayObject::addChild>( "addChild" )
			.fun<&DisplayObject::addChildAt>( "addChildAt" )
			.fun<&DisplayObject::removeChild>( "removeChild" )
			.fun<&DisplayObject::removeChildAt>( "removeChildAt" )
			.fun<&DisplayObject::removeAllChildren>( "removeAllChildren" )
			.fun<&DisplayObject::childAt>( "childAt" )
			.fun<&DisplayObject::indexOfChild>( "indexOfChild" )
			.fun<&DisplayObject::addBefore>( "addBefore" )
			.fun<&DisplayObject::addAfter>( "addAfter" )
			.fun<&DisplayObject::remove>( "remove" );

		// Image
		module.class_<Image>("Image")
			.base<DisplayObject>()
			.constructor<string>()
			.property<&Image::loaded>("loaded")
			.property<&Image::width>("width")
			.property<&Image::height>("height");

		// Rive
		module.class_<Rive>( "Rive" )
			.base<DisplayObject>()
			.constructor<string>()
			.property<&Rive::loaded>( "loaded" ) // Get
			.fun<&Rive::play>( "play" );

		const char* import = R"(
			import * as display from 'display';
			globalThis.display = display;
		)";
		context->eval( import, "<import>", JS_EVAL_TYPE_MODULE );
	}

	void Script::bindCore() {

		// Create core module
		auto& module = context->addModule( "core" );

		// Player aka App
		typedef int( Player::* Player_getIntF )( );
		typedef void( Player::* Player_setIntF )( int );
		typedef colorARGB( Player::* Player_getColorARGBF )( );
		typedef void( Player::* Player_setColorARGBF )(colorARGB);
		module.class_<Player>("Player")
			.constructor<int, int, string, bool>()
			.property<&Player::stage>("stage") // Get
			.property<(Player_getIntF)&Player::displayMode, (Player_setIntF)&Player::displayMode>("displayMode")
			.property<(Player_getIntF)&Player::scaleMode, (Player_setIntF)&Player::scaleMode>("scaleMode")
			.property<(Player_getIntF)&Player::alignMode, (Player_setIntF)&Player::alignMode>("alignMode")
			.property<(Player_getColorARGBF)&Player::backgroundColor, (Player_setColorARGBF)&Player::backgroundColor>("backgroundColor")
			.property<(Player_getColorARGBF)&Player::letterboxColor, (Player_setColorARGBF)&Player::letterboxColor>("letterboxColor")
			.fun<&Player::run>("run");

		// Modes
		const char* code = R"(
			class DisplayMode {
				static Cover=0;
				static Contain=1;
				static Letterbox=2;
			};
			class ScaleMode {
				static Exact=0;
				static Pixel=1;
			};
			class AlignMode {
				static Center=0;
				static Top=1;
				static Bottom=2;
				static Left=4;
				static Right=8;
				static LeftTop=5;
				static LeftBottom=6;
				static RightTop=9;
				static RightBottom=10;
			};
		)";
		context->eval( code, "<define>", JS_EVAL_TYPE_GLOBAL );

		// Import
		const char* import = R"(
			import * as core from 'core';
			globalThis.Player = core.Player;
		)";
		context->eval( import, "<import>", JS_EVAL_TYPE_MODULE );
	}

} // ns: derive