#pragma once

#include <functional>

#include "glad/glad.h"
#include "glfw3.h"

typedef struct GLFWwindow GLFWwindow;

namespace Simpleton {
    class Engine;

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
}