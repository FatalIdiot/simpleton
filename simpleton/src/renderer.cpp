#include "renderer.hpp"
#include "engine.hpp"

#include "glad/glad.h"
#include "glfw3.h"

#define _USE_MATH_DEFINES
#include <math.h>

class Simpleton::Renderer;

void GLAPIENTRY MessageCallback(GLenum source, GLenum type, GLuint id, GLenum severity,
                                GLsizei length, const GLchar *message, const void *userParam)
{
    printf("Init Window: %s\n", message);
}

void FramebufferSizeCallback(GLFWwindow* window, int width, int height)
{
    Simpleton::Engine* engine = reinterpret_cast<Simpleton::Engine*>(glfwGetWindowUserPointer(window));
    if(engine->GetRenderer()->m_ResizeCallback != NULL)
        engine->GetRenderer()->m_ResizeCallback(width, height);
    glViewport(0, 0, width, height);
}

bool InitWindow(Simpleton::Renderer* renderer, void* engine) {
    printf("Init Window...\n");
    // Set pointer to engine instance to access it in callbacks
    glfwSetWindowUserPointer(renderer->m_Window, reinterpret_cast<void *>(engine));

    // Setting debugs
    glEnable(GL_DEBUG_OUTPUT);
    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
    glDebugMessageCallback(MessageCallback, nullptr);
    glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);

    glEnable(GL_DEPTH_TEST);

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glfwSetFramebufferSizeCallback(renderer->m_Window, FramebufferSizeCallback);

    printf("Window init done...\n");
    return true;
}

namespace Simpleton {
    bool Renderer::Init(void* engine, GLFWwindow* window) {
        printf("Renderer Init...\n");
        m_Engine = engine;
        m_Window = window;
        if(!InitWindow(this, engine)) {
            printf("InitWindow failed!\n");
            return false;
        }

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

    template <typename T>
    void Renderer::GetWindowSize(T& width, T& height) {
        int w, h; 
        glfwGetWindowSize(m_Window, &w, &h);
        width = static_cast<T>(w);
        height = static_cast<T>(h);
    }

    template <> // implementation for 'int', as we don't cast the type if this is the case 
    void Renderer::GetWindowSize<int>(int& width, int& height) {
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

    // Convert function for drawing primitives to screen.
    // Convert to screen space. isAxisY - to invert the Y axis, otherwise positive values go from bottom to top
    float ConvertScreenToOglCoords(int coord, int screenSize, bool isAxisY = false) {
        float result = (static_cast<float>(coord) / static_cast<float>(screenSize)) * 2.0f - 1.0f;
        return isAxisY ? result * -1.0f : result;
    }

    // Convert function for drawing primitives to screen.
    // Convert an array of OpenGL coordinates to screen coordinates. Result is stored in 'outArray'.
    void ConvertArrToOglCoords(int* array, float* outArray, int varsCount, int windowW, int windowH) {
        for(int i = 0, row = 0; i < varsCount; i++, row++) {
            int rowIndex = row % 3;
            switch(rowIndex) {
                case 0: // X
                    outArray[i] = ConvertScreenToOglCoords(array[i], windowW);
                    break;
                case 1: // Y
                    outArray[i] = ConvertScreenToOglCoords(array[i], windowH, true);
                    break;
                default: // Z
                    outArray[i] = static_cast<float>(array[i]);
            }
        }
    }

    void Renderer::FillTriangle(Color<float> color, Point<int> pos1, Point<int> pos2, Point<int> pos3) {
        glUseProgram(m_PrimitiveShaderProgram);

        int windowW, windowH;
        GetWindowSize<int>(windowW, windowH);
        int screenSpaceVerts[9] = {
            pos1.x, pos1.y, 0,
            pos2.x, pos2.y, 0,
            pos3.x, pos3.y, 0
        };
        float convertedVerts[9];
        ConvertArrToOglCoords(screenSpaceVerts, convertedVerts, 9, windowW, windowH);
        m_PrimitiveMesh.SetBufferData(PrimitiveTypes::Triangles, convertedVerts, sizeof(convertedVerts));
        unsigned int attributes[] = { 3 };
        m_PrimitiveMesh.SetAttributes(attributes, 1);
        m_PrimitiveMesh.Draw();
    }
    
    void Renderer::FillRect(Color<float> color, Rect<int> area) {
        glUseProgram(m_PrimitiveShaderProgram);

        int windowW, windowH;
        GetWindowSize<int>(windowW, windowH);
        int screenSpaceVerts[18] = {
            area.x, area.y, 0,
            area.x, area.y + area.h, 0,
            area.x + area.w, area.y, 0,
            area.x, area.y + area.h, 0,
            area.x + area.w, area.y, 0,
            area.x + area.w, area.y + area.h, 0
        };
        float convertedVerts[18];
        ConvertArrToOglCoords(screenSpaceVerts, convertedVerts, 18, windowW, windowH);
        m_PrimitiveMesh.SetBufferData(PrimitiveTypes::Triangles, convertedVerts, sizeof(convertedVerts));
        unsigned int attributes[] = { 3 };
        m_PrimitiveMesh.SetAttributes(attributes, 1);
        m_PrimitiveMesh.Draw();
    }

    void Renderer::FillCircle(Color<float> color, Circle<int> circle, unsigned short pointsCount) {
        glUseProgram(m_PrimitiveShaderProgram);
        int* screenSpaceVerts = new int[(pointsCount + 2) * 3];
        float* convertedVerts = new float[(pointsCount + 2) * 3];
        int windowW, windowH;
        GetWindowSize<int>(windowW, windowH);

        // First element is the center of the circle
        screenSpaceVerts[0] = circle.x;
        screenSpaceVerts[1] = circle.y;
        screenSpaceVerts[2] = 0;

        // Set points positions
        for(int i = 0, index = 3; i < pointsCount; i++, index += 3) {
            float angle = 2 * static_cast<float>(M_PI) * i / pointsCount;
            int x = static_cast<int>( circle.x + circle.radius * cos(angle) );
            int y = static_cast<int>( circle.y + circle.radius * sin(angle) );
            screenSpaceVerts[index] = x;
            screenSpaceVerts[index + 1] = y;
            screenSpaceVerts[index + 2] = 0;
        }

        // Adding another segment to close the circle
        screenSpaceVerts[(pointsCount + 1) * 3] = screenSpaceVerts[3];
        screenSpaceVerts[(pointsCount + 1) * 3 + 1] = screenSpaceVerts[4];
        screenSpaceVerts[(pointsCount + 1) * 3 + 2] = screenSpaceVerts[5];

        ConvertArrToOglCoords(screenSpaceVerts, convertedVerts, (pointsCount + 2) * 3, windowW, windowH);
        m_PrimitiveMesh.SetBufferData(PrimitiveTypes::TriangleFan, convertedVerts, (pointsCount + 2) * 3 * sizeof(float));
        unsigned int attributes[] = { 3 };
        m_PrimitiveMesh.SetAttributes(attributes, 1);
        m_PrimitiveMesh.Draw();

        delete convertedVerts;
        delete screenSpaceVerts;
    }

    void Renderer::ClearScreen() {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void Renderer::SwapBuffers() {
        glfwSwapBuffers(m_Window);
    }
}