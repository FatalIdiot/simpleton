#include "timer.hpp"

namespace Simpleton {
    using namespace std::chrono;
    using namespace std::literals::chrono_literals;

    Timer::Timer() {
        m_StartTime = steady_clock::now();
        m_LastElapsed = steady_clock::now();
        m_PassedTime = seconds::zero();
    }

    Timer::~Timer() {
    }

    void Timer::Start() {
        if(m_State == TimerState::Running)
            return;

        m_StartTime = steady_clock::now();
        m_State = TimerState::Running;
    }

    void Timer::Pause() {
        if(m_State != TimerState::Running)
            return;

        m_PassedTime += steady_clock::now() - m_StartTime;
        m_State = TimerState::Paused;
    }

    void Timer::Clear() {
        m_PassedTime = seconds::zero();
        m_State = TimerState::Stopped;
    }

    float Timer::Elapsed() {
        if(m_State != TimerState::Running)
            return 0.0f;

        duration<float> timePassed;
        timePassed = steady_clock::now() - m_LastElapsed;
        m_LastElapsed = steady_clock::now();
        return timePassed.count();
    }

    float Timer::GetPassedTime() {
        duration<float> timePassed = m_PassedTime;
        if(m_State == TimerState::Running) {
            timePassed += steady_clock::now() - m_StartTime;
        }
        return timePassed.count();
    }

    bool Timer::isRunning() const {
        return m_State == TimerState::Running;
    }

    bool Timer::isPaused() const {
        return m_State == TimerState::Paused;
    }
}