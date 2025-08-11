#pragma once

#include <filesystem>
namespace fs = std::filesystem;

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
            bool AddShaderFile(ShaderType type, fs::path filePath);

            bool Compile();

            // set uniforms
            void SetUniform(const char* name, float x, float y, float z, float w);
            void SetUniform(const char* name, int i);

            void Bind() const;
            void Unbind() const;

        private:
            bool CheckShaderValid(ShaderType type);
            void Terminate();
    };
}