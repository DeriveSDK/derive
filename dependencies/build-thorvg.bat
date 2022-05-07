:: Build ThorVG library
:: This script will download the ThorVG library, build it, and copy it to the lib folder.
:: By default a debug build is generated. Pass in 'release' to generate a release build.
:: Usage:
:: build-thorvg.bat debug (same as passing in no arguments)
:: build-thorvg.bat release

:: Start
@echo off
echo.
echo Building ThorVG
echo.

:: Check for meson
where meson >nul 2>nul
if not %ERRORLEVEL%==0 (
  echo Error: meson not found. Please install the meson build system (mesonbuild.com)
  ::goto :eof
)

:: Check for ninja
where ninja >nul 2>nul
if not %ERRORLEVEL%==0 (
  echo Error: ninja not found. Please install the ninja build system (ninja-build.org)
  ::goto :eof
)

:: Repo subfolder
set "folder=thorvg\"

:: Repo URL and branch
set "repo=https://github.com/DeriveSDK/thorvg.git"
set "branch=master"

:: Check if we are building release or debug (default)
set "debug=1"
if "%~1"=="release" (
  set "debug=0"
  echo Release build
  set "libfolder=%~dp0lib\release\"
) else (
  echo Debug build
  set "libfolder=%~dp0lib\debug\"
)

:: First ensure we have an up-to-date copy of the repo
set gitfolder=%folder%.git\.
if exist "%gitfolder%" (
  echo Repo already cloned
  echo Pulling latest
  cd "%folder%"
  git pull
) else (
  echo Cloning repo
  if not exist "%folder%" mkdir "%folder%"
  cd "%folder%"
  git clone "%repo%" .
)
git checkout "%branch%"
cd "%folder%"

:: Clean previous builds
echo Removing previous build artifacts
rmdir "build" /s /q

:: Configure build
echo Configuring build
set "CXX=clang-cl"
meson build
cd build
meson configure -Ddefault_library=static -Db_vscrt=static_from_buildtype -Dwarning_level=0 -Dloaders=svg,png,jpg -Dlog=false -Dsavers=[] -Dstatic=true -Db_ndebug=if-release
if "%debug%" == "0" (
  meson configure -Dbuildtype=release -Ddebug=false
) else (
  meson configure -Dbuildtype=debug -Ddebug=true
)

:: Compile
echo Compiling
ninja -C .

:: Copy library to folder
echo Copy library to lib folder
copy /y /b src/libthorvg.a "%libfolder%thorvg.lib"

:: Change directory
cd ../..

:: Done
echo   Building ThorVG done!
