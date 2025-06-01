#include "inputs.hpp"
#include "engine.hpp"

#include <iostream>

namespace Simpleton {
    void Inputs::Init(Engine* engine) {
        printf("Init Inputs...\n");
        m_Engine = engine;

        glfwSetKeyCallback(engine->GetRenderer()->m_Window, KeyCallback);
        glfwSetMouseButtonCallback(engine->GetRenderer()->m_Window, MouseButtonCallback);
        glfwSetCursorPosCallback(engine->GetRenderer()->m_Window, MousePositionCallback);
    }

    void Inputs::Terminate() {
        printf("Inputs Terminate...\n");
    }

    void Inputs::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
        Inputs* inputs = reinterpret_cast<Engine*>(glfwGetWindowUserPointer(window))->GetInputs();
        if(inputs->OnKey != NULL)
            inputs->OnKey(key, scancode, action);
    }

    void Inputs::MouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
    {
        Inputs* inputs = reinterpret_cast<Engine*>(glfwGetWindowUserPointer(window))->GetInputs();
        if(inputs->OnMouseButton != NULL)
            inputs->OnMouseButton(button, action);
    }

    void Inputs::MousePositionCallback(GLFWwindow* window, double xpos, double ypos) {
        Inputs* inputs = reinterpret_cast<Engine*>(glfwGetWindowUserPointer(window))->GetInputs();
        inputs->m_MouseX = static_cast<int>(xpos);
        inputs->m_MouseY = static_cast<int>(ypos);
        if(inputs->OnMouseMove != NULL)
            inputs->OnMouseMove(inputs->m_MouseX, inputs->m_MouseY);
    }
}