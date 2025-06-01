#pragma once

#include <api.hpp>

#define Game GameState::get()

class GameState {
public:
    enum State { Playing = 1, WinnerScreen = 2, DrawScreen = 3 };
    Simpleton::Point m_MouseCellPos = {0, 0};

private:
    State currentState = Playing;
    short map[3 * 3];
    int* highlightedMapIndexes = nullptr;
    short currentPlayer = 1;

public:
    static GameState& get();
    bool Init();
    bool Quit();

    int* GetHighlightedIndexes();
    State GetState();
    short* GetMap();
    short GetMark(short index);
    short GetPlayer();
    bool CheckGameEnded();

    void Restart();
    void ClearMap();
    void SetHighlightIndexes(int* indexes);
    void SetState(GameState::State state);
    void SetMark(int index, short value);
    void SwitchPlayer();
};