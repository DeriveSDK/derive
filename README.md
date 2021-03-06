# Derive

![Derive icon](/icon.png "Derive")

## Status

**Important:** Derive is pre-alpha. It is not yet production-ready, so please only use it for evaluation purposes. Major parts of the code may (and will) change without warning or backwards compatibility until the project reaches alpha.

## What is derive?

Derive is a flash-like cross-platform SDK and tool set for developing games. Derive was designed with Rive vector animations in mind, but of course you can also use Derive to make pixel-based games, include raster images, text, audio and more (and mix all of these!).

Derive uses the Rive c++ runtime and is rendered with ThorVG. QuickJS is used for javascript scripting support.

## License
Derive is distributed under the [MIT](https://opensource.org/licenses/MIT) license (free for commercial and personal use). The dependencies use a variety of licenses, but are all compatible with the MIT license.

## Usage

There are two main ways to use derive - either develop a native C++ application using it, or write your entire game in JavaScript (and compile it to an executable). 

## Native C++

Include the derive code in your project and extend from the Player class. Example:
```
#include "Player.h"
#include "display/Rive.h"

class Main : public Player {
public:
	Rive* juice;

	Main() : Player( 800, 800, "Application name", false ) {
		juice = new derive::display::Rive( "juice.riv" );
		juice->fit( stage()->bounds(), FitMode::Contain );
		stage()->addChild( juice );
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
````

## Javascript (currently disabled - work in progress)
Write your code in JavaScript and launch the Derive debugger tool to run it. When you are happy, compile your JavaScript code to a standalone executable with qjsc (the QuickJS compiler). Example:

````
class Main extends Player {
	juice;

	constructor() {
		super(800, 880, "Hello world", false);

		this.juice = new display.Rive("juice.riv");
		this.juice.fit(this.stage.bounds, FitMode.Contain);
		this.stage.addChild(this.juice);
	}
}
main = new Main();
main.run();
````

## Build instructions

Currently derive is supported on windows only. It uses a combination of MSVC and Clang-cl, and the meson build system (for dependencies).

Make sure you have the following installed:
* [Visual Studio](https://docs.microsoft.com/en-us/visualstudio/install/install-visual-studio)
* [LLVM Visual Studio extension](https://docs.microsoft.com/en-us/cpp/build/clang-support-msbuild)
* [Python](https://www.python.org/downloads/)
* [Meson](https://mesonbuild.com/Getting-meson.html) and [Ninja](https://ninja-build.org/)

Tip: We recommend installing python, meson and ninja by using the [chocolatey](https://chocolatey.org/install) package manager.

To get Derive running:
* Clone this repository (for example, to `C:\projects\derive`)
* Open the native command prompt for Visual Studio ([hit windows search and start typing "native command prompt"](https://stackoverflow.com/questions/61209155/how-do-i-get-the-x64-native-tools-developer-command-prompt-for-visual-studio-com))
* Change directory to the `dependencies` folder.
  * For example, `cd C:\projects\derive\dependencies`
* Build the dependencies by running the following two scripts:
  * `build-all-debug.bat`
  * `build-all-release.bat`
* Now, open the solution in Visual Studio and hit build!
  * Example, open `C:\projects\derive\solution\Derive.sln`

## Dependencies

Derive would not be possible without the fantastic work of others. Derive requires:

* [Rive-CPP](https://rive.app/). By Luigi Rosso and Guido Rosso. C++ Runtime for the Rive animation format. [MIT](https://opensource.org/licenses/MIT) license.
* [ThorVG](https://thorvg.org/). By the ThorVG team. Open-source vector graphics engine. [MIT](https://opensource.org/licenses/MIT) license.
* [QuickJS](https://bellard.org/quickjs/). By Fabrice Bellard. ES2020 JavaScript engine for scripting. [MIT](https://opensource.org/licenses/MIT) license.
* [quickjspp](https://github.com/ftk/quickjspp). By FTK. C++ wrapper for QuickJS. [COO](https://creativecommons.org/publicdomain/zero/1.0/) license.
* [GLFW](https://www.glfw.org/). By Marcus Geelnard and Camilla L??wy. For window and events. [ZLIB](https://opensource.org/licenses/Zlib) license.

The Derive repository will, over time, attempt to provide a pre-compiled static library for the main platforms, but in the meantime these dependencies need to be compiled for your target platform.
