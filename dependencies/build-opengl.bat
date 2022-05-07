:: Clone OpenGL and EGL registries

:: Start
@echo off
echo.
echo Cloning OpenGL and EGL registries
echo.

:: Repo subfolder
set "folder_opengl=OpenGL-Registry\"
set "folder_egl=EGL-Registry\"

:: Repo URL
set "repo_opengl=https://github.com/KhronosGroup/OpenGL-Registry.git"
set "repo_egl=https://github.com/KhronosGroup/EGL-Registry.git"

:: Ensure we have an up-to-date copy of the OpenGL repo
set gitfolder=%folder_opengl%.git\.
if exist "%gitfolder%" (
  echo Repo already cloned
  echo Pulling latest
  cd "%folder_opengl%"
  git pull
) else (
  echo Cloning repo
  if not exist "%folder_opengl%" mkdir "%folder_opengl%"
  cd "%folder_opengl%"
  git clone "%repo_opengl%" .
)
cd ..

:: Ensure we have an up-to-date copy of the OpenGL repo
set gitfolder=%folder_egl%.git\.
if exist "%gitfolder%" (
  echo Repo already cloned
  echo Pulling latest
  cd "%folder_egl%"
  git pull
) else (
  echo Cloning repo
  if not exist "%folder_egl%" mkdir "%folder_egl%"
  cd "%folder_egl%"
  git clone "%repo_egl%" .
)
cd ..

:: Done
echo   Cloning OpenGL and EGL done!
