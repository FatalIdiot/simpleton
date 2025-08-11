#pragma once

namespace Simpleton {
    enum TextureLoadType {
        File,
        Data
    };

    enum TextureFiltering {
        Nearest,
        Linear
    };

    class Texture {
        private:
            unsigned char m_Slot;
            int m_FilteringMode;

            unsigned int m_TextureId;
            TextureLoadType m_LoadType;

            int m_Width, m_Height, m_ChannelsCount;
            unsigned char *m_Data;

            bool m_isLoaded;

        public:
            Texture(unsigned char slot = 0);
            Texture(const char* filePath, unsigned char slot = 0);
            Texture(int width, int height, int channelsCount, unsigned char* data, unsigned char slot = 0);
            ~Texture();

            unsigned int GetId() const;
            bool IsLoaded();
            void SetSlot(unsigned char slot);

            bool LoadFile(const char* filePath);
            bool LoadData(int width, int height, int channelsCount, unsigned char* data);

            void Bind() const;
            void Unbind() const;

            void SetFiltering(TextureFiltering filteringMode);

        private:
            void Init(unsigned char slot);
            void GeneralLoad();
    };
}