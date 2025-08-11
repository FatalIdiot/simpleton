#include "../utils.hpp"
#include "resourceManager.hpp"
#include "texture.hpp"
#include "sound.hpp"
#include "../loaders/audioWavLoader.hpp"
#include "../logger.hpp"

namespace Simpleton {
    void ResourceManager::Init() {
        LogMsg("Resource Manager Init...");

        // Create default texture and add to map
        const unsigned int defaultTextureSize = 5;
        unsigned char defaultTextureData[defaultTextureSize * defaultTextureSize * 3];
        for(int i = 0; i < defaultTextureSize * defaultTextureSize; i++) {
            if(i % 2 == 0) {
                defaultTextureData[i * 3] = 255;
                defaultTextureData[i * 3 + 1] = 164;
                defaultTextureData[i * 3 + 2] = 210;
            } else {
                defaultTextureData[i * 3] = 0;
                defaultTextureData[i * 3 + 1] = 0;
                defaultTextureData[i * 3 + 2] = 0;
            }
        }
        Texture* defaultTexture = new Texture(defaultTextureSize, defaultTextureSize, 3, defaultTextureData);
        defaultTexture->SetFiltering(TextureFiltering::Nearest);
        AddTexture("default", defaultTexture);

        // Create default sound
        WavData testAudio = GenTestWav();
        AddSound("default", new Sound(testAudio.format, testAudio.frequency, static_cast<int>(testAudio.data.size()), testAudio.data.data()));
    }

    void ResourceManager::Terminate() {
        LogMsg("Resource Manager Terminate...");

        // Delete all textures
        std::map<std::string, Texture*>::iterator texture_it;
        for (texture_it = m_Textures.begin(); texture_it != m_Textures.end(); texture_it++)
        {
            delete texture_it->second;
        }
        m_Textures.clear();

        // Delete all sounds
        std::map<std::string, Sound*>::iterator sound_it;
        for (sound_it = m_Sounds.begin(); sound_it != m_Sounds.end(); sound_it++)
        {
            delete sound_it->second;
        }
        m_Sounds.clear();
    }

    Texture* ResourceManager::GetTexture(const char* name) {
        // return default texture if failed to load
        if(m_Textures[name] == nullptr || !m_Textures[name]->IsLoaded()) {
            LogMsg("Resource Manager: Unable to get texture '{}', returning default texture.", name);
            return m_Textures["default"];
        }
        return m_Textures[name];
    }

    void ResourceManager::AddTexture(const char* name, Texture* texture) {
        if(m_Textures[name] != nullptr) {
            delete m_Textures[name];
            m_Textures.erase(name);
        }
        m_Textures[name] = texture;
    }

    void ResourceManager::AddTexture(const char* name, const char* filePath, unsigned char slot) {
        Texture* newTexture = new Texture(filePath, slot);
        AddTexture(name, newTexture);
    }

    void ResourceManager::AddTexture(const char* name, int width, int height, int channelsCount, unsigned char* data, unsigned char slot) {
        Texture* newTexture = new Texture(width, height, channelsCount, data, slot);
        AddTexture(name, newTexture);
    }


    Sound* ResourceManager::GetSound(const char* name) {
        // return default sound if failed to load
        if(m_Sounds[name] == nullptr) {
            LogMsg("Resource Manager: Unable to get sound '{}', returning default sound.", name);
            return m_Sounds["default"];
        }
        return m_Sounds[name];
    }

    void ResourceManager::AddSound(const char* name, Sound* sound) {
        if(m_Sounds[name] != nullptr) {
            delete m_Sounds[name];
            m_Sounds.erase(name);
        }
        m_Sounds[name] = sound;
    }

    void ResourceManager::AddSound(const char* name, const char* filePath) {
        if(m_Sounds[name] != nullptr) {
            delete m_Sounds[name];
            m_Sounds.erase(name);
        }
        m_Sounds[name] = new Sound(filePath);
    }

    void ResourceManager::AddSound(const char* name, int format, int freq, int size, void* data) {
        if(m_Sounds[name] != nullptr) {
            delete m_Sounds[name];
            m_Sounds.erase(name);
        }
        m_Sounds[name] = new Sound(format, freq, size, data);
    }
}

