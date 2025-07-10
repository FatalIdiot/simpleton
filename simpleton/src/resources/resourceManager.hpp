#pragma once

#include <map>
#include <string>
#include "texture.hpp"

namespace Simpleton {
    class Engine;

    class ResourceManager {
        friend class Engine; 

        private:
            std::map<std::string, Texture*> m_Textures;

        public:
            Texture* GetTexture(const char* name);
            void AddTexture(const char* name, Texture* texture);
            void AddTexture(const char* name, const char* filePath, unsigned char slot = 0);
            void AddTexture(const char* name, int width, int height, int channelsCount, unsigned char* data, unsigned char slot = 0);
    
        private:
            void Init();
            void Terminate();
    };
}