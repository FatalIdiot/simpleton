#include "game.hpp"

GameState& GameState::get() {
    static GameState* singleton = nullptr;
    if(singleton == nullptr) {
        singleton = new GameState;
    }
    return *singleton;
}

bool GameState::Init() {
    ClearMap();
    return true;
}

bool GameState::Quit() {
    if(highlightedMapIndexes != nullptr)
        delete [] highlightedMapIndexes;
    return true;
}

int* GameState::GetHighlightedIndexes() {
    return highlightedMapIndexes;
}

GameState::State GameState::GetState() {
    return currentState;
}

short* GameState::GetMap() {
    return Game.map;
}

short GameState::GetMark(short index) {
    return map[index];
}

short GameState::GetPlayer() {
    return currentPlayer;
}

bool GameState::CheckGameEnded() {
    short* map = Game.GetMap();

    // Return true if player won
    // List of possible winning solutions
    Simpleton::Point possibleWinIndexes[8][3] = {
        // Horizontal
        {{0, 0}, {1, 0}, {2, 0}},
        {{0, 1}, {1, 1}, {2, 1}},
        {{0, 2}, {1, 2}, {2, 2}},
        // Vertical
        {{0, 0}, {0, 1}, {0, 2}},
        {{1, 0}, {1, 1}, {1, 2}},
        {{2, 0}, {2, 1}, {2, 2}},
        // Diagonal
        {{0, 0}, {1, 1}, {2, 2}},
        {{2, 0}, {1, 1}, {0, 2}}
    };
    // Check each index list on if the marks are that same and are not empty
    for(int i = 0; i < 8; i++) {
        // Convert Points into map indexes
        int* translatedIndexes = new int[3] {
            possibleWinIndexes[i][0].x + possibleWinIndexes[i][0].y * 3,
            possibleWinIndexes[i][1].x + possibleWinIndexes[i][1].y * 3,
            possibleWinIndexes[i][2].x + possibleWinIndexes[i][2].y * 3,
        };
        // See if three map indexes have the same marks
        bool isSame = true;
        for(int i = 0; i < 3; i++) {
            if(i == 0)
                continue;
            if(map[translatedIndexes[i]] != map[translatedIndexes[i-1]])
                isSame = false;
        }
        // If same - also see the its not just all empty cells
        bool winningIndexes = isSame && map[translatedIndexes[0]] != 0;
        if(winningIndexes) {
            Game.SetState(GameState::WinnerScreen);
            Game.SetHighlightIndexes(translatedIndexes);
            return true;
        } else {
            delete [] translatedIndexes;
        }
    }

    // Return true if no more room to place marks
    bool gameDraw = true;
    for(int i = 0; i < 3 * 3; i++) {
        if(map[i] == 0) {
            gameDraw = false;
            break;
        }
    }
    if(gameDraw) {
        Game.SetState(GameState::DrawScreen);
        int* indexes = new int[3 * 3];
        for(int i = 0; i < 3 * 3; i++) {
            indexes[i] = i;
        }
        Game.SetHighlightIndexes(indexes);
        return true;
    }

    // Return false if game continues
    return false;
}

void GameState::Restart() {
    ClearMap();
    currentPlayer = 1;
    SetState(Playing);
    if(highlightedMapIndexes != nullptr)
        delete [] highlightedMapIndexes;
    highlightedMapIndexes = nullptr;
}

void GameState::ClearMap() {
    for(int i = 0; i < 3 * 3; i++) {
        map[i] = 0;
    }
}

void GameState::SetHighlightIndexes(int* indexes) {
    highlightedMapIndexes = indexes;
}

void GameState::SetState(GameState::State state) {
    currentState = state;
}

void GameState::SetMark(int index, short value) {
    if(index < 0 || index > 3 * 3)
        return;
    map[index] = value;
}

void GameState::SwitchPlayer() {
    currentPlayer = (currentPlayer == 1) ? 2 : 1;
}