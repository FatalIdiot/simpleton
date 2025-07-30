#pragma once

#include "../resources/sound.hpp"

namespace Simpleton {
    class SoundSource {
        private:
            unsigned int m_SoundSourceId;
        
        public:
            SoundSource();
            void AttachSound(Sound* sound);

            void SetPosition(float x, float y, float z);
            void SetVelocity(float x, float y, float z);
            void SetPitch(float pitch);
            void SetGain(float gain);
            void SetLooping(bool loop);

            void Play();
    };
}