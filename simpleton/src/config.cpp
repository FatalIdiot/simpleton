#include <windows.h>
#include <stdio.h>

#include "config.hpp"

namespace Simpleton {
    int GetConfigString(char* buffer, int bufferSize, const char* name, const char* sectionName) {
        int pulledChars = GetPrivateProfileString (
            sectionName,
            name,
            NULL, 
            buffer,
            bufferSize,
            "./config.ini"
        );

        return pulledChars;
    }

    int GetConfigInt(const char* name, const char* sectionName) {
        return GetPrivateProfileInt (
            sectionName,
            name,
            0,
            "./config.ini"
        );
    }

    void GetConfigs() {
        // Test configs load
        // char iniBuffer[256];
        // GetConfigString(iniBuffer, 256, "Test Line");
        // printf("%.*s\n", 256, iniBuffer);

        // int pulledInt = GetConfigInt("Test Number");
        // printf("%d\n", pulledInt);
    }
}