#pragma once

#include <string>

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
            static void Write(LogType type, std::string str);
    };
}