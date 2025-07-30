#pragma once
#define M_PI 3.14159265358979323846

#include <fstream>
#include <vector>
#include <cstdint>
#include <iostream>
#include <cstring>
#include <stdexcept>

struct WavData {
    std::vector<char> data;
    int format;
    int frequency;
};

// Helper: read little-endian values
template<typename T>
T readLE(std::ifstream &file) {
    T value;
    file.read(reinterpret_cast<char*>(&value), sizeof(T));
    return value;
}

WavData loadWavFile(const std::string &filename) {
    std::ifstream file(filename, std::ios::binary);
    if (!file) throw std::runtime_error("Failed to open file");

    // Check RIFF header
    char riff[4];
    file.read(riff, 4);
    if (std::memcmp(riff, "RIFF", 4) != 0) throw std::runtime_error("Not a RIFF file");

    readLE<uint32_t>(file); // file size
    char wave[4];
    file.read(wave, 4);
    if (std::memcmp(wave, "WAVE", 4) != 0) throw std::runtime_error("Not a WAVE file");

    uint16_t audioFormat = 0;
    uint16_t numChannels = 0;
    uint32_t sampleRate = 0;
    uint16_t bitsPerSample = 0;
    std::vector<char> audioData;

    // Parse chunks
    while (file && !file.eof()) {
        char chunkId[4];
        file.read(chunkId, 4);
        uint32_t chunkSize = readLE<uint32_t>(file);
        if (!file) break;

        if (std::memcmp(chunkId, "fmt ", 4) == 0) {
            audioFormat = readLE<uint16_t>(file);
            numChannels = readLE<uint16_t>(file);
            sampleRate = readLE<uint32_t>(file);
            readLE<uint32_t>(file); // byteRate
            readLE<uint16_t>(file); // blockAlign
            bitsPerSample = readLE<uint16_t>(file);

            // Skip any extra fmt bytes
            if (chunkSize > 16) file.seekg(chunkSize - 16, std::ios::cur);
        }
        else if (std::memcmp(chunkId, "data", 4) == 0) {
            audioData.resize(chunkSize);
            file.read(audioData.data(), chunkSize);
        }
        else {
            // Skip unhandled chunks
            file.seekg(chunkSize, std::ios::cur);
        }
    }

    if (audioFormat != 1) throw std::runtime_error("Unsupported WAV format (must be PCM)");

    ALenum format;
    if (bitsPerSample == 8) {
        format = (numChannels == 1) ? AL_FORMAT_MONO8 : AL_FORMAT_STEREO8;
    } else if (bitsPerSample == 16) {
        format = (numChannels == 1) ? AL_FORMAT_MONO16 : AL_FORMAT_STEREO16;
    } else {
        throw std::runtime_error("Unsupported WAV bit depth");
    }

    return { std::move(audioData), format, static_cast<int>(sampleRate) };
}

// Generates a 1 second AL_FORMAT_MONO16 wav file of 44100 sample rate.
// int dataSize;
// short* testData = GenTestWav(dataSize);
// alBufferData(m_SoundId, AL_FORMAT_MONO16, testData, dataSize, 44100);
short* GenTestWav(int &dataSize) {
    int sampleRate = 44100;
    int duration = 1; // seconds
    std::vector<short> samples(sampleRate * duration);
    for (int i = 0; i < sampleRate * duration; ++i) {
        samples[i] = static_cast<short>(32760 * std::sin((2.f * M_PI * 440.f * i) / sampleRate));
    }
    dataSize = static_cast<int>(samples.size() * sizeof(short));
    return samples.data();
}