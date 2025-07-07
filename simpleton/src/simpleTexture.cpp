// #include "simpleTexture.hpp"

// #define STB_IMAGE_IMPLEMENTATION
// #include "stb_image.h"
// #include "glad/glad.h"
// #include <iostream>

// namespace Simpleton {
//     SimpleTexture::SimpleTexture(const char* texturePath, bool flip, bool genMipmaps) {
//         glGenTextures(1, &m_TextureId);
//         glBindTexture(GL_TEXTURE_2D, m_TextureId);

//         stbi_set_flip_vertically_on_load(flip);
//         m_Data = stbi_load(texturePath, &m_Width, &m_Height, &m_Channels, 0);
//         std::cout << "Loaded channels: " << m_Channels << std::endl;
//         if(m_Data) {
//             glTexImage2D(GL_TEXTURE_2D, 0, m_Channels == 4 ? GL_RGBA : GL_RGB, m_Width, m_Height, 0, m_Channels == 4 ? GL_RGBA : GL_RGB,
//             GL_UNSIGNED_BYTE, m_Data);

//             stbi_image_free(m_Data);
//         } else {
//             std::cout << "ERROR: Failed to load texture data!\n";
//         }

//         glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
//         glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);

//         glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
//         glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

//         if(genMipmaps)
//             glGenerateMipmap(GL_TEXTURE_2D);

//         glBindTexture(GL_TEXTURE_2D, 0);
//     }

//     void SimpleTexture::Bind(unsigned short slot) {
//         glActiveTexture(GL_TEXTURE0 + slot);
//         glBindTexture(GL_TEXTURE_2D, m_TextureId);
//     }

//     void SimpleTexture::Unbind() {
//         glBindTexture(GL_TEXTURE_2D, 0);
//     }
// }