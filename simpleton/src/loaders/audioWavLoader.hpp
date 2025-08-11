#pragma once

#include <fstream>
#include <vector>

struct WavData {
    std::vector<char> data;
    int format;
    int frequency;
};

// Helper: read little-endian values
template<typename T>
T readLE(std::ifstream &file);
WavData loadWavFile(const std::string &filename);

// Generates a 1 second AL_FORMAT_MONO16 wav file of 44100 sample rate.
WavData GenTestWav();