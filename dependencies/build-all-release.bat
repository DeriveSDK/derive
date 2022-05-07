:: Start
@echo off
echo.
echo Build all Derive dependencies (release)
echo.

:: The release folder
set "libfolder=%~dp0lib\release\"
echo Lib folder is %libfolder%

:: Ensure library folders exist
echo Check that library folders exist
if not exist "%libfolder%" (
  echo Create release library folder
  mkdir "%libfolder%"
)

:: Build ThorVG
call build-thorvg.bat release

:: Build Rive (rive-tizen)
call build-rive.bat release

:: Build GLEW
call build-glew.bat release

:: Build GLFW
call build-glfw.bat release

:: Build QuickJS
call build-quickjs.bat release

:: Download OpenGL
call build-opengl.bat release

:: Finish
echo.
echo Derive dependencies complete
echo.
