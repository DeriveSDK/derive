:: Check for python
where python >nul 2>nul
if not %ERRORLEVEL%==0 (
  echo Error: python not found. Please install python and ensure it is on the path
) else (
    python %~dp0build-assets.py
)
