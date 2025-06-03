#include <windows.h>
#include <stdio.h>

#include "config.hpp"

namespace Simpleton {
    int GetConfigString(wchar_t* buffer, int bufferSize, const WCHAR* name, const WCHAR* sectionName) {
        int pulledChars = GetPrivateProfileString (
            sectionName,
            name,
            NULL, 
            buffer,
            bufferSize,
            (const WCHAR*)"./config.ini"
        );

        return pulledChars;
    }

    int GetConfigInt(const WCHAR* name, const WCHAR* sectionName) {
        return GetPrivateProfileInt (
            sectionName,
            name,
            0,
            (const WCHAR*)"./config.ini"
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