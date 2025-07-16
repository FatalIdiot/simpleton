#pragma once

#include <functional>
#include <queue>
#include <map>
#include <vector>

#include "glad/glad.h"
#include "glfw3.h"

#include "../engine.hpp"
#include "../utils.hpp"

namespace Simpleton {
    enum InputEventType {
        KeyboardKey,
        MouseKey
    };

    struct InputEvent {
        InputEventType type;
        int key;
        int action;
        double time;
        Point<unsigned int> mousePos;

        InputEvent(InputEventType eType, int eKey, int eAction, double eTime, Point<unsigned int> eMousePos) :
            type(eType), key(eKey), action(eAction), time(eTime), mousePos(eMousePos) {}
    };

    class InputsManager {
        friend class Engine; 

        private:
            Engine* m_Engine = nullptr;
            unsigned int m_MouseX, m_MouseY;
            std::queue<InputEvent> m_Events; 
            std::map<int, std::vector< std::function<void(InputEvent e)> >> m_Bindings;

        public:
            void AddBinding(int key, std::function<void(InputEvent e)> func); 
            void RemoveBinding(int key); 

        private:
            void Init(Engine* engine);
            void Terminate();

            void ProcessKey(InputEventType type, int key, int action);
            void MouseMove(double xpos, double ypos);

            void PollInputEvents();

            // Static methods that are called by GLFW. Instance methods are called from these.
            static void KeyboardCallbackDispatch(GLFWwindow* window, int key, int scancode, int action, int mods);
            static void MouseCallbackDispatch(GLFWwindow* window, int button, int action, int mods);
            static void MouseMoveDispatch(GLFWwindow* window, double xpos, double ypos);
    };
}