#include "renderer.hpp"
#include "engine.hpp"

#include "glad/glad.h"
#include "glfw3.h"

#define _USE_MATH_DEFINES
#include <math.h>

class Simpleton::Renderer;

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

        // Enable alpha blending for textures with alpha channel
        // Might make this more addaptable in future for optimization
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        // Shader for texture drawing functions
        m_PrimitiveShader.AddShaderSource(ShaderType::VertexShader, "#version 330 core\n"
            "layout (location = 0) in vec2 aPos;\n"
            "uniform ivec2 ScreenSize;\n"
            "void main()\n"
            "{\n"
            "    gl_Position = vec4(\n"
            "        (aPos.x / ScreenSize.x) * 2.0 - 1.0,\n"
            "        ((aPos.y / ScreenSize.y) * 2.0 - 1.0) * -1,\n"
            "        0.0, 1.0\n"
            "    );\n"
            "}\0");
        m_PrimitiveShader.AddShaderSource(ShaderType::FragmentShader, "#version 330 core\n"
            "out vec4 FragColor;\n"
            "uniform vec4 Color;\n"
            "void main()\n"
            "{\n"
            "    FragColor = Color;\n"
            "}\0");
        m_PrimitiveShader.Compile();

        // Shader for blitting textures
        m_TextureShader.AddShaderSource(ShaderType::VertexShader, "#version 330 core\n"
            "layout (location = 0) in vec2 aPos;\n"
            "layout (location = 1) in vec2 aTextureCoord;\n"
            "out vec2 TextureCoord;\n"
            "uniform ivec2 ScreenSize;\n"
            "void main()\n"
            "{\n"
            "   gl_Position = vec4(\n"
            "       (aPos.x / ScreenSize.x) * 2.0 - 1.0,\n"
            "       ((aPos.y / ScreenSize.y) * 2.0 - 1.0) * -1,\n"
            "       0.0, 1.0\n"
            "   );\n"
            "   TextureCoord = aTextureCoord;"
            "}\0");
        m_TextureShader.AddShaderSource(ShaderType::FragmentShader, "#version 330 core\n"
            "out vec4 FragColor;\n"
            "in vec2 TextureCoord;"
            "uniform sampler2D texture1;"
            "void main()\n"
            "{\n"
            "    FragColor = texture(texture1, TextureCoord);\n"
            "}\0");
        m_TextureShader.Compile();

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

    void Renderer::DepthTest(bool enable) {
        if(enable)
            glEnable(GL_DEPTH_TEST);
        else
            glDisable(GL_DEPTH_TEST);
    }

    void Renderer::FillTriangle(Color<float> color, Point<int> pos1, Point<int> pos2, Point<int> pos3) {
        m_PrimitiveShader.Bind();
        m_PrimitiveShader.SetUniform("Color", color.r, color.g, color.b, color.a);

        int screenSpaceVerts[6] = {
            pos1.x, pos1.y,
            pos2.x, pos2.y,
            pos3.x, pos3.y
        };
        m_PrimitiveMesh.SetBufferData(GL_TRIANGLES, screenSpaceVerts, sizeof(screenSpaceVerts));
        MeshAttribute attributes[] = {
            { GL_INT, 2 }
        };
        m_PrimitiveMesh.SetAttributes(attributes, 1);

        // We draw triangle primitives with VBOs, so make sure EBO data is not set
        m_PrimitiveMesh.RemoveIndexData();
        m_PrimitiveMesh.Draw();
    }
    
    void Renderer::FillRect(Color<float> color, Rect<int> area) {
        m_PrimitiveShader.Bind();
        m_PrimitiveShader.SetUniform("Color", color.r, color.g, color.b, color.a);

        int screenSpaceVerts[12] = {
            area.x, area.y, // left top
            area.x, area.y + area.h, // left bottom
            area.x + area.w, area.y, // right top
            area.x + area.w, area.y + area.h // right bottom
        };
        m_PrimitiveMesh.SetBufferData(GL_TRIANGLES, screenSpaceVerts, sizeof(screenSpaceVerts));
        
        unsigned int indexes[6] = {
            0, 1, 2, 1, 2, 3
        };
        m_PrimitiveMesh.SetIndexData(indexes, 6);

        MeshAttribute attributes[] = {
            { GL_INT, 2 }
        };
        m_PrimitiveMesh.SetAttributes(attributes, 1);

        m_PrimitiveMesh.Draw();
    }

    void Renderer::FillCircle(Color<float> color, Circle<int> circle, unsigned short pointsCount) {
        m_PrimitiveShader.Bind();
        m_PrimitiveShader.SetUniform("Color", color.r, color.g, color.b, color.a);

        int* screenSpaceVerts = new int[(pointsCount + 2) * 2];

        // First element is the center of the circle
        screenSpaceVerts[0] = circle.x;
        screenSpaceVerts[1] = circle.y;

        // Set points positions
        for(int i = 0, index = 2; i < pointsCount; i++, index += 2) {
            float angle = 2 * static_cast<float>(M_PI) * i / pointsCount;
            int x = static_cast<int>( circle.x + circle.radius * cos(angle) );
            int y = static_cast<int>( circle.y + circle.radius * sin(angle) );
            screenSpaceVerts[index] = x;
            screenSpaceVerts[index + 1] = y;
        }

        // Adding another segment to close the circle
        screenSpaceVerts[(pointsCount + 1) * 2] = screenSpaceVerts[2];
        screenSpaceVerts[(pointsCount + 1) * 2 + 1] = screenSpaceVerts[3];

        m_PrimitiveMesh.SetBufferData(GL_TRIANGLE_FAN, screenSpaceVerts, (pointsCount + 2) * 2 * sizeof(int));
        
        MeshAttribute attributes[] = {
            { GL_INT, 2 }
        };
        m_PrimitiveMesh.SetAttributes(attributes, 1);

        // We draw circle primitives with VBOs, using GL_TRIANGLE_FAN, so make sure EBO data is not set
        m_PrimitiveMesh.RemoveIndexData();

        m_PrimitiveMesh.Draw();

        delete screenSpaceVerts;
    }

    void Renderer::DrawLine(Color<float> color, Point<int> pointA, Point<int> pointB) {
        m_PrimitiveShader.Bind();
        m_PrimitiveShader.SetUniform("Color", color.r, color.g, color.b, color.a);

        int screenSpaceVerts[4] = {
            pointA.x, pointA.y,
            pointB.x, pointB.y
        };
        m_PrimitiveMesh.SetBufferData(GL_LINES, screenSpaceVerts, sizeof(screenSpaceVerts));
        
        unsigned int indexes[2] = {
            0, 1
        };
        m_PrimitiveMesh.SetIndexData(indexes, 2);

        MeshAttribute attributes[] = {
            { GL_INT, 2 }
        };
        m_PrimitiveMesh.SetAttributes(attributes, 1);

        m_PrimitiveMesh.Draw();
    }

    void Renderer::DrawTriangle(Color<float> color, Point<int> pos1, Point<int> pos2, Point<int> pos3) {
        m_PrimitiveShader.Bind();
        m_PrimitiveShader.SetUniform("Color", color.r, color.g, color.b, color.a);

        int screenSpaceVerts[6] = {
            pos1.x, pos1.y,
            pos2.x, pos2.y,
            pos3.x, pos3.y
        };
        m_PrimitiveMesh.SetBufferData(GL_LINES, screenSpaceVerts, sizeof(screenSpaceVerts));
        
        unsigned int indexes[6] = {
            0, 1, 1, 2, 2, 0
        };
        m_PrimitiveMesh.SetIndexData(indexes, 6);

        MeshAttribute attributes[] = {
            { GL_INT, 2 }
        };
        m_PrimitiveMesh.SetAttributes(attributes, 1);

        m_PrimitiveMesh.Draw();
    }
    
    void Renderer::DrawRect(Color<float> color, Rect<int> area) {
        m_PrimitiveShader.Bind();
        m_PrimitiveShader.SetUniform("Color", color.r, color.g, color.b, color.a);

        int screenSpaceVerts[8] = {
            area.x, area.y,
            area.x + area.w, area.y,
            area.x + area.w, area.y + area.h,
            area.x, area.y + area.h
        };
        m_PrimitiveMesh.SetBufferData(GL_LINES, screenSpaceVerts, sizeof(screenSpaceVerts));
        
        unsigned int indexes[8] = {
            0, 1, 1, 2, 2, 3, 3, 0
        };
        m_PrimitiveMesh.SetIndexData(indexes, 8);

        MeshAttribute attributes[] = {
            { GL_INT, 2 }
        };
        m_PrimitiveMesh.SetAttributes(attributes, 1);

        m_PrimitiveMesh.Draw();
    }
    
    void Renderer::DrawCircle(Color<float> color, Circle<int> circle, unsigned short pointsCount) {
        m_PrimitiveShader.Bind();
        m_PrimitiveShader.SetUniform("Color", color.r, color.g, color.b, color.a);

        int* screenSpaceVerts = new int[pointsCount * 2];

        // Set points positions
        for(int i = 0; i < pointsCount; i++) {
            float angle = 2 * static_cast<float>(M_PI) * i / pointsCount;
            int x = static_cast<int>( circle.x + circle.radius * cos(angle) );
            int y = static_cast<int>( circle.y + circle.radius * sin(angle) );
            screenSpaceVerts[i * 2] = x;
            screenSpaceVerts[i * 2 + 1] = y;
        }

        m_PrimitiveMesh.SetBufferData(GL_LINES, screenSpaceVerts, pointsCount * 2 * sizeof(int));

        MeshAttribute attributes[] = {
            { GL_INT, 2 }
        };
        m_PrimitiveMesh.SetAttributes(attributes, 1);

        // Set point indexes
        unsigned int* indexes = new unsigned int[pointsCount * 2];
        for(int i = 0, j = 0; i < pointsCount * 2; i+=2, j++) {
            if(i == (pointsCount * 2) - 2) {
                indexes[i] = j;
                indexes[i+1] = 0;
                break;
            }
            indexes[i] = j;
            indexes[i+1] = j + 1;
        }
        m_PrimitiveMesh.SetIndexData(indexes, pointsCount * 2);

        m_PrimitiveMesh.Draw();

        delete screenSpaceVerts;
    }
    
    void Renderer::BlitTexture(Texture* texture, Rect<int> destRect, Rect<float> srcRect) {
        texture->Bind();
        m_PrimitiveMesh.Bind();

        m_TextureShader.Bind();
        m_TextureShader.SetUniform("texture1", 0);

        struct ShaderTextureCoords {
            int posX;
            int posY;
            float textureCoordX;
            float textureCoordY;
        };

        ShaderTextureCoords screenSpaceVerts[4] = {
            {destRect.x, destRect.y,                            srcRect.x, srcRect.y},
            {destRect.x, destRect.y + destRect.h,               srcRect.x, srcRect.y + srcRect.h},
            {destRect.x + destRect.w, destRect.y,               srcRect.x + srcRect.w, srcRect.y},
            {destRect.x + destRect.w, destRect.y + destRect.h,  srcRect.x + srcRect.w, srcRect.y + srcRect.h}
        };

        m_PrimitiveMesh.SetBufferData(GL_TRIANGLES, screenSpaceVerts, sizeof(ShaderTextureCoords) * 4);
        
        unsigned int indexes[6] = {
            0, 1, 2, 1, 2, 3
        };
        m_PrimitiveMesh.SetIndexData(indexes, 6);

        MeshAttribute attributes[2] = {
            { GL_INT, 2 }, { GL_FLOAT, 2 }
        };
        m_PrimitiveMesh.SetAttributes(attributes, 2);

        m_PrimitiveMesh.Draw();
    }

    void Renderer::ClearScreen() {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void Renderer::SwapBuffers() {
        glfwSwapBuffers(m_Window);
    }
}