call build_vars.bat

@echo ======== Compiling Game
del GAME.exe
cd game
rmdir /s /q build
mkdir build
cd build
cmake ..

IF %BUILD_MODE% == "DEBUG" (
    cmake --build . --parallel
)
IF %BUILD_MODE% == "RELEASE" (
    cmake --build . --parallel --config Release
)

cd ../..

@echo ======== Copy game .exe to root
IF %BUILD_MODE% == "DEBUG" (
    set assetsSource=%~dp0game\build\Debug\GAME.exe
)
IF %BUILD_MODE% == "RELEASE" (
    set assetsSource=%~dp0game\build\Release\GAME.exe
)
set assetsDestinationPath=%~dp0
xcopy "%assetsSource%" "%assetsDestinationPath%" /E /H /C /I /Y
