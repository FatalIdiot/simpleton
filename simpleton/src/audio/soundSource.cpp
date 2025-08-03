#include "soundSource.hpp"
#include "../logger.hpp"

namespace Simpleton {
    SoundSource::SoundSource() {
        alGenSources(1, &m_SoundSourceId); LogOal();
        LogMsg("Generated sound source {}", m_SoundSourceId);

        SetPitch(1.0f); LogOal();
        SetGain(1.0f); LogOal();
        SetPosition(0.0f, 0.0f, 0.0f); LogOal();
        SetLooping(false); LogOal();
    }

    SoundSource::~SoundSource() {
        LogMsg("Deleting sound source {}", m_SoundSourceId);
        alSourcei(m_SoundSourceId, AL_BUFFER, 0); LogOal();
        alDeleteSources(1, &m_SoundSourceId); LogOal();
    }

    void SoundSource::AttachSound(Sound* sound) {
        LogMsg("Attaching sound {} to source {}", sound->GetId(), m_SoundSourceId);
        alSourcei(m_SoundSourceId, AL_BUFFER, sound->GetId()); LogOal();
    }

    void SoundSource::SetPosition(float x, float y, float z) {
        alSource3f(m_SoundSourceId, AL_POSITION, x, y, z); LogOal();
    }

    void SoundSource::SetVelocity(float x, float y, float z) {
        alSource3f(m_SoundSourceId, AL_VELOCITY, x, y, z); LogOal();
    }

    void SoundSource::SetPitch(float pitch) {
        alSourcef(m_SoundSourceId, AL_PITCH, pitch); LogOal();
    }

    void SoundSource::SetGain(float gain) {
        alSourcef(m_SoundSourceId, AL_GAIN, gain); LogOal();
    }

    void SoundSource::SetLooping(bool loop) {
        alSourcei(m_SoundSourceId, AL_LOOPING, loop ? AL_TRUE : AL_FALSE); LogOal();
    }

    void SoundSource::Play() {
        alSourcePlay(m_SoundSourceId); LogOal();
    }
}