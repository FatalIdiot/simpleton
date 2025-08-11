#include <api.hpp>
#include <iostream>

int main() {
    Simpleton::Engine engine(800, 800, (char*)"TicTacToe", Simpleton::EngineFlags::EnableOglDebug);
    engine.GetRenderer()->SetWindowResizable(false);
    engine.GetRenderer()->SetClearColor(0.0f, 0.0f, 0.0f);

    // Play test sound on Space key press
    engine.GetLibrary()->AddSound("test", fs::path("assets/test.wav"));
    Simpleton::SoundSource soundSource;
    soundSource.AttachSound(engine.GetLibrary()->GetSound("test"));
    engine.GetInputs()->AddBinding(VK_KEY_SPACE, [&soundSource](Simpleton::InputEvent e){
        if(e.action != 1)
            return;
        soundSource.Play();
    });

    engine.GetInputs()->AddBinding(VK_KEY_ESCAPE, [&engine](Simpleton::InputEvent e){
        engine.Stop();
    });

    Simpleton::Texture* testTexture = engine.GetLibrary()->GetTexture("test");

    engine.Run([&engine, testTexture](float dt) {        
        Simpleton::Renderer* renderer = engine.GetRenderer();
        renderer->DepthTest(false);

        // Test moving rect
        static float testX = 0;
        static int velX = 300;
        renderer->FillRect(
            { 0.0f, 0.0f, 1.0f, 1.0f },
            { static_cast<int>(testX), 500, 50, 50 }
        );
        testX += velX * dt;
        if(velX > 0 && testX > 800 - 50)
            velX *= -1;
        if(velX < 0 && testX < 0)
            velX *= -1;


        // Test missing texture
        Simpleton::Rect<int> destRect = {0, 0, 500, 500};
        renderer->BlitTexture(testTexture, destRect);

        renderer->FillTriangle(
            { 1.0f, 1.0f, 1.0f, 1.0f },
            { 0, 0 },
            { 400, 800 },
            { 800, 0 }
        );
        renderer->FillRect(
            { 1.0f, 1.0f, 1.0f, 1.0f },
            { 50, 500, 50, 50 }
        );
        renderer->FillCircle(
            { 1.0f, 1.0f, 1.0f, 1.0f },
            { 800 - 70, 500, 50 }
        );
        
        renderer->DrawLine(
            { 1.0f, 0.0f, 0.0f, 1.0f },
            { 0, 0 },
            { 800, 800 }
        );

        renderer->DrawTriangle(
            { 1.0f, 0.0f, 0.0f, 1.0f },
            { 0, 800 },
            { 400, 0 },
            { 800, 800 }
        );

        renderer->DrawRect(
            { 1.0f, 0.0f, 0.0f, 1.0f },
            { 750, 750, 50, 50 }
        );

        renderer->DrawCircle(
            { 1.0f, 0.0f, 0.0f, 1.0f },
            { 400, 400, 200 }
        );
    });
    
    return 0;
}