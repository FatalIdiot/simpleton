#pragma once

#include <functional>
#include <chrono>

// Events for keys and mouse
#define KEY_EVENT_RELEASE 0
#define KEY_EVENT_PRESS 1
#define KEY_EVENT_REPEAT 2

typedef struct GLFWwindow GLFWwindow;

namespace Simpleton {
    using namespace std::chrono;
    using namespace std::literals::chrono_literals;

    typedef struct Point
    {
        int x;
        int y;
    } Point;

    typedef struct Color 
    {
        float r, g, b, a;
    } Color;

    typedef struct Rect 
    {
        int x, y;
        int w, h;
    } Rect;

    class Engine;
    class Renderer;
    class SimpleTexture;
    class SimpleShader;
    class SimpleMesh;
    class Timer;

    class Renderer {
        public:
            GLFWwindow* m_Window;
            void* m_Engine;
            std::function<void(int& width, int& height)> m_ResizeCallback = NULL; // callback functions to customize window resize result

        public:
            bool Init(void* engine, int windowWidth, int windowHeight, char* windowName);
            void Terminate();

            void GetWindowSize(int& width, int& height);

            bool WindowShouldClose(); // return if GLFW window must be closed
            void SetWireframeRendering(bool enable); // enable rendering wireframes
            void SetWindowResizable(bool setResizable);
            void SetClearColor(float r, float g, float b);

            void FillRect(Color color, Rect area); // render color to area on screen
            void DrawTexture(Rect area, SimpleTexture* texture); // draw texture to area on screen

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
            Engine(int screenW, int screenH, char* title); // init engine
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

    class SimpleShader {
        private:
            unsigned int m_ShaderProgId;

        public:
            SimpleShader();
            SimpleShader(const char* vartexShader, const char* fragmentShader);

            void SetUniform1i(const char* name, int i);
            void SetUniform4f(const char* name, float x, float y, float z, float w);
            void SetUniformMatrix4fv(const char* name, const float* value, const bool transpose);

            bool CompileShader(const char* vartexShader, const char* fragmentShader);
            void Use();
    };

    class SimpleMesh {
        private:
            unsigned int m_VAO, m_VBO, m_EBO;
            unsigned int m_vertSize, m_indSize;

        public:
            SimpleMesh(float* vertices, int vertSize, int* indices, int indSize);
            void Terminate();

            void Bind();
            void Unbind();

            void VertexAttrib(unsigned int index, int size, int stride, const void* offset);
            void Draw();
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

    // Get data from 'config.ini' file
    int GetConfigString(char* buffer, int bufferSize, const char* name, const char* sectionName = "Config");
    int GetConfigInt(const char* name, const char* sectionName = "Config");
}