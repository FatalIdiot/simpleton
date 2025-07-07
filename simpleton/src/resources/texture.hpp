#pragma once

namespace Simpleton {
    class Texture {
        private:
            unsigned int m_TextureId;

        public:
            Texture();
            ~Texture();

            void Bind();
            void Unbind();
    };
}