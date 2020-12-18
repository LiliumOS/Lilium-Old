@echo off
WHERE cmake >nul 2>nul
IF %ERRORLEVEL% NEQ 0 (
	echo Error: Could not locate cmake. Please ensure cmake is on the path. 
	pause
	goto :eof
)
@echo on
mkdir build
cd build
cmake -DCMAKE_TOOLCHAIN_FILE=..\cross\toolchain.cmake ..
cmake --build .
