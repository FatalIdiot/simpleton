#pragma once

#include <functional>
#include <chrono>
#include <vector>
#include <map>
#include <queue>
#include <string>

// OpenAL defines
#define SOUND_FORMAT_MONO8              0x1100
#define SOUND_FORMAT_MONO16             0x1101
#define SOUND_FORMAT_STEREO8            0x1102
#define SOUND_FORMAT_STEREO16           0x1103
#define SOUND_FORMAT_MONO_FLOAT32       0x10010
#define SOUND_FORMAT_STEREO_FLOAT32     0x10011

// Key bindings
#define 	VK_KEY_SPACE   32
#define 	VK_KEY_APOSTROPHE   39 /* ' */
#define 	VK_KEY_COMMA   44 /* , */
#define 	VK_KEY_MINUS   45 /* - */
#define 	VK_KEY_PERIOD   46 /* . */
#define 	VK_KEY_SLASH   47 /* / */
#define 	VK_KEY_0   48
#define 	VK_KEY_1   49
#define 	VK_KEY_2   50
#define 	VK_KEY_3   51
#define 	VK_KEY_4   52
#define 	VK_KEY_5   53
#define 	VK_KEY_6   54
#define 	VK_KEY_7   55
#define 	VK_KEY_8   56
#define 	VK_KEY_9   57
#define 	VK_KEY_SEMICOLON   59 /* ; */
#define 	VK_KEY_EQUAL   61 /* = */
#define 	VK_KEY_A   65
#define 	VK_KEY_B   66
#define 	VK_KEY_C   67
#define 	VK_KEY_D   68
#define 	VK_KEY_E   69
#define 	VK_KEY_F   70
#define 	VK_KEY_G   71
#define 	VK_KEY_H   72
#define 	VK_KEY_I   73
#define 	VK_KEY_J   74
#define 	VK_KEY_K   75
#define 	VK_KEY_L   76
#define 	VK_KEY_M   77
#define 	VK_KEY_N   78
#define 	VK_KEY_O   79
#define 	VK_KEY_P   80
#define 	VK_KEY_Q   81
#define 	VK_KEY_R   82
#define 	VK_KEY_S   83
#define 	VK_KEY_T   84
#define 	VK_KEY_U   85
#define 	VK_KEY_V   86
#define 	VK_KEY_W   87
#define 	VK_KEY_X   88
#define 	VK_KEY_Y   89
#define 	VK_KEY_Z   90
#define 	VK_KEY_LEFT_BRACKET   91 /* [ */
#define 	VK_KEY_BACKSLASH   92 /* \ */
#define 	VK_KEY_RIGHT_BRACKET   93 /* ] */
#define 	VK_KEY_GRAVE_ACCENT   96 /* ` */
#define 	VK_KEY_WORLD_1   161 /* non-US #1 */
#define 	VK_KEY_WORLD_2   162 /* non-US #2 */
#define 	VK_KEY_ESCAPE   256
#define 	VK_KEY_ENTER   257
#define 	VK_KEY_TAB   258
#define 	VK_KEY_BACKSPACE   259
#define 	VK_KEY_INSERT   260
#define 	VK_KEY_DELETE   261
#define 	VK_KEY_RIGHT   262
#define 	VK_KEY_LEFT   263
#define 	VK_KEY_DOWN   264
#define 	VK_KEY_UP   265
#define 	VK_KEY_PAGE_UP   266
#define 	VK_KEY_PAGE_DOWN   267
#define 	VK_KEY_HOME   268
#define 	VK_KEY_END   269
#define 	VK_KEY_CAPS_LOCK   280
#define 	VK_KEY_SCROLL_LOCK   281
#define 	VK_KEY_NUM_LOCK   282
#define 	VK_KEY_PRINT_SCREEN   283
#define 	VK_KEY_PAUSE   284
#define 	VK_KEY_F1   290
#define 	VK_KEY_F2   291
#define 	VK_KEY_F3   292
#define 	VK_KEY_F4   293
#define 	VK_KEY_F5   294
#define 	VK_KEY_F6   295
#define 	VK_KEY_F7   296
#define 	VK_KEY_F8   297
#define 	VK_KEY_F9   298
#define 	VK_KEY_F10   299
#define 	VK_KEY_F11   300
#define 	VK_KEY_F12   301
#define 	VK_KEY_F13   302
#define 	VK_KEY_F14   303
#define 	VK_KEY_F15   304
#define 	VK_KEY_F16   305
#define 	VK_KEY_F17   306
#define 	VK_KEY_F18   307
#define 	VK_KEY_F19   308
#define 	VK_KEY_F20   309
#define 	VK_KEY_F21   310
#define 	VK_KEY_F22   311
#define 	VK_KEY_F23   312
#define 	VK_KEY_F24   313
#define 	VK_KEY_F25   314
#define 	VK_KEY_KP_0   320
#define 	VK_KEY_KP_1   321
#define 	VK_KEY_KP_2   322
#define 	VK_KEY_KP_3   323
#define 	VK_KEY_KP_4   324
#define 	VK_KEY_KP_5   325
#define 	VK_KEY_KP_6   326
#define 	VK_KEY_KP_7   327
#define 	VK_KEY_KP_8   328
#define 	VK_KEY_KP_9   329
#define 	VK_KEY_KP_DECIMAL   330
#define 	VK_KEY_KP_DIVIDE   331
#define 	VK_KEY_KP_MULTIPLY   332
#define 	VK_KEY_KP_SUBTRACT   333
#define 	VK_KEY_KP_ADD   334
#define 	VK_KEY_KP_ENTER   335
#define 	VK_KEY_KP_EQUAL   336
#define 	VK_KEY_LEFT_SHIFT   340
#define 	VK_KEY_LEFT_CONTROL   341
#define 	VK_KEY_LEFT_ALT   342
#define 	VK_KEY_LEFT_SUPER   343
#define 	VK_KEY_RIGHT_SHIFT   344
#define 	VK_KEY_RIGHT_CONTROL   345
#define 	VK_KEY_RIGHT_ALT   346
#define 	VK_KEY_RIGHT_SUPER   347
#define 	VK_KEY_MENU   348 
#define 	VK_KEY_LAST   VK_KEY_MENU

