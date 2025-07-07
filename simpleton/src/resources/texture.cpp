#include "texture.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "glad/glad.h"

namespace Simpleton {
    Texture::Texture() {
        glGenTextures(1, &m_TextureId);
    }

    Texture::~Texture() {
        
    }

    void Texture::Bind() {
        glBindTexture(GL_TEXTURE_2D, m_TextureId);
    }

    void Texture::Unbind() {
        glBindTexture(GL_TEXTURE_2D, 0);
    }
}