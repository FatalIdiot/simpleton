#pragma once

#include "glad/glad.h"

namespace Simpleton {
    enum ShaderType {
        VertexShader,
        FragmentShader
    };

    class Shader {
        private:
            unsigned int m_VertexShader;
            unsigned int m_FragmentShader; 
            unsigned int m_ShaderProgId;
            bool m_IsValid;
            char m_ErrorLog[512];

        public:
            Shader();
            ~Shader();

            bool CheckProgramValid();

            bool AddShaderSource(ShaderType type, const char* code);
            bool AddShaderFile(ShaderType type, const char* filePath);

            bool Compile();

            // set uniforms
            void SetUniform(const char* name, float x, float y, float z, float w);

            void Bind();
            void Unbind();

        private:
            bool CheckShaderValid(ShaderType type);
            void Terminate();
    };
}