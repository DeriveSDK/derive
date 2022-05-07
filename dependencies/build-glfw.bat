:: Build GLFW3 library
:: This script will download the precompiled GLFW library, build it, and copy it to the lib folder.

:: Start
@echo off
echo.
echo Downloading GLFW
echo.

:: Download subfolder
set "folder=glfw\"

:: Set URLs to download the precompiled binaries
set "filename64=glfw-3.3.7.bin.WIN64"
set "filename32=glfw-3.3.7.bin.WIN32"

set "downloadurl=https://github.com/glfw/glfw/releases/download/3.3.7/"

:: Download src target
set "srclib=lib-vc2019\glfw3_mt.lib"

:: Create download folder
echo Create download folder
if not exist "%folder%" mkdir "%folder%"

:: Detect 32 or 64 bit
echo Detect 64 or 32 bit OS
reg Query "HKLM\Hardware\Description\System\CentralProcessor\0" | find /i "x86" > NUL && set "OSBITS=32BIT" || set "OSBITS=64BIT"
if %OSBITS%==64BIT (
  set "filename=%filename64%"
) else (
  set "filename=%filename32%"
)
set "download=%downloadurl%%filename%.zip"

:: Download and unzip
echo Download files
powershell -Command "Invoke-WebRequest %download% -OutFile %folder%glfw.zip"
echo Unzip files
powershell -Command "Expand-Archive -Path ""%folder%glfw.zip"""

echo Copy library
if "%~1"=="release" (
  set "libfolder=%~dp0lib\release\"
) else (
  set "libfolder=%~dp0lib\debug\"
)
xcopy /y /q "%~dp0%folder%%filename%\%srclib%" "%libfolder%glfw3.lib"

echo Copy header files
if not exist "%folder%include\" mkdir "%folder%include\"
xcopy /e /q /y "%~dp0%folder%%filename%\include" "%~dp0%folder%include"

echo Delete temporary files
del /q "%~dp0%folder%glfw.zip"
rmdir /q /s "%~dp0%folder%%filename%"

:: Done
echo   Downloading GLFW done!
