#include "logger.hpp"

namespace Simpleton {
    unsigned char Log::m_Verbosity = 1;
    std::ofstream Log::logFile;
    bool Log::enableFileLog = true;
}