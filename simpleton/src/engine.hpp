#pragma once

#include <functional>
#include "renderer.hpp"
#include "inputs.hpp"
#include "resources/resourceManager.hpp"

#define KEY_EVENT_RELEASE 0
#define KEY_EVENT_PRESS 1
#define KEY_EVENT_REPEAT 2

namespace Simpleton {
    enum EngineFlags : unsigned int {
        EnableOglDebug = 1 << 0
    };

    class Engine {
        private:
            bool m_IsRunning = false; // game will quit when this is false
            Renderer* m_Renderer;
            Inputs* m_Inputs;
            ResourceManager* m_Library;

        public:
            Engine(int screenW, int screenH, char* title, unsigned int flags = 0); // init engine
            ~Engine(); // kill engine in destructor
            void Terminate(); // manually kill engine

            void Run(std::function<void(float dt)> Update); // start game loop, lambda function will be called each frame

            Renderer* GetRenderer();
            Inputs* GetInputs();
            ResourceManager* GetLibrary();

            void CaptureCursor(bool setCapture); // Hide cursor and cature it inside window
            double GetTime(); // Get time in seconds since engine start
            void SetTime(double time); // Set engine time
            
            void Stop(); // set m_isRunning to false
    };
}