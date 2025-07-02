#include "shader.hpp"

#include <iostream>
#include <fstream>
#include <sstream>

#include "glad/glad.h"

namespace Simpleton {
    Shader::Shader() {
        m_VertexShader = glCreateShader(GL_VERTEX_SHADER);
        m_FragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        m_ShaderProgId = glCreateProgram();

        m_IsValid = false;
    }

    Shader::~Shader() {
        Terminate();
    }

    bool Shader::CheckShaderValid(ShaderType type) {
        unsigned int shader = (type == ShaderType::VertexShader ? m_VertexShader : m_FragmentShader);

        int success;
        glGetShaderiv(shader, GL_SHADER_SOURCE_LENGTH, &success);
        if(!success) {
            strcpy_s(m_ErrorLog, sizeof(m_ErrorLog), "Shader has no source code.");
            return false;
        }
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if(!success) {
            strcpy_s(m_ErrorLog, sizeof(m_ErrorLog), "Shader not compiled or compiled unseccessfully.");
            return false;
        }

        return true;
    }

    bool Shader::CheckProgramValid() {
        return m_IsValid;
    }

    bool Shader::AddShaderSource(ShaderType type, const char* code) {
        int success;
        const char* shaderTypeStr = (type == ShaderType::VertexShader ? "Vertex" : "Fragment");
        printf("Adding %s Shader...\n", shaderTypeStr);
        unsigned int shader = (type == ShaderType::VertexShader ? m_VertexShader : m_FragmentShader);

        glShaderSource(shader, 1, &code, 0);
        glCompileShader(shader);
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if(!success)
        {
            glGetShaderInfoLog(shader, 512, 0, m_ErrorLog);
            printf("%s Shader Error: %s\n", shaderTypeStr, m_ErrorLog);
            return false;
        }

        return true;
    }

    bool Shader::AddShaderFile(ShaderType type, const char* filePath) {
        std::ifstream file(filePath);
        if (!file.is_open()) {
            printf("Error opening shader file: %s\n", filePath);
            return false;
        }

        std::stringstream buffer;
        buffer << file.rdbuf();

        file.close();

        return AddShaderSource(type, buffer.str().c_str());
    }

    bool Shader::Compile() {
        printf("Compiling shader %u\n", m_ShaderProgId);
        int success;

        // Check both shaders for validity 
        if(!CheckShaderValid(ShaderType::VertexShader)) {
            printf("Vertex Shader Error: %s\n", m_ErrorLog);
            return false;
        }
        if(!CheckShaderValid(ShaderType::FragmentShader)) {
            printf("Fragment Shader Error: %s\n", m_ErrorLog);
            return false;
        }

        glAttachShader(m_ShaderProgId, m_VertexShader);
        glAttachShader(m_ShaderProgId, m_FragmentShader);
        glLinkProgram(m_ShaderProgId);
        glGetProgramiv(m_ShaderProgId, GL_LINK_STATUS, &success);
        if(!success) {
            m_IsValid = false;
            glGetProgramInfoLog(m_ShaderProgId, 512, 0, m_ErrorLog);
            printf("Shader Compilation Error: %s\n", m_ErrorLog);
            return false;
        }

        m_IsValid = true;
        return true;
    }

    void Shader::SetUniform(const char* name, float x, float y, float z, float w) {
        int uniformLocation = glGetUniformLocation(m_ShaderProgId, name);
        glUniform4f(uniformLocation, x, y, z, w);
    }

    void Shader::Bind() {
        glUseProgram(m_ShaderProgId);
    }

    void Shader::Unbind() {
        glUseProgram(0);
    }

    void Shader::Terminate() {
        glDeleteShader(m_VertexShader);
        glDeleteShader(m_FragmentShader);

        int currentShaderProg;
        glGetIntegerv(GL_CURRENT_PROGRAM, &currentShaderProg);
        if(currentShaderProg == m_ShaderProgId)
            Unbind();
        glDeleteProgram(m_ShaderProgId);
    }
}