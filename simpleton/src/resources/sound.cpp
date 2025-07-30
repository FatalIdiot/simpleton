#include "sound.hpp"
#include "../loaders/audioWavLoader.hpp"

namespace Simpleton {
    void Sound::Init() {
        alGenBuffers(1, &m_SoundId);
    }

    Sound::Sound() {
        Init();
    }

    Sound::Sound(const char* filePath) {
        Init();
        LoadFile(filePath);
    }

    Sound::~Sound() {
        alDeleteBuffers(1, &m_SoundId); 
    }

    bool Sound::LoadFile(const char* filePath) {
        WavData wavFile = loadWavFile(filePath);

        alBufferData(m_SoundId, wavFile.format, wavFile.data.data(), static_cast<int>(wavFile.data.size()), wavFile.frequency);
        
        return true;
    }

    unsigned int Sound::GetId() const {
        return m_SoundId;
    }
}