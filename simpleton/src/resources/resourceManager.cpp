#include "../utils.hpp"
#include "resourceManager.hpp"
#include "texture.hpp"
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
    }

    void ResourceManager::Terminate() {
        LogMsg("Resource Manager Terminate...");

        // Delete all textures
        std::map<std::string, Texture*>::iterator it;
        for (it = m_Textures.begin(); it != m_Textures.end(); it++)
        {
            delete it->second;
        }
        m_Textures.clear();
    }

    Texture* ResourceManager::GetTexture(const char* name) {
        // return default texture if failed to load
        if(m_Textures[name] == nullptr || !m_Textures[name]->IsLoaded())
            return m_Textures["default"];
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
}

