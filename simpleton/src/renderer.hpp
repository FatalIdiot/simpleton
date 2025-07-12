#pragma once

#include <functional>

#include "utils.hpp"
#include "graphics/mesh.hpp"
#include "graphics/shader.hpp"
#include "resources/texture.hpp"

typedef struct GLFWwindow GLFWwindow;

namespace Simpleton {    
    class Engine;

    class Renderer {
        friend class Engine; 
        
        public:
            GLFWwindow* m_Window;
            void* m_Engine;
            std::function<void(int& width, int& height)> m_ResizeCallback = NULL; // callback functions to customize window resize result

        private:
            Mesh m_PrimitiveMesh;
            Shader m_PrimitiveShader;
            Shader m_TextureShader;

        public:
            template <typename T>
            void GetWindowSize(T& width, T& height);

            bool WindowShouldClose(); // return if GLFW window must be closed
            void SetWireframeRendering(bool enable); // enable rendering wireframes
            void SetWindowResizable(bool setResizable);
            void SetClearColor(float r, float g, float b);
            void DepthTest(bool enable);

            void FillTriangle(Color<float> color, Point<int> pos1, Point<int> pos2, Point<int> pos3);
            void FillRect(Color<float> color, Rect<int> area);
            void FillCircle(Color<float> color, Circle<int> circle, unsigned short pointsCount = 25);

            void DrawLine(Color<float> color, Point<int> pointA, Point<int> pointB);
            void DrawTriangle(Color<float> color, Point<int> pos1, Point<int> pos2, Point<int> pos3);
            void DrawRect(Color<float> color, Rect<int> area);
            void DrawCircle(Color<float> color, Circle<int> circle, unsigned short pointsCount = 25);

            void BlitTexture(Texture* texture, Rect<int> destRect, Rect<float> srcRect = {0.0f, 0.0f, 1.0f, 1.0f});

        private:
            bool Init(void* engine, GLFWwindow* window);
            void Terminate();
            void ClearScreen();
            void SwapBuffers();
    };
}