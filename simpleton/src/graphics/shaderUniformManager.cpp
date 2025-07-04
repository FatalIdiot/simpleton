#include "shaderUniformManager.hpp"

#include "glad/glad.h"

namespace Simpleton {
    Engine* ShaderUniformManager::m_Engine = nullptr;
    
    void ShaderUniformManager::SetEngine(Engine* engine) {
        ShaderUniformManager::m_Engine = engine;
    }

    void ShaderUniformManager::SetData() {
        int currentShader;
        glGetIntegerv(GL_CURRENT_PROGRAM, &currentShader);

        int screenW, screenH;
        ShaderUniformManager::m_Engine->GetRenderer()->GetWindowSize(screenW, screenH);

        glUniform2i(
            glGetUniformLocation(currentShader, "ScreenSize"), 
            screenW, screenH
        );
    }
}