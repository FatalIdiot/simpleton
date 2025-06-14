#include "config.hpp"
#include "engine.hpp"
// #include "../ogl/ogl.h"

#include "glfw3.h"
#include <iostream>

namespace Simpleton {
    Engine::Engine(int screenW, int screenH, char* title) {
        printf("Engine Init...\n");
        bool windowInit = m_Renderer.Init(this, screenW, screenH, title);
        if(!windowInit || m_Renderer.m_Window == NULL) 
        {
            m_IsRunning = false;
        }

        GetConfigs();

        m_Inputs.Init(this);

        printf("Engine Init done...\n");
        m_IsRunning = true;
    }

    void Engine::Terminate() {
        printf("Engine Terminate...\n");
        m_Renderer.Terminate();
        m_Renderer.m_Window = NULL;
    }

    void Engine::Run(std::function<void()> Update)  {
        printf("Starting game loop...\n");
        while(!m_Renderer.WindowShouldClose() && m_IsRunning)
        {
            m_Renderer.ClearScreen();

            Update();

            m_Renderer.SwapBuffers();
            glfwPollEvents();
        }
    }

    Renderer* Engine::GetRenderer() {
        return (&m_Renderer);
    }

    Inputs* Engine::GetInputs() {
        return (&m_Inputs);
    }

    void Engine::CaptureCursor(bool setCapture) {
        glfwSetInputMode(m_Renderer.m_Window, GLFW_CURSOR, setCapture ? GLFW_CURSOR_DISABLED : GLFW_CURSOR_NORMAL);
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