:: Start
@echo off
echo.
echo Build all Derive dependencies (debug)
echo.

:: The debug folder
set "libfolder=%~dp0lib\debug\"
echo Lib folder is %libfolder%

:: Ensure library folders exist
echo Check that library folders exist
if not exist "%libfolder%" (
  echo Create debug library folder
  mkdir "%libfolder%"
)

:: Build ThorVG
call build-thorvg.bat debug

:: Build Rive (rive-tizen)
call build-rive.bat debug

:: Build GLEW
call build-glew.bat debug

:: Build GLFW
call build-glfw.bat debug

:: Build QuickJS
call build-quickjs.bat debug

:: Download OpenGL
call build-opengl.bat debug

:: Finish
echo.
echo Derive dependencies complete
echo.
