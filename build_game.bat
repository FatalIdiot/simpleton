call build_vars.bat

@echo ======== Compiling Game
del GAME.exe
cd game
rmdir /s /q build
mkdir build
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

cd ../..

@echo ======== Copy Simpleton files to root
set assetsSource=%~dp0game\build\Release\GAME.exe
@REM set assetsSource=%~dp0game\build\Debug\GAME.exe
set assetsDestinationPath=%~dp0
xcopy "%assetsSource%" "%assetsDestinationPath%" /E /H /C /I /Y
