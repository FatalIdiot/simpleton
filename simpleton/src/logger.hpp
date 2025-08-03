#pragma once

#include <string>
#include <format>
#include <iostream>

#define LogErr(format, ...) Simpleton::Log::WriteErr(__FILE__, __LINE__, format, __VA_ARGS__)
#define LogMsg(format, ...) Simpleton::Log::WriteMsg(format, __VA_ARGS__)

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

            template<typename... Args>
            static void WriteMsg(std::format_string<Args...> format, Args&&... args) {
                if(Log::m_Verbosity < LogType::Msg)
                    return;

                Log::Write(
                    std::format(format, std::forward<Args>(args)...) + '\n'
                );
            }

            template<typename... Args>
            static void WriteErr(const char* filePath, int lineNum, std::format_string<Args...> format, Args&&... args) {
                if(Log::m_Verbosity < LogType::Error)
                    return;

                Log::Write(
                    std::format("\nError [{} : {}]:\n", filePath, lineNum) + std::format(format, std::forward<Args>(args)...) + "\n\n"
                );
            }

        private:
            // internal function to be wraped with type specific functions
            static void Write(std::string format) {
                std::cout << format;
            }
    };
}