// Mouse bindings
#define MOUSE_BUTTON_1         0
#define MOUSE_BUTTON_2         1
#define MOUSE_BUTTON_3         2
#define MOUSE_BUTTON_4         3
#define MOUSE_BUTTON_5         4
#define MOUSE_BUTTON_6         5
#define MOUSE_BUTTON_7         6
#define MOUSE_BUTTON_8         7
#define MOUSE_BUTTON_LAST      MOUSE_BUTTON_8
#define MOUSE_BUTTON_LEFT      MOUSE_BUTTON_1
#define MOUSE_BUTTON_RIGHT     MOUSE_BUTTON_2
#define MOUSE_BUTTON_MIDDLE    MOUSE_BUTTON_3

// Events for keys and mouse
#define KEY_EVENT_RELEASE 0
#define KEY_EVENT_PRESS 1
#define KEY_EVENT_REPEAT 2

typedef struct GLFWwindow GLFWwindow;

namespace Simpleton {
    using namespace std::chrono;
    using namespace std::literals::chrono_literals;

    template <typename T>
    struct Point
    {
        T x, y;
    };

    template <typename T>
    struct Color
    {
        T r, g, b, a;
    };

    template <typename T>
    struct Rect 
    {
        T x, y;
        T w, h;
    };

    template <typename T>
    struct Circle
    {
        T x, y;
        T radius;
    };

    


    typedef struct {
        unsigned int type; // OpenGL type of data
        unsigned int count;
        bool normalized;
    } MeshAttribute;

    class Mesh {
        private:
            unsigned int m_Type;
            unsigned int m_VBO;

            unsigned int m_VAO;
            std::vector<MeshAttribute> m_Attributes; // attributes data is saved for recalculations

            unsigned int m_EBO;

            unsigned int m_DataSize;
            unsigned int m_IndexCount;
            unsigned int m_AttribStride;

        public:
            Mesh();
            Mesh(unsigned int type, const void* data, unsigned int size);
            ~Mesh();

            // Vertex Buffer Object - must be Interleaved data
            void SetBufferData(unsigned int type, const void* data, unsigned int size);

            // Vertex Array Object
            void SetAttributes(MeshAttribute attributes[], short count); // Add all attributes as array
            void AddAttribute(MeshAttribute newAttribute); // Add attribute to the list
            void ClearAttributes();
            unsigned int GetAttribCount();
            void EnableAttribute(short index);
            void DisableAttribute(short index);

            // Element Buffer Object
            void SetIndexData(unsigned int* data, unsigned int count);
            void RemoveIndexData();

