#include "engine.hpp"
#include "timer.hpp"
#include "graphics/shaderUniformManager.hpp"
#include "logger.hpp"

#include "glfw3.h"
#include <iostream>

namespace Simpleton {
    void GLAPIENTRY MessageCallback(GLenum source, GLenum type, GLuint id, GLenum severity,
        GLsizei length, const GLchar *message, const void *userParam)
    {
        LogErr("OGL Debug: {}", message);
    }

    bool InitOpenGL(GLFWwindow*& window, int windowWidth, int windowHeight, char* windowName, unsigned int flags) {
        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

        if(flags & EngineFlags::EnableOglDebug)
            glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, true);

        LogMsg("Creating Window...");
        window = glfwCreateWindow(windowWidth, windowHeight, windowName, NULL, NULL);
        if (window == NULL)
        {
            LogErr("Failed to create window!");
            glfwTerminate();
            return false;
        }

        LogMsg("Setting current context...");
        glfwMakeContextCurrent(window);

        LogMsg("Init GLAD...");
        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            LogErr("Failed to init GLAD!");
            glfwTerminate();
            return false;
        }

        if(flags & EngineFlags::EnableOglDebug) {
            LogMsg("OpenGL debuging enabled.");
            
            glEnable(GL_DEBUG_OUTPUT);
            glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
            glDebugMessageCallback(MessageCallback, nullptr);
            glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);
        }

        glViewport(0, 0, windowWidth, windowHeight);

        return true;
    }

    Engine::Engine(int screenW, int screenH, char* title, unsigned int flags) {
        Log::Init();
        LogMsg("Engine Init...");
        GLFWwindow* window;
        bool initSuccess = InitOpenGL(window, screenW, screenH, title, flags);
        if(!initSuccess) 
        {
            LogErr("Failed to init OpenGL!");
            m_IsRunning = false;
            return;
        }

        m_Renderer = new Renderer();
        initSuccess = m_Renderer->Init(this, window);
        if(!initSuccess || m_Renderer->m_Window == NULL) 
        {
            LogErr("Failed to init Window!");
            m_IsRunning = false;
            return;
        }

        m_Inputs = new InputsManager();
        m_Inputs->Init(this);

        m_Audio = new AudioManager();
        m_Audio->Init(this);

        m_Library = new ResourceManager();
        m_Library->Init();

        ShaderUniformManager::SetEngine(this);

        LogMsg("Engine Init done...");
        m_IsRunning = true;
    }

    Engine::~Engine() {
        Terminate();
    }

    void Engine::Terminate() {
        LogMsg("Engine Terminate...");
        m_Renderer->Terminate();
        m_Renderer->m_Window = NULL;
        delete m_Renderer;

        m_Inputs->Terminate();
        delete m_Inputs;

        m_Library->Terminate();
        delete m_Library;

        m_Audio->Terminate();
        delete m_Audio;

        Log::Terminate();
    }

    void Engine::Run(std::function<void(float dt)> Update)  {
        LogMsg("Starting game loop...");

        Timer gameLoopTimer;
        gameLoopTimer.Start();
        while(!m_Renderer->WindowShouldClose() && m_IsRunning)
        {
            float deltaT = gameLoopTimer.Elapsed();

            m_Renderer->ClearScreen();

            Update(deltaT);
            
            m_Renderer->SwapBuffers();
            glfwPollEvents();
            m_Inputs->PollInputEvents();
        }

        LogMsg("Out of game loop...");
    }

    Renderer* Engine::GetRenderer() const {
        return m_Renderer;
    }

    InputsManager* Engine::GetInputs() const {
        return m_Inputs;
    }

    ResourceManager* Engine::GetLibrary() const {
        return m_Library;
    }

    AudioManager* Engine::GetAudio() const {
        return m_Audio;
    }

    void Engine::CaptureCursor(bool setCapture) {
        glfwSetInputMode(m_Renderer->m_Window, GLFW_CURSOR, setCapture ? GLFW_CURSOR_DISABLED : GLFW_CURSOR_NORMAL);
    }

    double Engine::GetTime() const {
        return glfwGetTime();
    }

    void Engine::SetTime(double time) {
        glfwSetTime(time);
    }

    void Engine::Stop() {
        m_IsRunning = false;
    }
}