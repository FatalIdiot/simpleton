call build_vars.bat

@echo ======== Building OpenAL
cd simpleton/vendor/openal-soft
del "%~dp0simpleton\vendor\OpenAL32.lib"
rmdir /s /q build
mkdir build
cd build
cmake -DLIBTYPE=STATIC -DBUILD_SHARED_LIBS=OFF -DALSOFT_UTILS=OFF -DALSOFT_EXAMPLES=OFF -DALSOFT_TESTS=OFF ..

IF %BUILD_MODE% == "DEBUG" (
    cmake --build .
)
IF %BUILD_MODE% == "RELEASE" (
    cmake --build . --config Release
)

@echo ======== Copy the .lib file to 'vendor' root
IF %BUILD_MODE% == "DEBUG" (
    copy "%~dp0simpleton\vendor\openal-soft\build\Debug\OpenAL32.lib" "%~dp0simpleton\vendor"
)
IF %BUILD_MODE% == "RELEASE" (
    copy "%~dp0simpleton\vendor\openal-soft\build\Release\OpenAL32.lib" "%~dp0simpleton\vendor"
)

cd ../../../..