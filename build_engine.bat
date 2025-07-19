call build_vars.bat

@echo ======== Compiling Simpleton
cd simpleton
rmdir /s /q build
mkdir build
rmdir /s /q bin
mkdir bin
cd build
cmake ..

IF %BUILD_MODE% == "DEBUG" (
    cmake --build .
)
IF %BUILD_MODE% == "RELEASE" (
    cmake --build . --config Release
)

@REM cmake --build . --config Release
@REM cmake --build .

cd ..

@echo ======== Copy Simpleton files to bin
copy "%~dp0simpleton\build\Release\SIMPLETON_LIB.lib" "%~dp0simpleton\bin"
@REM copy "%~dp0simpleton\build\Debug\SIMPLETON_LIB.lib" "%~dp0simpleton\bin"
copy "%~dp0simpleton\vendor\glfw\glfw3.lib" "%~dp0simpleton\bin"
copy "%~dp0simpleton\api.hpp" "%~dp0simpleton\bin"

cd ..