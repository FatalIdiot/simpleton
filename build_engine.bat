call build_vars.bat

@REM Assuming OpenAL is already built. If not - run 'build_openal'.

@echo ======== Compiling Simpleton
cd simpleton
rmdir /s /q build
mkdir build
rmdir /s /q bin
mkdir bin
cd build
cmake ..

IF %BUILD_MODE% == "DEBUG" (
    cmake --build . --parallel
)
IF %BUILD_MODE% == "RELEASE" (
    cmake --build . --parallel --config Release
)

cd ..

@echo ======== Copy Simpleton files to bin
IF %BUILD_MODE% == "DEBUG" (
    copy "%~dp0simpleton\build\Debug\SIMPLETON_LIB.lib" "%~dp0simpleton\bin"
)
IF %BUILD_MODE% == "RELEASE" (
    copy "%~dp0simpleton\build\Release\SIMPLETON_LIB.lib" "%~dp0simpleton\bin"
)
copy "%~dp0simpleton\vendor\glfw\glfw3.lib" "%~dp0simpleton\bin"
copy "%~dp0simpleton\vendor\OpenAL32.lib" "%~dp0simpleton\bin"
copy "%~dp0simpleton\api.hpp" "%~dp0simpleton\bin"

cd ..