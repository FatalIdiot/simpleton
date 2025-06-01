namespace Simpleton {
    void GetConfigs();
    int GetConfigString(char* buffer, int bufferSize, const char* name, const char* sectionName = "Config");
    int GetConfigInt(const char* name, const char* sectionName = "Config");
}