:: Build Rive library from the rive-tizen repo
:: This script will download the rive-tizen library, build it, and copy it to the lib folder.
:: By default a debug build is generated. Pass in 'release' to generate a release build.
:: Usage:
:: build-rive.bat debug (same as passing in no arguments)
:: build-rive.bat release

:: Start
@echo off
echo.
echo Building Rive
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

:: Check that ThorVG is available


:: Repo subfolder
set "folder=rive-tizen\"

:: Repo URL and branch
set "repo=https://github.com/DeriveSDK/rive-tizen.git"
set "branch=update_to_latest_rive"

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

:: Now update submodules
echo Updating submodules
git submodule update --init --recursive

:: Clean previous builds
echo Removing previous build artifacts
rmdir "build" /s /q

:: Configure build
echo Configuring build
set "CXX=clang-cl"
meson build
cd build
meson configure -Ddefault_library=static -Dwarning_level=0 -Db_ndebug=if-release -Db_vscrt=static_from_buildtype
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
copy /y /b src/librive_tizen.a "%libfolder%rive.lib"

:: Change directory
cd ../..

:: Done
echo   Building Rive done!
