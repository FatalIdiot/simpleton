#include <api.hpp>

int main() {
    Simpleton::Engine engine(800, 800, "TicTacToe", Simpleton::EngineFlags::EnableOglDebug);
    engine.GetRenderer()->SetWindowResizable(false);
    engine.GetRenderer()->SetClearColor(0.0f, 0.0f, 0.0f);

    engine.GetInputs()->AddBinding(VK_KEY_ESCAPE, [&engine](Simpleton::InputEvent e){
        engine.Stop();
    });

    engine.Run([&engine](float dt) {        
        Simpleton::Renderer* renderer = engine.GetRenderer();
        renderer->DepthTest(false);

        // Test missing texture
        Simpleton::Rect<int> destRect = {0, 0, 500, 500};
        renderer->BlitTexture(engine.GetLibrary()->GetTexture("test"), destRect);

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