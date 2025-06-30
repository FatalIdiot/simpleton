#pragma once

#include <functional>
#include <chrono>
#include <vector>

// Events for keys and mouse
#define KEY_EVENT_RELEASE 0
#define KEY_EVENT_PRESS 1
#define KEY_EVENT_REPEAT 2

typedef struct GLFWwindow GLFWwindow;

namespace Simpleton {
    using namespace std::chrono;
    using namespace std::literals::chrono_literals;

    template <typename T>
    struct Point
    {
        T x, y;
    };

    template <typename T>
    struct Color
    {
        T r, g, b, a;
    };

    template <typename T>
    struct Rect 
    {
        T x, y;
        T w, h;
    };

    template <typename T>
    struct Circle
    {
        T x, y;
        T radius;
    };

    class Engine;
    class Renderer;
    class SimpleTexture;
    class Timer;
    class Mesh;
    class Shader;

    class Renderer {
        public:
            GLFWwindow* m_Window;
            void* m_Engine;
            std::function<void(int& width, int& height)> m_ResizeCallback = NULL; // callback functions to customize window resize result

        private:
            unsigned int m_PrimitiveVBO;
            unsigned int m_PrimitiveVAO;
            unsigned int m_PrimitiveShaderProgram;

        public:
            bool Init(void* engine, int windowWidth, int windowHeight, char* windowName);
            void Terminate();

            template <typename T>
            void GetWindowSize(T& width, T& height);

            bool WindowShouldClose(); // return if GLFW window must be closed
            void SetWireframeRendering(bool enable); // enable rendering wireframes
            void SetWindowResizable(bool setResizable);
            void SetClearColor(float r, float g, float b);

            void FillTriangle(Color<float> color, Point<int> pos1, Point<int> pos2, Point<int> pos3);
            void FillRect(Color<float> color, Rect<int> area);
            void FillCircle(Color<float> color, Circle<int> circle, unsigned short pointsCount = 25);

            void ClearScreen();
            void SwapBuffers();
    };

    typedef struct GLFWwindow GLFWwindow;
    class Inputs {
        private:
            Engine* m_Engine = nullptr;
            int m_MouseX = 0, m_MouseY = 0;

        public:
            std::function<void(int button, int action)> OnMouseButton = NULL; // callback for mouse events
            std::function<void(int xpos, int ypos)> OnMouseMove = NULL; // callback for mouse movement
            std::function<void(int key, int scancode, int action)> OnKey = NULL; // callback for keyboard events

        public:
            void Init(Engine* engine);
            void Terminate();

        private:
            static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
            static void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
            static void MousePositionCallback(GLFWwindow* window, double xpos, double ypos);
    };

    class Engine {
         private:
            bool m_IsRunning = false; // game will quit when this is false
            Renderer m_Renderer;
            Inputs m_Inputs;

        public:
            Engine(int screenW, int screenH, char* title, bool enableOglDebug = false); // init engine
            void Terminate(); // kill engine

            void Run(std::function<void(float dt)> Update); // start game loop, lambda function will be called each frame

            Renderer* GetRenderer();
            Inputs* GetInputs();

            void CaptureCursor(bool setCapture); // Hide cursor and cature it inside window
            double GetTime(); // Get time in seconds since engine start
            void SetTime(double time); // Set engine time

            void Stop(); // set m_isRunning to false
    };

    class SimpleTexture {
        public:
            unsigned int m_TextureId;
            int m_Width, m_Height, m_Channels;
            unsigned char* m_Data;

        public:
            SimpleTexture(const char* texturePath, bool flip, bool genMipmaps = true);

            void Bind(unsigned short slot);
            void Unbind();
    };

    class Timer {
        public:
            enum TimerState { Running, Paused, Stopped };

        private:
            time_point<steady_clock> m_StartTime; // start time after creation or Start call
            time_point<steady_clock> m_LastElapsed; // time passed since last Elapsed call
            duration<float> m_PassedTime; // passed time including paused periods
            TimerState m_State; // current state of the timer
            
        public:
            Timer();
            ~Timer();

            void Start();
            void Pause();
            void Clear(); // Stop timer

            float GetPassedTime(); // get time since Start
            float Elapsed(); // get time from last Elapsed call or from timer start

            bool isRunning();
            bool isPaused();
    };

    enum PrimitiveTypes {
        Points,
        Lines,
        LineStrip,
        Triangles,
        TriangleFan
    };

    typedef struct {
        short componentCount;
        unsigned int size;
    } MeshAttribute;

    class Mesh {
        private:
            PrimitiveTypes m_Type;
            unsigned int m_VBO;

            unsigned int m_VAO;
            std::vector<MeshAttribute> m_Attributes; // attributes data is saved for recalculations

            unsigned int m_DataSize;
            unsigned int m_AttribStride;
            PrimitiveTypes m_PrimitiveType;

        public:
            Mesh();
            Mesh(PrimitiveTypes type, const void* data, unsigned int size);
            ~Mesh();

            // Vertex Buffer Object - must be Interleaved data
            void SetBufferData(PrimitiveTypes type, const void* data, unsigned int size);

            // Vertex Array Object
            void SetAttributes(unsigned int* attributes, unsigned int count); // Add all attributes as array
            void AddAttribute(short componentCount); // Add attribute to the list
            void ClearAttributes();
            unsigned int GetAttribCount();
            void EnableAttribute(short index);
            void DisableAttribute(short index);

            void Bind();
            void Unbind();
            void Draw();

            void Terminate();

        private:
            void InitMesh();
    };

    enum ShaderType {
        VertexShader,
        FragmentShader
    };

    class Shader {
        public:
            Shader();
            ~Shader();

            void Terminate();

        private:
            unsigned int m_VertexShader;
            unsigned int m_FragmentShader; 
            unsigned int m_ShaderProgId;
            bool m_IsValid;
            char m_ErrorLog[512];

        public:
            bool CheckShaderValid(ShaderType type);
            bool CheckProgramValid();

            bool AddShaderSource(ShaderType type, const char* code);
            bool AddShaderFile(ShaderType type, const char* filePath);

            bool Compile();

            // set uniforms

            void Bind();
            void Unbind();
    };

    // Get data from 'config.ini' file
    int GetConfigString(char* buffer, int bufferSize, const char* name, const char* sectionName = "Config");
    int GetConfigInt(const char* name, const char* sectionName = "Config");
}