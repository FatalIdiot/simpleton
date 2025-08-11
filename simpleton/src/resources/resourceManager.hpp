#pragma once

#include <filesystem>
namespace fs = std::filesystem;

#include <map>
#include <string>
#include "texture.hpp"
#include "sound.hpp"

namespace Simpleton {
    class Engine;

    class ResourceManager {
        friend class Engine; 

        private:
            std::map<std::string, Texture*> m_Textures;
            std::map<std::string, Sound*> m_Sounds;

        public:
            Texture* GetTexture(const char* name);
            void AddTexture(const char* name, Texture* texture);
            void AddTexture(const char* name, fs::path filePath, unsigned char slot = 0);
            void AddTexture(const char* name, int width, int height, int channelsCount, unsigned char* data, unsigned char slot = 0);
    
            Sound* GetSound(const char* name);
            void AddSound(const char* name, Sound* sound);
            void AddSound(const char* name, fs::path filePath);
            void AddSound(const char* name, int format, int freq, int size, void* data);

        private:
            void Init();
            void Terminate();
    };
}