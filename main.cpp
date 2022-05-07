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
#include "derive/Script.h"
#else
#include "derive/Player.h"
#include "derive/display/Rive.h"
#include "derive/display/Image.h"
#include "derive/events/MouseEvent.h"
#include "derive/events/PlayerEvent.h"
#include "derive/geom/HitAreaCircle.h"
#endif

using namespace derive;

#ifdef DERIVE_SCRIPT
/**
 * @brief Derive script entry point
 * DERIVE_SCRIPT currently not supported (work in progress) 
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
	Rive* juice = nullptr;
	Rive* babyJuice = nullptr;
	Image* logo = nullptr;

	Main() : Player( 1200, 800, "Hello world", false ) {
		scaleMode( ScaleMode::Pixel );
		displayMode( DisplayMode::Contain );
		letterboxColor( 0xff000000 );
		backgroundColor( 0xff662222 );
		
		juice = new Rive( "juice.riv" );
		juice->scaleX = 0.6;
		juice->scaleY = 0.6;
		juice->originX = juice->width / 2;
		juice->originY = juice->height / 2;
		juice->x = stage()->width / 2;
		juice->y = stage()->height / 2;
		stage()->addChild( juice );
		
		juice->hitArea(new HitAreaCircle(540, 540, 540));

		babyJuice = new Rive( "juice.riv" );
		babyJuice->originX = babyJuice->width / 2;
		babyJuice->originY = babyJuice->height / 2;
		babyJuice->x = 1080;
		babyJuice->y = 0;
		babyJuice->scaleX = 0.3;
		babyJuice->scaleY = 0.3;
		juice->addChild( babyJuice );

		logo = new Image( "derive-icon.png" );
		logo->originX = logo->width() / 2;
		logo->originY = logo->height() / 2;
		logo->x = 900;
		logo->y = 900;
		juice->addChild( logo );

		juice->listen( MouseEvent::Down, [this](Event* event) -> bool { return this->onMouseClick( event ); } );
		
		stage()->listen( PlayerEvent::Update, [this](Event* event) -> bool { return this->onUpdate( (PlayerEvent*)event ); } );
	}

	~Main() {	
		delete babyJuice;
		delete juice;
		delete logo;
	}

	bool onUpdate( PlayerEvent* event ) {
		juice->rotation += event->dt * 20;
		logo->rotation -= event->dt * 20;
		babyJuice->rotation += event->dt * 40;
		return true;
	}
	
	bool onMouseClick( Event* event ) {
		logo->x = juice->mouse->x;
		logo->y = juice->mouse->y;

		return true;
	}
};

int main( void ) {
	
	Main* main;
	try {
		main = new Main();
		main->run();
	}
	catch ( ... ) { }
	delete main;

	return 0;
}

#endif
