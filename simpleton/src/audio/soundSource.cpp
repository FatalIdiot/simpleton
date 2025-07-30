#include "soundSource.hpp"

namespace Simpleton {
    SoundSource::SoundSource() {
        alGenSources(1, &m_SoundSourceId);

        SetPitch(1.0f);
        SetGain(1.0f);
        SetPosition(0.0f, 0.0f, 0.0f);
        SetLooping(false);
    }

    void SoundSource::AttachSound(Sound* sound) {
        printf("Attaching sound %u to source %u\n", sound->GetId(), m_SoundSourceId);
        alSourcei(m_SoundSourceId, AL_BUFFER, sound->GetId()); 
    }

    void SoundSource::SetPosition(float x, float y, float z) {
        alSource3f(m_SoundSourceId, AL_POSITION, x, y, z);
    }

    void SoundSource::SetVelocity(float x, float y, float z) {
        alSource3f(m_SoundSourceId, AL_VELOCITY, x, y, z);
    }

    void SoundSource::SetPitch(float pitch) {
        alSourcef(m_SoundSourceId, AL_PITCH, pitch);
    }

    void SoundSource::SetGain(float gain) {
        alSourcef(m_SoundSourceId, AL_GAIN, gain);
    }

    void SoundSource::SetLooping(bool loop) {
        alSourcei(m_SoundSourceId, AL_LOOPING, loop ? AL_TRUE : AL_FALSE);
    }

    void SoundSource::Play() {
        alSourcePlay(m_SoundSourceId);
    }
}