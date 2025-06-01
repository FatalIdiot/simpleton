Simpleton is a Windows oriented framework for game development.

# Compilation
### Compile Simpleton
To compile Simpleton run the `build_engine.bat` file.
This will remove previous build files, create and compile a cmake build. After the process is done, it will copy the resulting `SIMPLETON_LIB.lib` static library file, `glfw3.lib` dependancy and the `api.h` header file to the `simpleton/bin` folder.

### Compile Game
To compile Simpleton run the `build_game.bat` file.
This will remove previous build files, create and compile a cmake build.
Cmake uses Simpleton dependancy files from `simpleton/bin`, created when Simpleton is compiled. After cmake is done, the `GAME.exe` executable file will be copied to the root.
To compile, `SIMPLETON_LIB.lib` and `glfw3.lib` static libraries must be linked, and `api.h` must be included to the project.

### All together
Running the `build.bat` file will run both of the above.

# Usage
You can find a demo in the `game` folder.

# Entities
### Engine
### Renderer
### Simple Mesh
### Simple Texture
### Shader

# API
