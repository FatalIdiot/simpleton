#pragma once

#include <vector>

#define AL_LIBTYPE_STATIC
#include "AL/al.h"
#include "AL/alc.h"

namespace Simpleton {
    class Sound {
        private:
            unsigned int m_SoundId;
            std::vector<char> m_Data;
            int m_Format;
            int m_Freq;

        public:
            Sound();
            Sound(const char* filePath);
            Sound(int format, int freq, int size, void* data);
            ~Sound();

            bool LoadFile(const char* filePath);
            bool LoadData(int format, int freq, int size, void* data);

            unsigned int GetId() const;

        private:
            void Init();
    };
}