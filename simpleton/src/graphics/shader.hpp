#pragma once

#include "glad/glad.h"

namespace Simpleton {
    enum ShaderType {
        VertexShader,
        FragmentShader
    };

    class Shader {
        public:
            Shader();
            ~Shader();

            void Terminate();

        private:
            unsigned int m_VertexShader;
            unsigned int m_FragmentShader; 
            unsigned int m_ShaderProgId;
            bool m_IsValid;
            char m_ErrorLog[512];

        public:
            bool CheckShaderValid(ShaderType type);
            bool CheckProgramValid();

            bool AddShaderSource(ShaderType type, const char* code);
            // bool AddShaderFile(ShaderType type, const char* filePath);

            bool Compile();

            // set uniforms

            void Bind();
            void Unbind();
    };
}