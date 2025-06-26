#include <api.hpp>

#include <iostream>

int main() {
    Simpleton::Engine engine(800, 800, "TicTacToe");
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
        // Render frame

        engine.GetRenderer()->SetWireframeRendering(true);
        engine.GetRenderer()->FillTriangle(
            { 1.0f, 1.0f, 1.0f, 1.0f },
            { 0, 0 },
            { 400, 800 },
            { 800, 0 }
        );
        engine.GetRenderer()->FillRect(
            { 1.0f, 1.0f, 1.0f, 1.0f },
            { 50, 500, 50, 50 }
        );
        engine.GetRenderer()->FillCircle(
            { 1.0f, 1.0f, 1.0f, 1.0f },
            { 800 - 70, 500, 50 }
        );
    });

    engine.Terminate();
    return 0;
}