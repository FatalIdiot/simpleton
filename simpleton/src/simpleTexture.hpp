#pragma once

namespace Simpleton {
    class SimpleTexture {
        public:
            unsigned int m_TextureId;
            int m_Width, m_Height, m_Channels;
            unsigned char* m_Data;

        public:
            SimpleTexture(const char* texturePath, bool flip, bool genMipmaps = true);

            void Bind(unsigned short slot);
            void Unbind();
    };
}