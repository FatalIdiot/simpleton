cd simpleton
rmdir /s /q build
rmdir /s /q bin

rmdir /s /q vendor/openal-soft/build
del "%~dp0simpleton\vendor\OpenAL32.lib"

cd ..
del GAME.exe
cd game
rmdir /s /q build
cd ..