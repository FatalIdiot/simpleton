#define DEBUG_MODE

#include "engine.hpp"
#include "timer.hpp"

#include "glfw3.h"
#include <iostream>

namespace Simpleton {
    bool InitOpenGL(GLFWwindow*& window, int windowWidth, int windowHeight, char* windowName) {
        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

        #ifdef DEBUG_MODE
        glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, true);
        #endif

        printf("Creating Window...\n");
        window = glfwCreateWindow(windowWidth, windowHeight, windowName, NULL, NULL);
        if (window == NULL)
        {
            printf("Failed to create window!\n");
            glfwTerminate();
            return false;
        }

        printf("Setting current context...\n");
        glfwMakeContextCurrent(window);

        printf("Init GLAD...\n");
        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            printf("Failed to init GLAD!\n");
            glfwTerminate();
            return false;
        }

        glViewport(0, 0, windowWidth, windowHeight);

        return true;
    }

    Engine::Engine(int screenW, int screenH, char* title) {
        printf("Engine Init...\n");
        GLFWwindow* window;
        bool initSuccess = InitOpenGL(window, screenW, screenH, title);
        if(!initSuccess) 
        {
            printf("Failed to init OpenGL!\n");
            m_IsRunning = false;
            return;
        }

        m_Renderer = new Renderer();
        initSuccess = m_Renderer->Init(this, window);
        if(!initSuccess || m_Renderer->m_Window == NULL) 
        {
            printf("Failed to init Window!\n");
            m_IsRunning = false;
            return;
        }

        m_Inputs = new Inputs();
        m_Inputs->Init(this);

        printf("Engine Init done...\n");
        m_IsRunning = true;
    }

    void Engine::Terminate() {
        printf("Engine Terminate...\n");
        m_Renderer->Terminate();
        m_Renderer->m_Window = NULL;
        delete m_Renderer;

        m_Inputs->Terminate();
        delete m_Inputs;
    }

    void Engine::Run(std::function<void(float dt)> Update)  {
        printf("Starting game loop...\n");
        Timer gameLoopTimer;
        gameLoopTimer.Start();
        while(!m_Renderer->WindowShouldClose() && m_IsRunning)
        {
            float deltaT = gameLoopTimer.Elapsed();

            m_Renderer->ClearScreen();

            Update(deltaT);
            
            m_Renderer->SwapBuffers();
            glfwPollEvents();
        }
    }

    Renderer* Engine::GetRenderer() {
        return m_Renderer;
    }

    Inputs* Engine::GetInputs() {
        return m_Inputs;
    }

    void Engine::CaptureCursor(bool setCapture) {
        glfwSetInputMode(m_Renderer->m_Window, GLFW_CURSOR, setCapture ? GLFW_CURSOR_DISABLED : GLFW_CURSOR_NORMAL);
    }

    double Engine::GetTime() {
        return glfwGetTime();
    }

    void Engine::SetTime(double time) {
        glfwSetTime(time);
    }

    void Engine::Stop() {
        m_IsRunning = false;
    }
}