            void Bind();
            void Draw();

        private:
            void InitMesh();
            static unsigned int GetTypeSize(unsigned int type);
            void Terminate();
    };

    enum ShaderType {
        VertexShader,
        FragmentShader
    };

    class Shader {
        private:
            unsigned int m_VertexShader;
            unsigned int m_FragmentShader; 
            unsigned int m_ShaderProgId;
            bool m_IsValid;
            char m_ErrorLog[512];

        public:
            Shader();
            ~Shader();

            bool CheckProgramValid();

            bool AddShaderSource(ShaderType type, const char* code);
            bool AddShaderFile(ShaderType type, const char* filePath);

            bool Compile();

            // set uniforms
            void SetUniform(const char* name, float x, float y, float z, float w);
            void SetUniform(const char* name, int i);

            void Bind();
            void Unbind();

        private:
            bool CheckShaderValid(ShaderType type);
            void Terminate();
    };

    enum TextureLoadType {
        File,
        Data
    };

    enum TextureFiltering {
        Nearest,
        Linear
    };

    class Texture {
        private:
            unsigned char m_Slot;
            int m_FilteringMode;

            unsigned int m_TextureId;
            TextureLoadType m_LoadType;

            int m_Width, m_Height, m_ChannelsCount;
            unsigned char *m_Data;

            bool m_isLoaded;

        public:
            Texture(unsigned char slot = 0);
            Texture(const char* filePath, unsigned char slot = 0);
            Texture(int width, int height, int channelsCount, unsigned char* data, unsigned char slot = 0);
            ~Texture();

            unsigned int GetId();
            bool IsLoaded();
            void SetSlot(unsigned char slot);

            bool LoadFile(const char* filePath);
            bool LoadData(int width, int height, int channelsCount, unsigned char* data);

            void Bind();
            void Unbind();

            void SetFiltering(TextureFiltering filteringMode);

        private:
            void Init(unsigned char slot);
            void GeneralLoad();
    };

    class Sound {
        private:
            unsigned int m_SoundId;
            std::vector<char> m_Data;
            int m_Format;
            int m_Freq;

        public:
            Sound();
            Sound(const char* filePath);
            Sound(int format, int freq, int size, void* data);
            ~Sound();

            bool LoadFile(const char* filePath);
            bool LoadData(int format, int freq, int size, void* data);

            unsigned int GetId() const;

        private:
            void Init();
    };

    class SoundSource {
        private:
            unsigned int m_SoundSourceId;
        
        public:
            SoundSource();
            ~SoundSource();
            void AttachSound(Sound* sound);

            void SetPosition(float x, float y, float z);
            void SetVelocity(float x, float y, float z);
            void SetPitch(float pitch);
            void SetGain(float gain);
            void SetLooping(bool loop);

            void Play();
    };

    class AudioManager {
        friend class Engine; 

        private:
            Engine* m_Engine = nullptr;
            void* m_Device;
            void* m_Context;

        public:
            AudioManager();
            
        private:
            void Init(Engine* engine);
            void Terminate();
    };

    class ResourceManager {
        friend class Engine; 

        private:
            std::map<std::string, Texture*> m_Textures;
            std::map<std::string, Sound*> m_Sounds;

        public:
            Texture* GetTexture(const char* name);
            void AddTexture(const char* name, Texture* texture);
            void AddTexture(const char* name, const char* filePath, unsigned char slot = 0);
            void AddTexture(const char* name, int width, int height, int channelsCount, unsigned char* data, unsigned char slot = 0);
    
            Sound* GetSound(const char* name);
            void AddSound(const char* name, Sound* sound);
            void AddSound(const char* name, const char* filePath);
            void AddSound(const char* name, int format, int freq, int size, void* data);

        private:
            void Init();
            void Terminate();
    };

    class Renderer {
        friend class Engine; 
        
        public:
            GLFWwindow* m_Window;
            void* m_Engine;
            std::function<void(int& width, int& height)> m_ResizeCallback = NULL; // callback functions to customize window resize result

        private:
            Mesh m_PrimitiveMesh;
            Shader m_PrimitiveShader;
            Shader m_TextureShader;

        public:
            template <typename T>
            void GetWindowSize(T& width, T& height);

            bool WindowShouldClose(); // return if GLFW window must be closed
            void SetWireframeRendering(bool enable); // enable rendering wireframes
            void SetWindowResizable(bool setResizable);
            void SetClearColor(float r, float g, float b);
            void DepthTest(bool enable);

