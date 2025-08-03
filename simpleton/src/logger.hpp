/*
    Class for engine debugging, internal usage, not meant to be used in game projects the engine is used in.
*/
#pragma once

#include <string>
#include <format>
#include <iostream>

// OpenAL errors
#define AL_NO_ERROR             0
#define AL_INVALID_NAME         0xA001
#define AL_INVALID_ENUM         0xA002
#define AL_INVALID_VALUE        0xA003
#define AL_INVALID_OPERATION    0xA004
#define AL_OUT_OF_MEMORY        0xA005

#define LogErr(format, ...) Simpleton::Log::WriteErr(__FILE__, __LINE__, format, __VA_ARGS__)
#define LogMsg(format, ...) Simpleton::Log::WriteMsg(format, __VA_ARGS__)
#define LogOal() Simpleton::Log::WriteOal(alGetError(), __FILE__, __LINE__)

namespace Simpleton {
    enum LogType {
        Error = 0,
        Msg = 1
    };

    class Log {
        private:
            static unsigned char m_Verbosity;

        public:
            static void SetVerbosity(LogType verbosityType);

            // Log last OpenAL error
            static void WriteOal(int errorCode, const char* filePath, int lineNum) {
                switch(errorCode) {
                    case AL_INVALID_NAME:
                        WriteErr(filePath, lineNum, "OpenAL: Invalid Name");
                        break;
                    case AL_INVALID_ENUM:
                        WriteErr(filePath, lineNum, "OpenAL: Invalid Enum");
                        break;
                    case AL_INVALID_VALUE:
                        WriteErr(filePath, lineNum, "OpenAL: Invalid Value");
                        break;
                    case AL_INVALID_OPERATION:
                        WriteErr(filePath, lineNum, "OpenAL: Invalid Operation");
                        break;
                    case AL_OUT_OF_MEMORY:
                        WriteErr(filePath, lineNum, "OpenAL: Out of Memory");
                        break;
                    default:
                        return;
                }
            }

            template<typename... Args>
            static void WriteMsg(std::format_string<Args...> format, Args&&... args) {
                if(Log::m_Verbosity < LogType::Msg)
                    return;

                Log::Write(
                    LogType::Msg,
                    std::format(format, std::forward<Args>(args)...) + '\n'
                );
            }

            template<typename... Args>
            static void WriteErr(const char* filePath, int lineNum, std::format_string<Args...> format, Args&&... args) {
                if(Log::m_Verbosity < LogType::Error)
                    return;

                Log::Write(
                    LogType::Error,
                    std::format("\nError [{} : {}]:\n", filePath, lineNum) + std::format(format, std::forward<Args>(args)...) + "\n\n"
                );
            }

        private:
            // internal function to be wraped with type specific functions
            static void Write(LogType type, std::string format) {
                if(type == LogType::Msg)
                    std::cout << format;
                else
                    std::cerr << format;
            }
    };
}