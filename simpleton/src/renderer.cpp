#include "renderer.hpp"
#include "engine.hpp"

#include <iostream>
#include "glad/glad.h"
#include "glfw3.h"

class Simpleton::Renderer;

void GLAPIENTRY MessageCallback(GLenum source, GLenum type, GLuint id, GLenum severity,
                                GLsizei length, const GLchar *message, const void *userParam)
{
    std::cout << "OpenGL Debug Message: " << message << std::endl;
}

void FramebufferSizeCallback(GLFWwindow* window, int width, int height)
{
    Simpleton::Engine* engine = reinterpret_cast<Simpleton::Engine*>(glfwGetWindowUserPointer(window));
    if(engine->GetRenderer()->m_ResizeCallback != NULL)
        engine->GetRenderer()->m_ResizeCallback(width, height);
    glViewport(0, 0, width, height);
}

bool InitWindow(Simpleton::Renderer* renderer, void* engine, int windowWidth, int windowHeight, char* windowName) {
    std::cout << "Init Window...\n";
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    std::cout << "Creating Window...\n";
    renderer->m_Window = glfwCreateWindow(windowWidth, windowHeight, windowName, NULL, NULL);
    if (renderer->m_Window == NULL)
    {
        glfwTerminate();
        return false;
    }

    std::cout << "Setting current context...\n";
    glfwMakeContextCurrent(renderer->m_Window);

    // Set pointer to engine instance to access it in callbacks
    glfwSetWindowUserPointer(renderer->m_Window, reinterpret_cast<void *>(engine));

    std::cout << "Init GLAD...\n";
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        return false;
    }

    // std::cout << "Setting debugs...\n";
    glEnable(GL_DEBUG_OUTPUT);
    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
    glDebugMessageCallback(MessageCallback, nullptr);
    glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);

    glEnable(GL_DEPTH_TEST);

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glViewport(0, 0, windowWidth, windowHeight);
    glfwSetFramebufferSizeCallback(renderer->m_Window, FramebufferSizeCallback);

    std::cout << "Window init done...\n";
    return true;
}

namespace Simpleton {
    bool Renderer::Init(void* engine, int windowWidth, int windowHeight, char* windowName) {
        printf("Renderer Inputs...\n");
        m_Engine = engine;
        return InitWindow(this, engine, windowWidth, windowHeight, windowName);
    }

    void Renderer::Terminate() {
        printf("Renderer Terminate...\n");
        glfwDestroyWindow(m_Window);
        glfwTerminate();
    }

    void Renderer::GetWindowSize(int& width, int& height) {
        glfwGetWindowSize(m_Window, &width, &height);
    }

    bool Renderer::WindowShouldClose() {
        return glfwWindowShouldClose(m_Window);
    }

    void Renderer::SetWireframeRendering(bool enable) {
        glPolygonMode(GL_FRONT_AND_BACK, enable ? GL_LINE : GL_FILL);
    }

    void Renderer::SetWindowResizable(bool setResizable) {
        glfwSetWindowAttrib(m_Window, GLFW_RESIZABLE, setResizable);
    }

    void Renderer::SetClearColor(float r, float g, float b) {
        glClearColor(r, g, b, 1.0f);
    }

    void Renderer::FillRect(Color color, Rect area) {
        // TO DO
    }

    void Renderer::DrawTexture(Rect area, SimpleTexture* texture) {
        // TO DO
    }

    void Renderer::ClearScreen() {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void Renderer::SwapBuffers() {
        glfwSwapBuffers(m_Window);
    }
}