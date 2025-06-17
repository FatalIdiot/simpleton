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
        if(!InitWindow(this, engine, windowWidth, windowHeight, windowName)) {
            printf("InitWindow failed!\n");
            return false;
        }

        // Init shaders for drawing primitives
        float primitiveVertices[9]; // Initial data for triangle is empty, populated before drawing 
        glGenBuffers(1, &m_PrimitiveVBO);  
        glBindBuffer(GL_ARRAY_BUFFER, m_PrimitiveVBO);  
        glBufferData(GL_ARRAY_BUFFER, sizeof(primitiveVertices), primitiveVertices, GL_DYNAMIC_DRAW);

        glGenVertexArrays(1, &m_PrimitiveVAO);  
        glBindVertexArray(m_PrimitiveVAO);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0); 

        int  shaderCompileSuccess;
        char shaderCompileInfoLog[512];

        unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER); // Create vertex shader
        const char *vertexShaderSource = "#version 330 core\n"
            "layout (location = 0) in vec3 aPos;\n"
            "void main()\n"
            "{\n"
            "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
            "}\0";
        glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
        glCompileShader(vertexShader);
        glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &shaderCompileSuccess);
        if(!shaderCompileSuccess)
        {
            glGetShaderInfoLog(vertexShader, 512, NULL, shaderCompileInfoLog);
            printf("Failed to compile Vertex shader: %s\n", shaderCompileInfoLog);
            return false;
        }

        unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER); // Create fragment shader
        const char *fragmentShaderSource = "#version 330 core\n"
            "out vec4 FragColor;\n"
            "void main()\n"
            "{\n"
            "    FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
            "}\0";
        glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
        glCompileShader(fragmentShader);
        glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &shaderCompileSuccess);
        if(!shaderCompileSuccess)
        {
            glGetShaderInfoLog(fragmentShader, 512, NULL, shaderCompileInfoLog);
            printf("Failed to compile Fragment shader: %s\n", shaderCompileInfoLog);
            return false;
        }

        m_PrimitiveShaderProgram = glCreateProgram(); // Compile shader program
        glAttachShader(m_PrimitiveShaderProgram, vertexShader);
        glAttachShader(m_PrimitiveShaderProgram, fragmentShader);
        glLinkProgram(m_PrimitiveShaderProgram);
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader); 
        glGetProgramiv(m_PrimitiveShaderProgram, GL_LINK_STATUS, &shaderCompileSuccess);
        if(!shaderCompileSuccess) {
            glGetProgramInfoLog(m_PrimitiveShaderProgram, 512, NULL, shaderCompileInfoLog);
            printf("Failed to link primitive shader program: %s\n", shaderCompileInfoLog);
            return false;
        }

        return true;
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

    // Convert to screen space. isAxisY - to invert the Y axis, otherwise positive values go from bottom to top
    float ConvertScreenToOglCoords(int coord, float screenSize, bool isAxisY = false) {
        float result = (coord / screenSize) * 2.0f - 1.0f;
        return isAxisY ? result * -1.0f : result;
    }

    void Renderer::FillTriangle(Color color, Point pos1, Point pos2, Point pos3) {
        glBindBuffer(GL_ARRAY_BUFFER, m_PrimitiveVBO);  
        glBindVertexArray(m_PrimitiveVAO);
        glUseProgram(m_PrimitiveShaderProgram);

        int windowW, windowH;
        GetWindowSize(windowW, windowH);
        float screenW = static_cast<float>(windowW);
        float screenH = static_cast<float>(windowH);
        float primitiveVertices[9] = {
            ConvertScreenToOglCoords(pos1.x, screenW), ConvertScreenToOglCoords(pos1.y, screenH, true), 0.0f,
            ConvertScreenToOglCoords(pos2.x, screenW), ConvertScreenToOglCoords(pos2.y, screenH, true), 0.0f,
            ConvertScreenToOglCoords(pos3.x, screenW), ConvertScreenToOglCoords(pos3.y, screenH, true), 0.0f
        }; 
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(primitiveVertices), primitiveVertices);

        glDrawArrays(GL_TRIANGLES, 0, 3);
        // TO DO
    }
    
    void Renderer::FillRect(Color color, Rect area) {
        // TO DO
    }

    void Renderer::FillCircle(Color color, Point pos, int radius) {
        // TO DO
    }

    

    void Renderer::ClearScreen() {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void Renderer::SwapBuffers() {
        glfwSwapBuffers(m_Window);
    }
}