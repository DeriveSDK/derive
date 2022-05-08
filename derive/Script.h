#pragma once

#define JS_STRICT_NAN_BOXING
#define CONFIG_BIGNUM
#define CONFIG_DEBUGGER
#include "quickjspp.hpp"
extern "C" {
#include "quickjs-libc.h"
}
#include "derive/Player.h"
#include <string>

using namespace std;
using namespace derive;

namespace derive {

	class Script {
	protected:
		qjs::Runtime* runtime;
		qjs::Context* context;
		Player* player;

		bool hasUpdate = false;
		bool hasRender = false;
	public:
		Script( string path );
		~Script();

		void bindStd();
		void bindGeom();
		void bindEvents();
		void bindDisplay();
		void bindCore();
	};

} // derive