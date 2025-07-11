// GameEnums.h
#pragma once

//Current scene we are rendering
enum GameState {
    OUTSIDE,
    APARTMENT,
    ROAD,
    CEMETERY,
    WORK,
    LOT,
    GRAVEYARD,
    ASTRAL,
    PARK,
    SUBWAY,
    NECROTECH,
    LOBBY,
    OFFICE,
    LAB,
    ALIEN,
    PENTHOUSE,
};

enum TrainState {
    MovingToStation,
    SlowingDown,
    StoppedAtStation,
    SpeedingUp,
    MovingFromStation,
    WaitingBeforeLoop
};

enum TransitionState {
    NONE,
    FADE_IN,
    FADE_OUT,
};

enum PauseState {
    GAME_RUNNING,
    GAME_PAUSED
};

extern GameState gameState;  // Declare global gameState
//extern PauseState currentPauseState;
