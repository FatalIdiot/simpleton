#include "audioManager.hpp" 

namespace Simpleton {
    AudioManager::AudioManager() {
    }

    void AudioManager::Init(Engine* engine) {
        printf("Init Audio...\n");
        m_Engine = engine;

        m_Device = alcOpenDevice(nullptr);
        if (m_Device == nullptr) {
            printf("AudioManager: error opening device!\n");
            return;
        }

        m_Context = alcCreateContext(m_Device, nullptr);
        if (m_Device == nullptr) {
            printf("AudioManager: error creating context!\n");
            return;
        }

        if (!alcMakeContextCurrent(m_Context)) {
            printf("AudioManager: error making current context!\n");
            return;
        }

        ALfloat listenerOri[] = { 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f };
        alListener3f(AL_POSITION, 0, 0, 1.0f);
        alListener3f(AL_VELOCITY, 0, 0, 0);
        alListenerfv(AL_ORIENTATION, listenerOri);

        ALCenum error = alGetError();
        if (error != AL_NO_ERROR)
                printf("Error!!!\n");
    }

    void AudioManager::Terminate() {
        alcMakeContextCurrent(nullptr);
        alcDestroyContext(m_Context);
        alcCloseDevice(m_Device);
    }
}