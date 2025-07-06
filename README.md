Simpleton is a framework for game development.

# Contents
**Usage:** <br />
- [Primitives](#primitives)
- [Rendering](#rendering) <br />

**Entities:** <br />
+ [Engine](#engine)
+ [Timer](#timer)
+ [Inputs](#inputs)
+ [Renderer](#renderer)
+ [Mesh](#mesh)
+ [Shader](#shader)
+ [Shader Uniform Manager](#shader-uniform-manager)<br />

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

**Methods:**
- `Run(std::function<void(float dt)> Update)` - defines the game loop
- `GetRenderer()` - returns a pointer to the Renderer instance
- `GetInputs()` - returns a pointer to the Inputs instance
- `CaptureCursor(bool setCapture)` - captures the cursor inside the window
- `GetTime()` - returns a `double` of time in seconds
- `SetTime(double time)` - set the time in seconds
- `Stop()` - stops the engine

Engine entity instance must be created and initialized before usage. It is done by calling `Simpleton::Engine engine(*WINDOW WIDTH*, *WINDOW HEIGHT*, "*WINDOW NAME*");`<br />
Game loop is defined int the `Run` method:
```
    engine.Run([](float dt) {
        *GAME CODE HERE*
    });
```
Game cursor can be captured inside the window using `CaptureCursor(*BOOLEAN IF THE CURSOR MUST BE CAPTURED*)`.<br />
Along with the `Timer` class, engine also tracs of the time since it was initialized using `GetTime`, or the time can be set using `SetTime(double TIME)`. Time is measured as `double` is seconds.<br />
To stop the game loop, call `Stop` method. <br />
When quiting the game, `Terminate` method must be called.<br />

### Timer

**Methods:**
- `Start()` - starts the timer
- `Pause()` - pauses the timer
- `Stop()` - stops the timer
- `GetPassedTime()` - returns a `float` of time in seconds that passed since Start without pauses
- `Elapsed()` - return time since last pause or start, with paused time
- `isRunning()` - check if the timer is running
- `isPaused()` - check if the timer is paused

Timer allows to take time measurements. It has the following functions: <br />
`Start` - starts the timer if it is new or paused. <br />
`Pause` - to pause the timer. Time before the pause will be saved, so the timer can be paused and started multiple times with the ability to get total time passed without the time it was paused. <br />
`Clear` - resets the timer, clearing passed time measurements and setting it as stopped. <br />
`GetPassedTime` - get total time passed while timer was running and not paused. <br />
`Elapsed` - get time from timer start or from the last Elapsed call. Timer must be running and not be paused for this. Returns `0.0f` as default. <br />

### Inputs

### Renderer

**Methods:**
- `GetWindowSize(T& width, T& height)` - template function, that returns screen size
- `WindowShouldClose()` - returns `bool` that is true if the window must be closed, if so - breaks the engine game loop
- `SetWireframeRendering(bool enable)` - if enabled, OpenGL will render the wireframe, instead of primitives and models
- `SetWindowResizable(bool setResizable)` - toogles if the window should be resizable or not
- `SetClearColor(float r, float g, float b)` - at the beginning of each frame, the screen is cleared with this color
- `FillTriangle(Color<float> color, Point<int> pos1, Point<int> pos2, Point<int> pos3)`
- `FillRect(Color<float> color, Rect<int> area)`
- `FillCircle(Color<float> color, Circle<int> circle, unsigned short pointsCount = 25)`

Renderer class is an abstraction above OpenGL, that is set to allow drawing primitives, textures and models.<br />
When using Simpleton, you can get the Renderer instance from the Engine object: `engine.GetRenderer()`, this will give a Renderer pointer.<br />
**Rendering:** <br />
Primitives are rendered using the following methods: <br />
`FillTriangle`, `FillRect`, `FillCircle`. All of them take a `Color` as the first parameter, and then relevant data of the primitive. For circle rendering, the number of points that form the circle may be specified, default value, if nothing is specified, is `25`. <br />

### Mesh

**Methods:**
- `SetBufferData(unsigned int type, const void* data, unsigned int size)`
- `SetAttributes(MeshAttribute attributes[], unsigned int count)`
- `AddAttribute(MeshAttribute newAttribute)`
- `ClearAttributes()`
- `GetAttribCount()`
- `EnableAttribute(short index)` | `DisableAttribute(short index)`
- `Bind()` | `Unbind()`
- `Draw()`

Provides a class to work with OpenGL Vertex Array and Vertex Buffer Objects. <br />
It uses the `MeshAttribute` struct to contain attribute's `type`, `count` and `normalized` values. <br />

> [!TIP]
> This class is used to abstract away OpenGL rendering for the engine, but also can be used directly in game code. For this you must understand how OpenGL VBOs and VAOs work, the data structure must be Interleaved.

When instanced, an OpenGL type of primitive must be specified. Available types are `GL_POINTS`, `GL_LINES`, `GL_LINE_STRIP`, `GL_TRIANGLES` and `GL_TRIANGLE_FAN`. <br />
![OpenGL draw modes](https://people.eecs.ku.edu/~jrmiller/Courses/OpenGL/resources/drawArrayModes_WithEdgesAndVertices.png)
Data is set by calling the `SetBufferData` method, and attributes can be specified by calling `SetAttributes` of added one by one with `AddAttribute`. <br />
```
    Mesh testMesh;
    float verts[] = {
        -0.5f, 0.5f,
        0.0f, 0.0f,
        0.5f, 0.5f
    }; 
    testMesh.SetBufferData(PrimitiveTypes::Triangles, verts, sizeof(verts));
    MeshAttribute attributes[] = {
            { GL_FLOAT, 2, true }
        };
    testMesh.SetAttributes(attributes, 1);
    testMesh.Draw();
```

### Shader

**Methods:**
- `CheckProgramValid()`
- `AddShaderSource(ShaderType type, const char* code)`
- `AddShaderFile(ShaderType type, const char* filePath)`
- `Compile()`
- `SetUniform(const char* name, float x, float y, float z, float w)`
- `Bind()` | `Unbind()`

Provides a class to work with OpenGL shaders and shader programs. <br />
Shader class includes functionality to compile a vertex and fragment shader and compile it into a shader program.<br />
To use it you create a Shader instance: `Shader exampleShader`. Then you pass source code for both shaders either from file or by directly providing code:
```
exampleShader.AddShaderFile(ShaderType::VertexShader, "file/path");
exampleShader.AddShaderFile(ShaderType::FragmentShader, "file/path");

// or

exampleShader.AddShaderSource(ShaderType::VertexShader, "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0");
exampleShader.AddShaderSource(ShaderType::FragmentShader, "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "    FragColor = vec4(1.0, 1.0, 1.0, 1.0);\n"
    "}\0");
```
Aftere the source been provided, the shader program is compiled by calling `Compile()`.<br />
Before the draw call you bind the program with `Bind()`, and `Unbind()` it after it's done.<br />
Uniforms are provided into the program with following functions:
```
void SetUniform(const char* name, float x, float y, float z, float w);
```
<br />
Shaders have global uniforms, that are passed to them before drawing by the engine. These are: <br />
`screenSize` - two `int` values that return screen width (`screenSize.x`) and screen height (`screenSize.y`). <br />

> [!TIP]
> These values are set by the static method `SetData` of the static `ShaderUniformManager` class when the `Draw` method of `Mesh` is called.

### Shader Uniform Manager

**Methods:**
- `SetEngine(Engine* engine)`
- `SetData()`

> [!WARNING]
> This class and all it's methods are static.

This class controls uniforms, that must be present in all shaders. It is a static class, that has a pointer to the Engine, since multiple Engine instances may be used in the code. The pointer is set with `SetEngine` static method, that is called in the Engine constructor. It can be called from game's code if needed. <br />
It works by calling the `SetData` static method inside the `Mesh.Draw()`, to pass data right before a draw call. The data is set for the currently active shader program. The `SetData` method is public and can be called at any place if needed. <br />