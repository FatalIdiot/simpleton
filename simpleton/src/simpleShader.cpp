#include "glad/glad.h"
#include <iostream>

#include "simpleShader.hpp"

namespace Simpleton {
    SimpleShader::SimpleShader(const char* vertexShaderSource, const char* fragmentShaderSource) {
        CompileShader(vertexShaderSource, fragmentShaderSource);
    }

    bool SimpleShader::CompileShader(const char* vertexShaderSource, const char* fragmentShaderSource) {
        m_ShaderProgId = glCreateProgram();
        std::cout << "Created Shader: " << m_ShaderProgId << std::endl;

        std::cout << "Compiling Shader...\n";
        int success;
        char errorLog[512];

        unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertexShader, 1, &vertexShaderSource, 0);
        glCompileShader(vertexShader);
        glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
        if(!success)
        {
            glGetShaderInfoLog(vertexShader, 512, 0, errorLog);
            std::cout << "Vertex Shader Error: " << errorLog << std::endl;
            return false;
        }

        unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragmentShader, 1, &fragmentShaderSource, 0);
        glCompileShader(fragmentShader);
        glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
        if(!success)
        {
            glGetShaderInfoLog(fragmentShader, 512, 0, errorLog);
            std::cout << "Fragment Shader Error: " << errorLog << std::endl;
            return false;
        }

        glAttachShader(m_ShaderProgId, vertexShader);
        glAttachShader(m_ShaderProgId, fragmentShader);
        glLinkProgram(m_ShaderProgId);
        glGetProgramiv(m_ShaderProgId, GL_LINK_STATUS, &success);
        if(!success) {
            glGetProgramInfoLog(m_ShaderProgId, 512, 0, errorLog);
            std::cout << "Shader Prog Error: " << errorLog << std::endl;
            return false;
        }

        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);

        std::cout << "Shader " << m_ShaderProgId << " Compile Done...\n";
        return true;
    }

    void SimpleShader::SetUniform1i(const char* name, int i) {
        int uniformLocation = glGetUniformLocation(m_ShaderProgId, name);
        glUseProgram(m_ShaderProgId);
        glUniform1i(uniformLocation, i);
    }

    void SimpleShader::SetUniform4f(const char* name, float x, float y, float z, float w) {
        int uniformLocation = glGetUniformLocation(m_ShaderProgId, name);
        glUseProgram(m_ShaderProgId);
        glUniform4f(uniformLocation, x, y, z, w);
    }

    void SimpleShader::SetUniformMatrix4fv(const char* name, const float* value, const bool transpose) {
        int uniformLocation = glGetUniformLocation(m_ShaderProgId, name);
        glUseProgram(m_ShaderProgId);
        glUniformMatrix4fv(uniformLocation, 1, transpose ? GL_TRUE : GL_FALSE, value);
    }

    void SimpleShader::Use() {
        glUseProgram(m_ShaderProgId);
        std::cout << "Using Shader: " << m_ShaderProgId << std::endl;
    }
}