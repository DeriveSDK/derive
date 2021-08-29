// Derive
#include "../Script.h"
#include "derive/Player.h"
#include "derive/geom/Point.h"
#include "derive/geom/Bounds.h"
#include "derive/display/Color.h"
#include "derive/display/DisplayObject.h"
#include "derive/display/Image.h"
#include "derive/display/Rive.h"
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
			"import * as os from 'os';
			"globalThis.std = std;
			"globalThis.os = os;
		)";
		context->eval( import, "<import>", JS_EVAL_TYPE_MODULE );
	}

	void Script::bindGeom() {

		// Create display module
		auto& module = context->addModule( "geom" );

		// Point
		typedef double( Point::* Point_getDoubleF )( ) const;
		typedef void( Point::* Point_setDoubleF )( double );
		typedef void ( Point::* Point_voidPointF )( Point* );
		typedef void ( Point::* Point_void2DoubleF )( double, double );
		typedef bool ( Point::* Point_boolPointF )( Point* );
		typedef bool ( Point::* Point_bool2DoubleF )( double, double );
		typedef void ( Point::* Point_voidDoubleF )( double );
		typedef void ( Point::* Point_voidDoublePointF )( double, Point* );
		typedef void ( Point::* Point_void3DoubleF )( double, double, double );
		module.class_<Point>( "Point" )
			.constructor<double, double>()
			.property<(Point_getDoubleF)&Point::x, (Point_setDoubleF)&Point::x>( "x" )
			.property<(Point_getDoubleF)&Point::y, (Point_setDoubleF)&Point::y>( "y" )
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

		const char* import = R"(
			import * as geom from 'geom';
			globalThis.geom = geom;
		)";
		context->eval( import, "<import>", JS_EVAL_TYPE_MODULE );
	}

	void Script::bindDisplay() {

		// Create display module
		auto& module = context->addModule( "display" );

		// Display object
		typedef Point* ( DisplayObject::* Displayobject_pointF )( );
		module.class_<DisplayObject>( "DisplayObject" )
			.constructor<>()
			.property<&DisplayObject::parent>( "parent" )
			.property<&DisplayObject::numChildren>( "numChildren" )
			.property<&DisplayObject::first>( "first" )
			.property<&DisplayObject::last>( "last" )
			.property<&DisplayObject::first>( "next" )
			.property<&DisplayObject::last>( "prev" )
			.property<(Displayobject_pointF)&DisplayObject::cursor>( "cursor" )
			.fun<&DisplayObject::addChild>( "addChild" )
			.fun<&DisplayObject::addChildAt>( "addChildAt" )
			.fun<&DisplayObject::removeChild>( "removeChild" )
			.fun<&DisplayObject::removeChildAt>( "removeChildAt" )
			.fun<&DisplayObject::removeAllChildren>( "removeAllChildren" )
			.fun<&DisplayObject::childAt>( "childAt" )
			.fun<&DisplayObject::indexOfChild>( "indexOfChild" )
			.fun<&DisplayObject::addBefore>( "addBefore" )
			.fun<&DisplayObject::addAfter>( "addAfter" )
			.fun<&DisplayObject::remove>( "remove" )
			.fun<&DisplayObject::dispatch>( "dispatch" );

		// Image
		module.class_<Image>( "Image" )
			.constructor<string>()
			.property<&Image::loaded>( "loaded" )
			.property<&Image::width>( "width" )
			.property<&Image::height>( "height" )
			.fun<&Image::getPixel>( "getPixel" )
			.fun<&Image::setPixel>( "setPixel" );

		// Rive
		module.class_<Rive>( "Rive" )
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
		module.class_<Player>( "Player" )
			.constructor<int, int, string, bool>()
			.property<&Player::stage>( "stage" ) // Get
			.property<(Player_getIntF)&Player::displayMode, (Player_setIntF)&Player::displayMode>( "displayMode" )
			.property<(Player_getIntF)&Player::scaleMode, (Player_setIntF)&Player::scaleMode>( "scaleMode" )
			.property<(Player_getIntF)&Player::alignMode, (Player_setIntF)&Player::alignMode>( "alignMode" )
			.property<(Player_getColorARGBF)&Player::backgroundColor, (Player_setColorARGBF)&Player::backgroundColor>( "backgroundColor" )
			.property<(Player_getColorARGBF)&Player::letterboxColor, (Player_setColorARGBF)&Player::letterboxColor>( "letterboxColor" )
			.fun<&Player::run>( "run" )
			.fun<&Player::update>( "update" );

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
		const char* import = R"(
			import * as core from 'core';
			globalThis.Player = core.Player;
		)";
		context->eval( import, "<import>", JS_EVAL_TYPE_MODULE );
	}

} // ns: derive