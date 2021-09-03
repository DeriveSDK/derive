/**
 * @file main.cpp
 * @author projectitis (peter@projectitis.com)
 * @brief Example usage of Derive
 * @version 0.1
 * @date 2021-08-25
 *
 * @copyright Copyright (c) 2021
 *
 * There are two main ways to use Derive -
 * - Javascript (#define DERIVE_SCRIPT)
 * - Native c++
 *
 * ### Javascript
 * Ensure that DERIVE_SCRIPT is defined.
 * This will build Derive as a player for javascript derive code. By default Derive will look
 * for main.js as the entry point to the application.
 *
 * ### Native c++
 * Ensure that DERIVE_SCRIPT is NOT defined
 * This will build native c++  derive code as an executable. No javascript will be parsed or
 * executed at all.
 */
 //#define DERIVE_SCRIPT

#ifdef DERIVE_SCRIPT
#include "Script.h"
#else
#include "derive/Player.h"
#include "derive/display/Rive.h"
#include "derive/events/MouseEvent.h"
#include "derive/geom/HitAreaCircle.h"
#endif

#include <iostream>

using namespace derive;

#ifdef DERIVE_SCRIPT
/**
 * @brief Derive script entry point
 */
int main( void ) {
	Script* script;
	try {
		script = new Script( "D:\\Projects\\derivesdk\\main.js" );
	}
	catch ( exception e ) { }
	delete script;

	return 0;
}

#else
/**
 * @brief Derive native entry point
 */
class Main : public Player {
public:
	Rive* juice;
	Rive* babyJuice;

	Main() : Player( 1200, 800, "Hello world", false ) {
		scaleMode( ScaleMode::Pixel );
		displayMode( DisplayMode::Contain );
		letterboxColor( 0xff000000 );
		backgroundColor( 0xff662222 );

		juice = new Rive( "juice.riv" );
		//juice->fit( stage()->bounds(), FitMode::Contain );
		juice->scaleX = 0.6;
		juice->scaleY = 0.6;
		juice->originX = juice->width / 2;
		juice->originY = juice->height / 2;
		juice->x = stage()->width / 2;
		juice->y = stage()->height / 2;
		juice->hitArea( new HitAreaCircle(540,540,540) );
		stage()->addChild( juice );

		babyJuice = new Rive( "juice.riv" );
		babyJuice->originX = babyJuice->width / 2;
		babyJuice->originY = babyJuice->height / 2;
		babyJuice->x = 1080;
		babyJuice->y = 0;
		babyJuice->scaleX = 0.3;
		babyJuice->scaleY = 0.3;
		juice->addChild( babyJuice );

		juice->listen( MouseEvent::move, [this](Event* event) -> bool { return this->onMouseMove( event ); } );
	}

	void update( double dt ) {
		juice->rotation += dt * 20;
		babyJuice->rotation += dt * 40;
	}

	bool onMouseMove( Event* event ) {
		cout << "mouse moved" << endl;
		babyJuice->x = juice->mouse->x;
		babyJuice->y = juice->mouse->y;
		return true;
	}
};

int main( void ) {
	try {
		Main main;
		main.run();
	}
	catch ( ... ) { }

	return 0;
}

#endif
