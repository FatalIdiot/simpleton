#include <api.hpp>
#include "game.hpp"

#include <iostream>

int main() {
    Simpleton::Engine engine(800, 800, "TicTacToe");
    engine.GetRenderer()->SetWindowResizable(false);
    engine.GetRenderer()->SetClearColor(0.0f, 0.0f, 0.0f);

    Game.Init();
    GameState game = GameState::get();

    engine.GetInputs()->OnMouseButton = [&game] (int button, int action) {
        short cellIndex = game.m_MouseCellPos.y * 3 + game.m_MouseCellPos.x;

        // printf("State: %d, Index: %d\n", Game.GetState(), cellIndex);

        switch(Game.GetState()) {
            case GameState::Playing:
                // Skip click if cell already filled 
                if(Game.GetMark(cellIndex) != 0)
                    break;
                Game.SetMark(cellIndex, Game.GetPlayer());
                // Check if game ends after new mark was placed
                if(!Game.CheckGameEnded())
                    Game.SwitchPlayer();
                break;
            default:
                // Reset game on click after game ended
                Game.Restart();
                break;
        }
    };

    engine.GetInputs()->OnMouseMove = [&game, &engine] (int xpos, int ypos) {
        int windowW, windowH;
        engine.GetRenderer()->GetWindowSize(windowW, windowH);
        int cellW = windowW / 3; 
        int cellH = windowH / 3;
        int cellX = xpos / cellW;
        int cellY = ypos / cellH;
        game.m_MouseCellPos = { cellX, cellY };
        // printf("X: %d, Y: %d\n", cellX, cellY);
    };

    engine.GetInputs()->OnKey = [&engine] (int key, int scancode, int action) {
        // printf("Key %d, Action %d!\n", key, action);
        if(key == 256 && action == 1)
            engine.Stop();
    };

    engine.Run([]() {
        // Render frame
    });

    Game.Quit();
    engine.Terminate();
    return 0;
}