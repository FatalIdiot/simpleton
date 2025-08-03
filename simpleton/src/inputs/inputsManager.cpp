#include "inputsManager.hpp"
#include "../logger.hpp"

#include <iostream>

namespace Simpleton {
    void InputsManager::Init(Engine* engine) {
        LogMsg("Init Inputs...");
        m_Engine = engine;

        GLFWwindow* window = m_Engine->GetRenderer()->m_Window;
        glfwSetKeyCallback(window, KeyboardCallbackDispatch);
        glfwSetMouseButtonCallback(window, MouseCallbackDispatch);
        glfwSetCursorPosCallback(window, MouseMoveDispatch);
    }

    void InputsManager::Terminate() {
        LogMsg("Inputs Terminate...");
    }

    void InputsManager::AddBinding(int key, std::function<void(InputEvent e)> func) {
        m_Bindings[key].push_back(func);
    }

    void InputsManager::RemoveBinding(int key) {
        if(m_Bindings[key].size() > 0)
            m_Bindings[key].clear();
        
    }

    void InputsManager::PollInputEvents() {
        while (!m_Events.empty()) {
            InputEvent event = m_Events.front();

            for (auto binding : m_Bindings[event.key]) {
                binding(event);
            }

            m_Events.pop();
        }
    }

    void InputsManager::ProcessKey(InputEventType type, int key, int action) {
        InputEvent newEvent(type, key, action, m_Engine->GetTime(), { m_MouseX, m_MouseY });
        m_Events.push(newEvent);
    }

    void InputsManager::MouseMove(double xpos, double ypos) {
        m_MouseX = static_cast<unsigned int>(xpos);
        m_MouseY = static_cast<unsigned int>(ypos);
    }

    void InputsManager::KeyboardCallbackDispatch(GLFWwindow* window, int key, int scancode, int action, int mods)
    {
        InputsManager* inputs = reinterpret_cast<Engine*>(glfwGetWindowUserPointer(window))->GetInputs();
        inputs->ProcessKey(InputEventType::KeyboardKey, key, action);
    }

    void InputsManager::MouseCallbackDispatch(GLFWwindow* window, int button, int action, int mods)
    {
        InputsManager* inputs = reinterpret_cast<Engine*>(glfwGetWindowUserPointer(window))->GetInputs();
        inputs->ProcessKey(InputEventType::MouseKey, button, action);
    }

    void InputsManager::MouseMoveDispatch(GLFWwindow* window, double xpos, double ypos) {
        InputsManager* inputs = reinterpret_cast<Engine*>(glfwGetWindowUserPointer(window))->GetInputs();
        inputs->MouseMove(xpos, ypos);
    }
}