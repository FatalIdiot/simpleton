#include "shaderUniformManager.hpp"

#include <iostream>

namespace Simpleton {
    void ShaderUniformManager::SetEngine(Engine* engine) {
        ShaderUniformManager::m_Engine = engine;
    }

    void ShaderUniformManager::SetData() {
        int currentShader;
        glGetIntegerv(GL_CURRENT_PROGRAM, &currentShader);

        int screenW, screenH;
        m_Engine->GetRenderer()->GetWindowSize(screenW, screenH);

        glUniform2i(
            glGetUniformLocation(currentShader, "screenSize"), 
            screenW, screenH
        );
    }
}