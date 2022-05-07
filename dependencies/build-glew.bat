:: Build GLEW library
:: This script will download the GLEW library, build it, and copy it to the lib folder.
:: By default a debug build is generated. Pass in 'release' to generate a release build.
:: Usage:
:: build-glew.bat debug (same as passing in no arguments)
:: build-glew.bat release

:: Start
@echo off
echo.
echo Building GLEW
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
set "folder=glew\"

:: Repo url
set "repo=https://github.com/meson-library/glew.git"

:: Version of GLEW (name of repo branch)
set "version=2.1.0"

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
git checkout %version%

:: Clean previous builds
echo Removing previous build artifacts
rmdir "build" /s /q

:: Configure build
echo Configuring build
:: Pretty sure this is ignored anyway. For some reason this meson build file only support windows and msvc
set "CC=clang-cl"
set "CXX=clang-cl"
meson build
cd build
meson configure -Ddefault_library=static -Dwarning_level=0 -Db_ndebug=if-release 
if "%debug%" == "0" (
  meson configure -Dbuildtype=release -Ddebug=false -Dstrip=true
) else (
  meson configure -Dbuildtype=debugoptimized -Ddebug=true
)

:: Compile
echo Compiling
ninja -C .

:: Copy library to folder
echo Copy library to lib folder
copy /y /b glew_static.lib "%libfolder%glew.lib"

:: Change directory
cd ../..

:: Done
echo   Building GLEW done!
