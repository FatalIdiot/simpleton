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

        private:
            unsigned int m_PrimitiveVBO;
            unsigned int m_PrimitiveVAO;
            unsigned int m_PrimitiveShaderProgram;

        public:
            bool Init(void* engine, int windowWidth, int windowHeight, char* windowName);
            void Terminate();

            void GetWindowSize(int& width, int& height);

            bool WindowShouldClose(); // return if GLFW window must be closed
            void SetWireframeRendering(bool enable); // enable rendering wireframes
            void SetWindowResizable(bool setResizable);
            void SetClearColor(float r, float g, float b);

            void FillTriangle(Color color, Point pos1, Point pos2, Point pos3);
            void FillRect(Color color, Rect area);
            void FillCircle(Color color, Point pos, int radius);

            void ClearScreen();
            void SwapBuffers();
    };
}