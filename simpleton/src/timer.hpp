#pragma once

#include <chrono>

namespace Simpleton {
    using namespace std::chrono;
    using namespace std::literals::chrono_literals;

    class Timer {
        public:
            enum TimerState { Running, Paused, Stopped };

        private:
            time_point<steady_clock> m_StartTime; // start time after creation or Start call
            time_point<steady_clock> m_LastElapsed; // time passed since last Elapsed call
            duration<float> m_PassedTime; // passed time including paused periods
            TimerState m_State;
            
        public:
            Timer();
            ~Timer();

            void Start();
            void Pause();
            void Clear(); // Stop timer

            float GetPassedTime(); // get time since Start
            float Elapsed(); // get time from last Elapsed call or from timer start

            bool isRunning() const;
            bool isPaused() const;
    };
}