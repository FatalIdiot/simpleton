#include "sound.hpp"
#include "../loaders/audioWavLoader.hpp"
#include "../logger.hpp"

namespace Simpleton {
    void Sound::Init() {
        alGenBuffers(1, &m_SoundId);
        LogMsg("Generated sound {}", m_SoundId);
    }

    Sound::Sound() {
        Init();
    }

    Sound::Sound(fs::path filePath) {
        Init();
        LoadFile(filePath);
    }

    Sound::Sound(int format, int freq, int size, void* data) {
        Init();
        LoadData(format, freq, size, data);
    }

    Sound::~Sound() {
        LogMsg("Deleting sound {}", m_SoundId);
        alDeleteBuffers(1, &m_SoundId); LogOal();
    }

    bool Sound::LoadFile(fs::path filePath) {
        WavData wavFile = loadWavFile(filePath.string());

        alBufferData(m_SoundId, wavFile.format, wavFile.data.data(), static_cast<int>(wavFile.data.size()), wavFile.frequency);
        
        return true;
    }

    bool Sound::LoadData(int format, int freq, int size, void* data) {
        alBufferData(m_SoundId, format, data, size, freq);
        return true;
    }

    unsigned int Sound::GetId() const {
        return m_SoundId;
    }
}