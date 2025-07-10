#include <api.hpp>

int main() {
    Simpleton::Engine engine(800, 800, "TicTacToe", Simpleton::EngineFlags::EnableOglDebug);
    engine.GetRenderer()->SetWindowResizable(false);
    engine.GetRenderer()->SetClearColor(0.0f, 0.0f, 0.0f);

    engine.GetInputs()->OnMouseButton = [] (int button, int action) {
        
    };

    engine.GetInputs()->OnMouseMove = [&engine] (int xpos, int ypos) {
        
    };

    engine.GetInputs()->OnKey = [&engine] (int key, int scancode, int action) {
        // printf("Key %d, Action %d!\n", key, action);
        if(key == 256 && action == 1)
            engine.Stop();
    };

    engine.Run([&engine](float dt) {
        Simpleton::Renderer* renderer = engine.GetRenderer();
        renderer->DepthTest(false);

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
        
        // Test missing texture
        Simpleton::Rect<int> destRect = {0, 0, 500, 500};
        renderer->BlitTexture(engine.GetLibrary()->GetTexture("test"), destRect);
    });
    
    return 0;
}