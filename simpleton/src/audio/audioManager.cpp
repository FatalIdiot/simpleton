#include "audioManager.hpp" 
#include "../logger.hpp"

namespace Simpleton {
    AudioManager::AudioManager() {
    }

    void AudioManager::Init(Engine* engine) {
        LogMsg("Init Audio...");
        m_Engine = engine;

        m_Device = alcOpenDevice(nullptr);
        if (m_Device == nullptr) {
            LogErr("AudioManager: error opening device!\n");
            return;
        }

        m_Context = alcCreateContext(m_Device, nullptr);
        if (m_Device == nullptr) {
            LogErr("AudioManager: error creating context!\n");
            return;
        }

        if (!alcMakeContextCurrent(m_Context)) {
            LogErr("AudioManager: error making current context!\n");
            return;
        }

        ALfloat listenerOri[] = { 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f };
        alListener3f(AL_POSITION, 0, 0, 1.0f); LogOal();
        alListener3f(AL_VELOCITY, 0, 0, 0); LogOal();
        alListenerfv(AL_ORIENTATION, listenerOri); LogOal();
    }

    void AudioManager::Terminate() {
        alcMakeContextCurrent(nullptr); LogOal();
        alcDestroyContext(m_Context); LogOal();
        alcCloseDevice(m_Device); LogOal();
    }
}