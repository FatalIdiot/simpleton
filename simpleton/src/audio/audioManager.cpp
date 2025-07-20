#include "audioManager.hpp" 

namespace Simpleton {
    AudioManager::AudioManager() {
        
    }

    void AudioManager::Init(Engine* engine) {
        m_Engine = engine;
    }

    void AudioManager::Terminate() {

    }
}