#include "audioWavLoader.hpp"
#include "../logger.hpp"

#define M_PI 3.14159265358979323846
#define AL_FORMAT_MONO8     0x1100
#define AL_FORMAT_MONO16    0x1101
#define AL_FORMAT_STEREO8   0x1102
#define AL_FORMAT_STEREO16  0x1101

#include <cstdint>
#include <iostream>
#include <cstring>
#include <stdexcept>
#include <climits>

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

    int format;
    if (bitsPerSample == 8) {
        format = (numChannels == 1) ? AL_FORMAT_MONO8 : AL_FORMAT_STEREO8;
    } else if (bitsPerSample == 16) {
        format = (numChannels == 1) ? AL_FORMAT_MONO16 : AL_FORMAT_STEREO16;
    } else {
        throw std::runtime_error("Unsupported WAV bit depth");
    }
    LogMsg("Loaded WAV file.");
    LogMsg("Format: {} {}, Sample Rate: {}", bitsPerSample, numChannels == 1 ? "MONO" : "STEREO", static_cast<int>(sampleRate));
    return { std::move(audioData), format, static_cast<int>(sampleRate) * 2 };
}

WavData GenTestWav() {
    int sampleRate = 44100;
    int duration = 1; // seconds
    std::vector<char> samples(sampleRate * duration);
    for (int i = 0; i < sampleRate * duration; i++) {
        samples[i] = static_cast<char>(CHAR_MAX * std::sin((2.f * M_PI * 440.f * i) / sampleRate));
    }
    LogMsg("Generated test audio.");
    return { std::move(samples), AL_FORMAT_MONO8, 44100 };
}