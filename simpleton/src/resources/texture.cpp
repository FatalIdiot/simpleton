#include "texture.hpp"

#include "glad/glad.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

namespace Simpleton {
    void Texture::Init(unsigned char slot) {
        glGenTextures(1, &m_TextureId);
        m_Slot = slot;
        m_FilteringMode = GL_LINEAR;
        m_isLoaded = false;
    }

    Texture::Texture(unsigned char slot) {
        Init(slot);
    }

    Texture::Texture(const char* filePath, unsigned char slot) {
        Init(slot);
        LoadFile(filePath);
    }

    Texture::Texture(int width, int height, int channelsCount, unsigned char* data, unsigned char slot) {
        Init(slot);
        LoadData(width, height, channelsCount, data);
    }

    Texture::~Texture() {
        printf("Terminating texture %u...\n", m_TextureId);
        glDeleteTextures(1, &m_TextureId);

        if(m_Data == nullptr)
            return;
        if(m_LoadType == TextureLoadType::File)
            stbi_image_free(m_Data);
    }

    unsigned int Texture::GetId() {
        return m_TextureId;
    }

    bool Texture::IsLoaded() {
        return m_isLoaded;
    }

    void Texture::SetSlot(unsigned char slot) {
        m_Slot = slot;

        // If texture currently bound - set slot for current texture
        int current2DTexture;
        glGetIntegerv(GL_TEXTURE_BINDING_2D, &current2DTexture);
        if(m_TextureId == current2DTexture) {
            glActiveTexture(GL_TEXTURE0 + m_Slot);
            Bind();
        }
    }

    void Texture::GeneralLoad() {
        Bind();
        
        int mipmapLevel = 0;
        unsigned int colorFormat = (m_ChannelsCount == 3 ? GL_RGB : GL_RGBA);

        unsigned char alignment = m_ChannelsCount == 3 ? 1 : 4;
        glPixelStorei(GL_UNPACK_ALIGNMENT, alignment);
        glPixelStorei(GL_PACK_ALIGNMENT, alignment);
        
        glTexImage2D(GL_TEXTURE_2D, mipmapLevel, colorFormat, m_Width, m_Height, 0, colorFormat, GL_UNSIGNED_BYTE, m_Data);
        
        glGenerateMipmap(GL_TEXTURE_2D);
    }

    bool Texture::LoadFile(const char* filePath) {
        m_Data = stbi_load(filePath, &m_Width, &m_Height, &m_ChannelsCount, 0); 

        if(!m_Data) {
            printf("Failed to load texture data!\n");
            printf("File path: %s\n", filePath);
            return false;
        }

        m_LoadType = TextureLoadType::File;

        GeneralLoad();

        printf("Loaded texture %u from file: %s\n", m_TextureId, filePath);
        printf("Width: %u, Height: %u, Channels: %u\n", m_Width, m_Height, m_ChannelsCount);
        m_isLoaded = true;

        return true;
    }

    bool Texture::LoadData(int width, int height, int channelsCount, unsigned char* data) {
        m_Data = data;
        m_Width = width;
        m_Height = height;
        m_ChannelsCount = channelsCount;
        m_LoadType = TextureLoadType::Data;

        GeneralLoad();

        printf("Loaded texture %u from data.\n", m_TextureId);
        printf("Width: %u, Height: %u, Channels: %u\n", m_Width, m_Height, m_ChannelsCount);
        m_isLoaded = true;

        return true;
    }

    void Texture::SetFiltering(TextureFiltering filteringMode) {
        int filter;
        switch(filteringMode) {
            case TextureFiltering::Nearest:     
                filter = GL_NEAREST;
                break;
            case TextureFiltering::Linear:     
                filter = GL_LINEAR;
                break;
        }
        m_FilteringMode = filter;
    }

    void Texture::Bind() {
        glActiveTexture(GL_TEXTURE0 + m_Slot);

        glBindTexture(GL_TEXTURE_2D, m_TextureId);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, m_FilteringMode);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, m_FilteringMode);
    }

    void Texture::Unbind() {
        glBindTexture(GL_TEXTURE_2D, 0);
    }
}