            void FillTriangle(Color<float> color, Point<int> pos1, Point<int> pos2, Point<int> pos3);
            void FillRect(Color<float> color, Rect<int> area);
            void FillCircle(Color<float> color, Circle<int> circle, unsigned short pointsCount = 25);

            void DrawLine(Color<float> color, Point<int> pointA, Point<int> pointB);
            void DrawTriangle(Color<float> color, Point<int> pos1, Point<int> pos2, Point<int> pos3);
            void DrawRect(Color<float> color, Rect<int> area);
            void DrawCircle(Color<float> color, Circle<int> circle, unsigned short pointsCount = 25);
            
            void BlitTexture(Texture* texture, Rect<int> destRect, Rect<float> srcRect = {0.0f, 0.0f, 1.0f, 1.0f});

        private:
            bool Init(void* engine, GLFWwindow* window);
            void Terminate();
            void ClearScreen();
            void SwapBuffers();
    };

    enum EngineFlags : unsigned int {
        EnableOglDebug = 1 << 0
    };

    class InputsManager;
    class AudioManager;

    class Engine {
        private:
            bool m_IsRunning = false; // game will quit when this is false
            Renderer* m_Renderer;
            InputsManager* m_Inputs;
            ResourceManager* m_Library;
            AudioManager* m_Audio;

        public:
            Engine(int screenW, int screenH, char* title, unsigned int flags = 0); // init engine
            ~Engine(); // kill engine in destructor
            void Terminate(); // manually kill engine

            void Run(std::function<void(float dt)> Update); // start game loop, lambda function will be called each frame

            Renderer* GetRenderer();
            InputsManager* GetInputs();
            ResourceManager* GetLibrary();
            AudioManager* GetAudio();

            void CaptureCursor(bool setCapture); // Hide cursor and cature it inside window
            double GetTime(); // Get time in seconds since engine start
            void SetTime(double time); // Set engine time
            
            void Stop(); // set m_isRunning to false
    };

    enum InputEventType {
        KeyboardKey,
        MouseKey
    };

    struct InputEvent {
        InputEventType type;
        int key;
        int action;
        double time;
        Point<unsigned int> mousePos;

        InputEvent(InputEventType eType, int eKey, int eAction, double eTime, Point<unsigned int> eMousePos) :
            type(eType), key(eKey), action(eAction), time(eTime), mousePos(eMousePos) {}
    };

    class InputsManager {
        friend class Engine; 

        private:
            Engine* m_Engine = nullptr;
            unsigned int m_MouseX, m_MouseY;
            std::queue<InputEvent> m_Events; 
            std::map<int, std::vector< std::function<void(InputEvent e)> >> m_Bindings;

        public:
            void AddBinding(int key, std::function<void(InputEvent e)> func); 
            void RemoveBinding(int key);

        private:
            void Init(Engine* engine);
            void Terminate();

            void ProcessKey(InputEventType type, int key, int action);
            void MouseMove(double xpos, double ypos);

            void PollInputEvents();
            
            // Static methods that are called by GLFW. Instance methods are called from these.
            static void KeyboardCallbackDispatch(GLFWwindow* window, int key, int scancode, int action, int mods);
            static void MouseCallbackDispatch(GLFWwindow* window, int button, int action, int mods);
            static void MouseMoveDispatch(GLFWwindow* window, double xpos, double ypos);
    };

    class Timer {
        public:
            enum TimerState { Running, Paused, Stopped };

        private:
            time_point<steady_clock> m_StartTime; // start time after creation or Start call
            time_point<steady_clock> m_LastElapsed; // time passed since last Elapsed call
            duration<float> m_PassedTime; // passed time including paused periods
            TimerState m_State; // current state of the timer
            
        public:
            Timer();
            ~Timer();

            void Start();
            void Pause();
            void Clear(); // Stop timer

            float GetPassedTime(); // get time since Start
            float Elapsed(); // get time from last Elapsed call or from timer start

            bool isRunning();
            bool isPaused();
    };

    class ShaderUniformManager {
        private:
            static Engine* m_Engine;

        private:
            ShaderUniformManager() = delete;

        public:
            // Sets engine pointer to get data from.
            // This is because there might be multiple instances of Engine.
            static void SetEngine(Engine* engine);

            // Sets global uniforms to the current shader program.
            static void SetData();
    };
}