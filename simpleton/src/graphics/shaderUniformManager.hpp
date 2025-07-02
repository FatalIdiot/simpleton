#pragma once

#include "../engine.hpp"

namespace Simpleton {
    class ShaderUniformManager {
        private:
            static Engine* m_Engine;

        private:
            ShaderUniformManager() = delete;

        public:
            // Sets engine pointer to get data from.
            // This is because there might be multiple instances of Engine.
            static void SetEngine(Engine* engine);

            // Sets global uniforms to the current shader program.
            static void SetData();
    };
}