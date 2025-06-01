#pragma once

#include <functional>

#include "./simpleTexture.hpp"
#include "./utils.hpp"

typedef struct GLFWwindow GLFWwindow;

namespace Simpleton {    
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
}