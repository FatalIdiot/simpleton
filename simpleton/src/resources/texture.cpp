#include "texture.hpp"

#include "glad/glad.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

namespace Simpleton {
    void Texture::Init(unsigned char slot) {
        glGenTextures(1, &m_TextureId);
        m_Slot = slot;
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

    bool Texture::LoadFile(const char* filePath) {
        unsigned char *m_Data = stbi_load(filePath, &m_Width, &m_Height, &m_ChannelsCount, 0); 

        if(!m_Data) {
            printf("Failed to load texture data!\n");
            printf("File path: %s\n", filePath);
            return false;
        }

        m_LoadType = TextureLoadType::File;

        Bind();

        int mipmapLevel = 0;
        unsigned int colorFormat = (m_ChannelsCount == 3 ? GL_RGB : GL_RGBA);

        glTexImage2D(GL_TEXTURE_2D, mipmapLevel, colorFormat, m_Width, m_Height, 0, colorFormat, GL_UNSIGNED_BYTE, m_Data);
        glGenerateMipmap(GL_TEXTURE_2D);

        printf("Loaded texture %u from file: %s\n", m_TextureId, filePath);
        printf("Width: %u, Height: %u, Channels: %u\n", m_Width, m_Height, m_ChannelsCount);

        return true;
    }

    bool Texture::LoadData(int width, int height, int channelsCount, unsigned char* data) {
        m_Data = data;
        m_Width = width;
        m_Height = height;
        m_ChannelsCount = channelsCount;
        m_LoadType = TextureLoadType::Data;

        Bind();

        int mipmapLevel = 0;
        unsigned int colorFormat = m_ChannelsCount == 3 ? GL_RGB : GL_RGBA;

        glTexImage2D(GL_TEXTURE_2D, mipmapLevel, colorFormat, m_Width, m_Height, 0, colorFormat, GL_UNSIGNED_BYTE, m_Data);
        glGenerateMipmap(GL_TEXTURE_2D);

        printf("Loaded texture %u from data.\n", m_TextureId);
        printf("Width: %u, Height: %u, Channels: %u\n", m_Width, m_Height, m_ChannelsCount);

        return true;
    }

    void Texture::Bind() {
        glActiveTexture(GL_TEXTURE0 + m_Slot);
        glBindTexture(GL_TEXTURE_2D, m_TextureId);
    }

    void Texture::Unbind() {
        glBindTexture(GL_TEXTURE_2D, 0);
    }
}