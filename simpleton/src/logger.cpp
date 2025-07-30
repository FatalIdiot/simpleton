#include "logger.hpp"

namespace Simpleton {
    unsigned char Log::m_Verbosity = 1;

    void Log::SetVerbosity(LogType verbosityType) {
        m_Verbosity = verbosityType;
    }

    void Log::Write(LogType type, std::string str) {

    }
}