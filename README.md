Simpleton is a Windows oriented framework for game development.

# Compilation
### Compile Simpleton
To compile Simpleton run the `build_engine.bat` file.
This will remove previous build files, create and compile a cmake build. After the process is done, it will copy the resulting `SIMPLETON_LIB.lib` static library file, `glfw3.lib` dependancy and the `api.h` header file to the `simpleton/bin` folder.

### Compile Demo Game
To compile the demo run the `build_game.bat` file.
This will remove previous build files, create and compile a cmake build.
Cmake uses Simpleton dependancy files from `simpleton/bin`, created when Simpleton is compiled. After cmake is done, the `GAME.exe` executable file will be copied to the root.
To compile, `SIMPLETON_LIB.lib` and `glfw3.lib` static libraries must be linked, and `api.h` must be included to the project. All of this is automatically done for the demo project.

### All together
Running the `build.bat` file will run both of the above.

### Cleaning
To delete all the buid data run the `clear.bat` file.

# Usage
You can find a demo in the `game` folder.

### Primitives
Engine uses a number of primitive structs:<br />
`Point` - has `x` and `y` members.<br />
`Color` - has `r`, `g`, `b`, and `a` members.<br />
`Rect` - has `x` and `y` to represent top-left corner of a rectangle, `w` and `h` to represent width and height.<br />
`Circle` = has `x`, `y` and `radius` fields.<br />
All structs are templates and their fields may be any type.<br />

### Rendering
You can draw primitives with functions found in the Renderer of the engine. To do this, get the Renderer pointer in the engine instance: `engine.GetRenderer()`.
```
void FillTriangle(Color color, Point pos1, Point pos2, Point pos3);
void FillRect(Color color, Rect area);
void FillCircle(Color<float> color, Circle<int> circle, unsigned short pointsCount = 25);
```
For `FillCircle` you can specify the number of points that will form the circle, default is `25`.<br />

# Entities
### Engine
### Renderer
### Simple Mesh
### Simple Texture
### Shader
### Timer

### Mesh
Provides a class to work with OpenGL Vertex Array and Vertex Buffer Objects. <br />
When instanced, a type of primitive must be specified. Available types are `Points`, `Lines`, `LineStrip`, `Triangles` and `TriangleFan`. <br />
Data is set by calling the `SetBufferData` method, and attributes can be specified by calling `SetAttributes` of added one by one with `AddAttribute`. <br />
```
    Mesh testMesh;
    float verts[] = {
        -0.5f, 0.5f, 0.0f,
        0.0f, 0.0f, 0.0f,
        0.5f, 0.5f, 0.0f
    }; 
    testMesh.SetBufferData(PrimitiveTypes::Triangles, verts, sizeof(verts));
    unsigned int attributes[] = { 3 };
    testMesh.SetAttributes(attributes, 1);
    testMesh.Draw();
```

# API
