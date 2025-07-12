#pragma once

#include <functional>
#include <chrono>
#include <vector>
#include <map>
#include <string>

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

    


    typedef struct {
        unsigned int type; // OpenGL type of data
        unsigned int count;
        bool normalized;
    } MeshAttribute;

    class Mesh {
        private:
            unsigned int m_Type;
            unsigned int m_VBO;

            unsigned int m_VAO;
            std::vector<MeshAttribute> m_Attributes; // attributes data is saved for recalculations

            unsigned int m_EBO;

            unsigned int m_DataSize;
            unsigned int m_IndexCount;
            unsigned int m_AttribStride;

        public:
            Mesh();
            Mesh(unsigned int type, const void* data, unsigned int size);
            ~Mesh();

            // Vertex Buffer Object - must be Interleaved data
            void SetBufferData(unsigned int type, const void* data, unsigned int size);

            // Vertex Array Object
            void SetAttributes(MeshAttribute attributes[], short count); // Add all attributes as array
            void AddAttribute(MeshAttribute newAttribute); // Add attribute to the list
            void ClearAttributes();
            unsigned int GetAttribCount();
            void EnableAttribute(short index);
            void DisableAttribute(short index);

            // Element Buffer Object
            void SetIndexData(unsigned int* data, unsigned int count);
            void RemoveIndexData();

            void Bind();
            void Draw();

        private:
            void InitMesh();
            static unsigned int GetTypeSize(unsigned int type);
            void Terminate();
    };

    enum ShaderType {
        VertexShader,
        FragmentShader
    };

    class Shader {
        private:
            unsigned int m_VertexShader;
            unsigned int m_FragmentShader; 
            unsigned int m_ShaderProgId;
            bool m_IsValid;
            char m_ErrorLog[512];

        public:
            Shader();
            ~Shader();

            bool CheckProgramValid();

            bool AddShaderSource(ShaderType type, const char* code);
            bool AddShaderFile(ShaderType type, const char* filePath);

            bool Compile();

            // set uniforms
            void SetUniform(const char* name, float x, float y, float z, float w);
            void SetUniform(const char* name, int i);

            void Bind();
            void Unbind();

        private:
            bool CheckShaderValid(ShaderType type);
            void Terminate();
    };

    enum TextureLoadType {
        File,
        Data
    };

    enum TextureFiltering {
        Nearest,
        Linear
    };

    class Texture {
        private:
            unsigned char m_Slot;
            int m_FilteringMode;

            unsigned int m_TextureId;
            TextureLoadType m_LoadType;

            int m_Width, m_Height, m_ChannelsCount;
            unsigned char *m_Data;

            bool m_isLoaded;

        public:
            Texture(unsigned char slot = 0);
            Texture(const char* filePath, unsigned char slot = 0);
            Texture(int width, int height, int channelsCount, unsigned char* data, unsigned char slot = 0);
            ~Texture();

            unsigned int GetId();
            bool IsLoaded();
            void SetSlot(unsigned char slot);

            bool LoadFile(const char* filePath);
            bool LoadData(int width, int height, int channelsCount, unsigned char* data);

            void Bind();
            void Unbind();

            void SetFiltering(TextureFiltering filteringMode);

        private:
            void Init(unsigned char slot);
            void GeneralLoad();
    };

    class ResourceManager {
        friend class Engine; 

        private:
            std::map<std::string, Texture*> m_Textures;

        public:
            Texture* GetTexture(const char* name);
            void AddTexture(const char* name, Texture* texture);
            void AddTexture(const char* name, const char* filePath, unsigned char slot = 0);
            void AddTexture(const char* name, int width, int height, int channelsCount, unsigned char* data, unsigned char slot = 0);
    
        private:
            void Init();
            void Terminate();
    };

    class Renderer {
        friend class Engine; 
        
        public:
            GLFWwindow* m_Window;
            void* m_Engine;
            std::function<void(int& width, int& height)> m_ResizeCallback = NULL; // callback functions to customize window resize result

        private:
            Mesh m_PrimitiveMesh;
            Shader m_PrimitiveShader;
            Shader m_TextureShader;

        public:
            template <typename T>
            void GetWindowSize(T& width, T& height);

            bool WindowShouldClose(); // return if GLFW window must be closed
            void SetWireframeRendering(bool enable); // enable rendering wireframes
            void SetWindowResizable(bool setResizable);
            void SetClearColor(float r, float g, float b);
            void DepthTest(bool enable);

            void FillTriangle(Color<float> color, Point<int> pos1, Point<int> pos2, Point<int> pos3);
            void FillRect(Color<float> color, Rect<int> area);
            void FillCircle(Color<float> color, Circle<int> circle, unsigned short pointsCount = 25);

            void DrawLine(Color<float> color, Point<int> pointA, Point<int> pointB);
            void DrawTriangle(Color<float> color, Point<int> pos1, Point<int> pos2, Point<int> pos3);
            void DrawRect(Color<float> color, Rect<int> area);
            void DrawCircle(Color<float> color, Circle<int> circle, unsigned short pointsCount = 25);
            
            void BlitTexture(Texture* texture, Rect<int> destRect, Rect<float> srcRect = {0.0f, 0.0f, 1.0f, 1.0f});

        private:
            bool Init(void* engine, GLFWwindow* window);
            void Terminate();
            void ClearScreen();
            void SwapBuffers();
    };

    class Inputs {
        friend class Engine; 

        private:
            Engine* m_Engine = nullptr;
            int m_MouseX = 0, m_MouseY = 0;

        public:
            std::function<void(int button, int action)> OnMouseButton = NULL; // callback for mouse events
            std::function<void(int xpos, int ypos)> OnMouseMove = NULL; // callback for mouse movement
            std::function<void(int key, int scancode, int action)> OnKey = NULL; // callback for keyboard events

        public:
            void Init(Engine* engine);

        private:
            static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
            static void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
            static void MousePositionCallback(GLFWwindow* window, double xpos, double ypos);
            void Terminate();
    };

    enum EngineFlags : unsigned int {
        EnableOglDebug = 1 << 0
    };

    class Engine {
        private:
            bool m_IsRunning = false; // game will quit when this is false
            Renderer* m_Renderer;
            Inputs* m_Inputs;
            ResourceManager* m_Library;

        public:
            Engine(int screenW, int screenH, char* title, unsigned int flags = 0); // init engine
            ~Engine(); // kill engine in destructor
            void Terminate(); // manually kill engine

            void Run(std::function<void(float dt)> Update); // start game loop, lambda function will be called each frame

            Renderer* GetRenderer();
            Inputs* GetInputs();
            ResourceManager* GetLibrary();

            void CaptureCursor(bool setCapture); // Hide cursor and cature it inside window
            double GetTime(); // Get time in seconds since engine start
            void SetTime(double time); // Set engine time
            
            void Stop(); // set m_isRunning to false
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

    class ShaderUniformManager {
        private:
            static Engine* m_Engine;

        private:
            ShaderUniformManager() = delete;

        public:
            // Sets engine pointer to get data from.
            // This is because there might be multiple instances of Engine.
            static void SetEngine(Engine* engine);

            // Sets global uniforms to the current shader program.
            static void SetData();
    };
}