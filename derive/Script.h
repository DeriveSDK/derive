#pragma once

#define JS_STRICT_NAN_BOXING
#define CONFIG_BIGNUM
#define CONFIG_JSX
#define CONFIG_STORAGE
#define CONFIG_DEBUG
#define QUICKJSPP_BASECLASS
#include "quickjspp.hpp"
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