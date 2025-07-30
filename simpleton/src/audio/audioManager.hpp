#pragma once

#define AL_LIBTYPE_STATIC
#include "AL/al.h"
#include "AL/alc.h"

#include "../engine.hpp"

namespace Simpleton {
    class AudioManager {
        friend class Engine; 

        private:
            Engine* m_Engine = nullptr;
            ALCdevice* m_Device;
            ALCcontext* m_Context;

        public:
            AudioManager();
            
        private:
            void Init(Engine* engine);
            void Terminate();
    };
}