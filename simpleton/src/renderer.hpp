#pragma once

#include <functional>

#include "simpleTexture.hpp"
#include "utils.hpp"
#include "graphics/mesh.hpp"

typedef struct GLFWwindow GLFWwindow;

namespace Simpleton {    
    class Renderer {
        public:
            GLFWwindow* m_Window;
            void* m_Engine;
            std::function<void(int& width, int& height)> m_ResizeCallback = NULL; // callback functions to customize window resize result

        private:
            unsigned int m_PrimitiveShaderProgram;
            Mesh m_PrimitiveMesh;

        public:
            bool Init(void* engine, GLFWwindow* window);
            void Terminate();

            template <typename T>
            void GetWindowSize(T& width, T& height);

            bool WindowShouldClose(); // return if GLFW window must be closed
            void SetWireframeRendering(bool enable); // enable rendering wireframes
            void SetWindowResizable(bool setResizable);
            void SetClearColor(float r, float g, float b);

            void FillTriangle(Color<float> color, Point<int> pos1, Point<int> pos2, Point<int> pos3);
            void FillRect(Color<float> color, Rect<int> area);
            // void FillCircle(Color<float> color, Point<int> pos, int radius);

            void ClearScreen();
            void SwapBuffers();
    };
}